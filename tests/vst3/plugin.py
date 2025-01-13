import sys
import os
import gc
from audio_processor.juce_audio_processors import AudioProcessor, AudioProcessorEditor, Colour
from ui_basics.ui_basics import Slider
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
import venom_effects
import venom_synth

gc.disable()
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

    def prepareToPlay(self, sampleRate, samplesPerBlock):
        self.sample_rate = sampleRate

    def processBlock(self, buffer, midiMessages):
        self.synth.processBlock(buffer, midiMessages)

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