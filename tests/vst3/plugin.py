import sys
import os
import gc
from venom.wrapper.audio.processors.VAudioProcessor import VAudioProcessor
from venom.wrapper.audio.processors.VAudioProcessorEditor import VAudioProcessorEditor
from pytest.mocks.mock_audio_buffer import MockAudioBuffer
from ui_basics.ui_basics import Slider
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
from venom_effects import simple_delay, soft_clipper

gc.disable()
class PyAudioProcessorEditor(VAudioProcessorEditor):
    def __init__(self, processor):
        super().__init__(processor)
        self.setSize(400, 400)
        self.slider = Slider()
        self.slider.setBounds(20, 20, 200, 20)
        self.addAndMakeVisible(self.slider, 1)

class PyAudioProcessor(VAudioProcessor):
    def __init__(self):
        super().__init__()
        self.sample_rate = 44100
        self.delay = simple_delay(self.sample_rate, 2, 0.25, 0.5, 0.5)
        self.clipper1 = soft_clipper(0.5)
        self.clipper2 = soft_clipper(0.25)

    def process_block(self, buffer, midiMessages):
        buffer = (self.delay >> self.clipper1).process(buffer)
        buffer = (self.delay >> [self.clipper2, self.clipper2]).process(buffer)
        return buffer

    def create_editor(self):
        return PyAudioProcessorEditor(self)