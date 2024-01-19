from juce.juce_audio_processors import AudioProcessor, AudioProcessorEditor
from juce.utils import AudioBuffer
from juce.juce_gui_basics import Slider
class PyAudioProcessorEditor(AudioProcessorEditor):
    def __init__(self, processor):
        super().__init__(processor)
        self.slider = Slider("Gain")
        self.slider.setRange(-48, 48)
        self.slider.setSliderStyle(Slider.SliderStyle.linearVertical)
        self.slider.setTextBoxStyle(Slider.TextBoxBelow, True, 50, 20)
        self.slider.onValueChange = self.onSliderValueChanged
        self.addAndMakeVisible(self.slider)
        self.setSize(200, 200)

    def onSliderValueChanged(self, value):
        self.getProcessor().gain = value

    def paint(self, graphics):
        graphics.fillAll(self.findColour(0x1000000))

    def resized(self):
        self.slider.setBounds(40, 40, 20, 80)

class PyAudioProcessor(AudioProcessor):
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
        return PyAudioProcessorEditor(self)

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
