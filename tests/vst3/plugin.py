import gc

import numpy as np
from audio_processor.juce_audio_processors import AudioProcessor

gc.disable()


class PyAudioProcessor(AudioProcessor):
    def __init__(self):
        super().__init__()
        self.sample_rate = 44100

    def prepareToPlay(self, sampleRate, samplesPerBlock):
        self.sample_rate = sampleRate

    def releaseResources(self):
        pass

    def processBlock(self, buffer, midiMessages):
        numChannels = buffer.getNumChannels()

        for channel in range(numChannels):
            data = buffer.getWritePointer(channel)
            a = np.fft.fft(np.ones((2000, 2000)))
            data[:] = data * 20.2

    def createEditor(self):
        return None

    def hasEditor(self):
        return False

    def getName(self):
        return "PyAudioProcessor"

    def acceptsMidi(self):
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
