from audio_processor.juce_audio_processors import AudioProcessor
import math

class PyAudioProcessor(AudioProcessor):
    def __init__(self):
        super().__init__()
        self.sample_rate = 44100
        self.freq = 210
        .0
        self.level = 0.06

    def prepareToPlay(self, sampleRate, samplesPerBlock):
        self.currentPhase = 0.0
        self.sample_rate = sampleRate
        self.phaseDelta =(self.freq/sampleRate)*2.0*math.pi


    def releaseResources(self):
        pass

    def processBlock(self, buffer, midiMessages):
        buffer.clear()
        for channel in range(buffer.getNumChannels()):
            data = buffer.getWritePointer(channel)
            for sample in range(buffer.getNumSamples()):
                data[sample] = math.sin(self.currentPhase)*self.level
                self.currentPhase += self.phaseDelta

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