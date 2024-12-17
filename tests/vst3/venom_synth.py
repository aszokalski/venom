import numpy as np
from audio_basics.juce_audio_basics import (
    MidiMessage,
    AudioSource,
    Synthesiser,
    SynthesiserVoice,
    SynthesiserSound,
)


class SineWaveVoice(SynthesiserVoice):
    def __init__(self):
        super().__init__()
        self.frequency = 440.0
        self.amplitude = 0.5
        self.phase = 0.0

    def startNote(self, midiNoteNumber, velocity, sound, pitch):
        pass

    def stopNote(self, velocity, allowTailOff):
        pass

    def pitchWheelMoved(self, newValue):
        pass

    def controllerMoved(self, controllerNumber, newValue):
        pass

    def renderNextBlock(self, buffer, start_sample, num_samples):
        t = (np.arange(num_samples) + self.phase) / self.get_sample_rate()
        self.phase = (self.phase + num_samples) % self.get_sample_rate()
        waveform = np.sin(2 * np.pi * self.frequency * t) * self.amplitude

        for channel in range(buffer.getNum_channels()):
            data = buffer.get_write_pointer(channel)
            data[start_sample : start_sample + num_samples] += waveform


class SineWaveSound(SynthesiserSound):
    def __init__(self):
        super().__init__()

    def appliesToNote(self, midiNoteNumber):
        return True

    def appliesToChannel(self, midiChannel):
        return True

    def get_name(self):
        return "SineWaveSound"


class PySynth(AudioSource):
    def __init__(
        self,
        sample_rate: int = 44100,
        waveform: str = "sine",
        voices: int = 4,
        sound: SynthesiserSound = SineWaveSound(),
    ):
        super().__init__()
        self.sample_rate = sample_rate
        self.waveform = waveform
        self.frequency = 440.0
        self.amplitude = 0.5
        self.phase = 0.0
        self.note_on = False
        self.current_note = None
        self.synth = Synthesiser()

        for _ in range(voices):
            self.synth.addVoice(SineWaveVoice())
        self.synth.addSound(sound)

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
        for message in midiMessages:
            self.synth.handle_midi_message(message)
        self.synth.process(buffer)

