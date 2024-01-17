from juce.juce_audio_processors import AudioProcessor
from juce.utils import AudioBuffer
from pprint import pprint


class PyAudioProcessor(AudioProcessor):
    pass
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



if __name__ == "__main__":
    proc = PyAudioProcessor()
    buff = AudioBuffer()


    # for method_name in dir(proc):
    #     method = getattr(proc, method_name)
    #     if callable(method) and not method_name.startswith("__"):
    #         for i in range(5):
    #             try:
    #                 method(*range(i))
    #                 break
    #             except TypeError:
    #                 continue
    #             except RuntimeError as e:
    #                 raise NotImplementedError("Method %s not implemented" % method_name) from None




