from audio_processor.juce_audio_processors import AudioProcessorEditor
from audio_processor.juce_audio_processors import AudioProcessor
import gc
class PyAudioProcessorEditor(AudioProcessorEditor):
    def __init__(self, processor):
        super().__init__(processor)
        self.setSize(200, 400)
    def paint(self, graphics):
        pass

    def resized(self):
        pass
class PyAudioProcessor(AudioProcessor):
    def __init__(self):
        super().__init__()
    def prepareToPlay(self, sampleRate, samplesPerBlock):
        print(f"DUPA: {sampleRate} {samplesPerBlock}")

    def releaseResources(self):
        pass

    def processBlock(self, buffer, midiMessages):
        pass

    def createEditor(self):
        return None

    def hasEditor(self):
        return True

    def getName(self):
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