import gc

import numpy as np
from audio_basics.juce_audio_basics import MidiMessage
from audio_processor.juce_audio_processors import MidiBuffer
from audio_basics.juce_audio_basics import (Synthesiser,
                                            SynthesiserSound, SynthesiserVoice)
from audio_processor.juce_audio_processors import (AudioProcessor,
                                                   AudioProcessorEditor,
                                                   Colour)
from ui_basics.ui_basics import Slider


class synth:
    def __init__(self, sample_rate: int = 44100, waveform: str = "sine"):
        self.sample_rate = sample_rate
        self.waveform = waveform
        self.frequency = 440.0
        self.amplitude = 0.5
        self.phase = 0.0
        self.note_on = False
        self.current_note = None

    def note_to_freq(self, note: int) -> float:
        return 440.0 * (2.0 ** ((note - 69) / 12.0))

    def handle_midi_message(self, message):
        if message.isNoteOn():
            self.note_on = True
            self.current_note = message.getNoteNumber()
            self.frequency = self.note_to_freq(self.current_note)

        elif message.isNoteOff() and message.getNoteNumber() == self.current_note:
            self.note_on = False

    def generate_waveform(self, num_samples: int):
        t = (np.arange(num_samples) + self.phase) / self.sample_rate
        self.phase = (self.phase + num_samples) % self.sample_rate

        if self.waveform == "sine":
            return np.sin(2 * np.pi * self.frequency * t)
        elif self.waveform == "square":
            return np.sign(np.sin(2 * np.pi * self.frequency * t))
        elif self.waveform == "sawtooth":
            return 2 * (t * self.frequency - np.floor(0.5 + t * self.frequency))
        elif self.waveform == "triangle":
            return (
                2
                * np.abs(2 * (t * self.frequency - np.floor(t * self.frequency + 0.5)))
                - 1
            )
        else:
            raise ValueError(f"Unsupported waveform: {self.waveform}")

    def process(self, buffer):
        num_samples = buffer.getNumSamples()

        if not self.note_on:
            for channel in range(buffer.getNumChannels()):
                data = buffer.getWritePointer(channel)
                data[:] = np.zeros(num_samples)
            return buffer

        waveform = self.generate_waveform(num_samples) * self.amplitude

        for channel in range(buffer.getNumChannels()):
            data = buffer.getWritePointer(channel)
            data[:] = waveform

        return buffer

    # tak sobie wobrazam ze powinno tak dzialac, aczkolwiek tak sie nie dzieje
    def processBlock(self, buffer, midiMessages):
        print(midiMessages.getNumEvents())
        iterator = midiMessages.begin()
        end = midiMessages.end()
        print("iterator:", iterator)
        print("end:", end)

        while iterator != end:
            event = next(iterator)
            message = event.getMessage()
            sample_pos = event.samplePosition
            print(f"MIDI event at sample {sample_pos}")

        # for message in midiMessages:
        #     self.synth.handle_midi_message(message)
        self.process(buffer)


gc.disable()
class SineWaveVoice(SynthesiserVoice):
    def __init__(self):
        super().__init__()
        self.sample_rate = 44100
        self.frequency = 440.0
        self.amplitude = 0.5
        self.phase = 0.0

    def generate_waveform(self, num_samples: int):
        t = (np.arange(num_samples) + self.phase) / self.sample_rate
        self.phase = (self.phase + num_samples) % self.sample_rate
        return np.sin(2 * np.pi * self.frequency * t)

    def startNote(self, midiNoteNumber, velocity, sound, pitch):
        self.frequency = MidiMessage.getMidiNoteInHertz(midiNoteNumber)
        print(f"Note: {midiNoteNumber}, Frequency: {self.frequency}")

    def stopNote(self, velocity, allowTailOff):
        pass

    def renderNextBlock(self, buffer, start_sample, num_samples):
        waveform = self.generate_waveform(num_samples) * self.amplitude
        print(f"Generated waveform: {waveform}")

        for channel in range(buffer.getNumChannels()):
            data = buffer.getWritePointer(channel)
            data[:] = waveform


class SineWaveSound(SynthesiserSound):
    def __init__(self):
        super().__init__()

    def appliesToNote(self, midiNoteNumber):
        return True

    def appliesToChannel(self, midiChannel):
        return True


class PyAudioProcessorEditor(AudioProcessorEditor):
    def __init__(self, processor):
        super().__init__(processor)
        self.setSize(400, 400)
        self.slider = Slider()
        self.slider.setBounds(20, 20, 200, 20)
        self.addAndMakeVisible(self.slider, 1)


class PySynth(AudioProcessor):
    def __init__(
        self,
        voices: int = 4,
        sound: SynthesiserSound = SineWaveSound(),
        voice: SynthesiserVoice = SineWaveVoice(),
    ):
        super().__init__()
        self.synth = Synthesiser()

        self.synth.clearVoices()
        self.synth.clearSounds()

        for _ in range(voices):
            self.synth.addVoice(voice)
        self.synth.addSound(sound)

    def processBlock(self, buffer, midiMessages):
        buffer.clear()
        self.synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples())

    def createEditor(self):
        return PyAudioProcessorEditor(self)

