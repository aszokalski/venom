import sys
import os
import gc
from venom.wrapper.audio.processors.VAudioProcessor import VAudioProcessor
from venom.wrapper.audio.processors.VAudioProcessorEditor import VAudioProcessorEditor
from pytest.mocks.mock_audio_buffer import MockAudioBuffer
from ui_basics.ui_basics import Slider
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
import venom_effects

class Module:
    def __init__(self):
        pass

    def process(self, buffer):
        raise NotImplementedError

class simple_delay(Module):
    def __init__(self, sample_rate : int, channel_num : int, time : float, feedback : float, wet : float):
        self.sample_rate = sample_rate
        self.time = time
        self.feedback = feedback
        self.wet = wet
        self.delay_buffer = MockAudioBuffer(channel_num, int(sample_rate * time))
        self.delay_buffer.clear()
        self.delay_buffer_index = [0] * channel_num
    
    def process(self, buffer):
        num_channels = buffer.getNumChannels()
        for channel in range(num_channels):
            data = buffer.getWritePointer(channel)
            delay_data = self.delay_buffer.getWritePointer(channel)
            for sample in range(buffer.getNumSamples()):
                delayed_sample = delay_data[self.delay_buffer_index[channel]]
                delay_data[self.delay_buffer_index[channel]] = data[sample] * self.wet + delayed_sample * self.feedback
                data[sample] += delayed_sample
                self.delay_buffer_index[channel] = (self.delay_buffer_index[channel] + 1) % self.delay_buffer.getNumSamples()
        return buffer

gc.disable()
class CustomAudioProcessorEditor(VAudioProcessorEditor):
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

    def prepareToPlay(self, sampleRate, samplesPerBlock):
        self.sample_rate = sampleRate

    def processBlock(self, buffer, midiMessages):
        buffer = self.delay.process(buffer)

    def createEditor(self):
        return CustomAudioProcessorEditor(self)
