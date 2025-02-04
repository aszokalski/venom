import sys
import os
import numpy
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from pytest.mocks.mock_audio_buffer import MockAudioBuffer

class Module:
    def __init__(self):
        pass

    def process(self, buffer):
        raise NotImplementedError

    def __rshift__(self, other):
        if isinstance(other, list):
            def chain_process(buffer):
                result = self.process(buffer)
                for module in other:
                    result = module.process(result)
                return result
        else:
            def chain_process(buffer):
                return other.process(self.process(buffer))
                
        return_module = Module()
        return_module.process = chain_process
        return return_module

    def __lshift__(self, other):
        if isinstance(other, list):
            def chain_process(buffer):
                result = buffer
                for module in reversed(other):
                    result = module.process(result)
                return self.process(result)
        else:
            def chain_process(buffer):
                return self.process(other.process(buffer))
                
        return_module = Module()
        return_module.process = chain_process
        return return_module

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


class soft_clipper(Module):
    def __init__(self, gain : float):
        self.gain = gain

    def process(self, buffer):
        num_channels = buffer.getNumChannels()
        for channel in range(num_channels):
            data = buffer.getWritePointer(channel)
            for sample in range(buffer.getNumSamples()):
                data[sample] = numpy.tanh(data[sample] * self.gain)
        return buffer
