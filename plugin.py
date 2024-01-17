from juce.juce_audio_processors import AudioProcessor
from juce.utils import AudioBuffer


class VAudioProcessor(AudioProcessor):
    # Todo: implement a simple plugin
    def prepareToPlay(self, sampleRate, samplesPerBlock):
        pass

    def releaseResources(self):
        pass

    def processBlock(self, buffer: AudioBuffer, midiMessages):
        buffer.applyGain(14)

    def createEditor(self):
        return None

    def hasEditor(self):
        return False

    def getName(self):
        print("PyAudioProcessor.getName()")
        return "PyAudioProcessor"

    def acceptsMidi(self):
        return True

    def producesMidi(self):
        return True

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
