import sys
import os
import gc
import numpy as np
from audio_processor.juce_audio_processors import AudioProcessor, AudioProcessorEditor, Colour
from audio_basics.juce_audio_basics import (Synthesiser,
                                            SynthesiserSound, SynthesiserVoice)
from audio_processor.juce_audio_processors import (AudioProcessor,
                                                   AudioProcessorEditor,
                                                   Colour)
from audio_basics.juce_audio_basics import MidiMessage
from ui_basics.ui_basics import Slider
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
import venom_effects
import venom_synth

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

class PyAudioProcessor(AudioProcessor):
    def __init__(self):
        super().__init__()
        self.sample_rate = 44100
        self.delay = venom_effects.simple_delay(self.sample_rate, 2, 0.25, 0.5, 0.5)
        self.clipper = venom_effects.soft_clipper(30)

        sound: SynthesiserSound = SineWaveSound(),
        voice: SynthesiserVoice = SineWaveVoice(),

        self.synth = Synthesiser()

        self.synth.clearVoices()
        self.synth.clearSounds()

        for _ in range(4):
            self.synth.addVoice(voice)
        self.synth.addSound(sound)

    def processBlock(self, buffer, midiMessages):
        buffer.clear()
        self.synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples())

    def prepareToPlay(self, sampleRate, samplesPerBlock):
        self.sample_rate = sampleRate

    def releaseResources(self):
        pass

    def createEditor(self):
        return PyAudioProcessorEditor(self)

    def hasEditor(self):
        return True

    def getName(self):
        return "PyAudioProcessor"

    def acceptsMidi(self):
        return True

    def isMidiEffect(self):
        return False

    def producesMidi(self):
        return False

    def getTailLengthSeconds(self):
        return 0

    def getNumPrograms(self):
        return 0

    def getCurrentProgram(self):
        return 0
    
    def setCurrentProgram(self, index):
        pass

    def getProgramName(self, index):
        return ""

    def changeProgramName(self, index, newName):
        pass

    def getStateInformation(self, memoryBlock):
        pass

    def setStateInformation(self, data, sizeInBytes):
        pass
