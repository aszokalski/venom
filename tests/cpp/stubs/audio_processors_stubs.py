from audio_processor.juce_audio_processors import AudioProcessorEditor
from audio_processor.juce_audio_processors import AudioProcessor
from audio_processor.juce_audio_processors import Colour

class PyAudioProcessorEditor(AudioProcessorEditor):
    def __init__(self, processor):
        super().__init__(processor)
        self.setSize(200, 400)
    def paint(self, graphics):
        graphics.fillAll(Colour(1.0, 1.0, 1.0, 0.8))
        pass

    def resized(self):
        pass
class PyAudioProcessor(AudioProcessor):
    def __init__(self):
        super().__init__()


    def prepareToPlay(self, sampleRate, samplesPerBlock):
        pass


    def releaseResources(self):
        pass

    def processBlock(self, buffer, midiMessages):
        pass


    def createEditor(self):
        return PyAudioProcessorEditor(self)

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