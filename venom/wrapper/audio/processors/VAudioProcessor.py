from juce.juce_audio_processors import AudioProcessor
from juce.utils import AudioBuffer

class VAudioProcessor(AudioProcessor):
    def process_block(self, buffer: AudioBuffer, midiMessages):
        raise NotImplementedError
    
    def create_editor(self):
        return None

    def processBlock(self, buffer: AudioBuffer, midiMessages):
        self.process_block(buffer, midiMessages)

    def createEditor(self):
        return self.create_editor()

    # Methods below dont need to be implemented in inheriting classes
    def prepareToPlay(self, sampleRate, samplesPerBlock):
        pass

    def releaseResources(self):
        pass

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
