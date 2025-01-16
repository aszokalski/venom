import sys
import os
import numpy
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from pytest.mocks.mock_audio_buffer import MockAudioBuffer


class effect_base:
    def __init__(self):
        pass

    def process(self, buffer):
        return buffer


class soft_clipper(effect_base):
    def __init__(self, gain: float):
        self.gain = gain

    def process(self, buffer):
        num_channels = buffer.getNumChannels()
        for channel in range(num_channels):
            data = buffer.getWritePointer(channel)
            for sample in range(buffer.getNumSamples()):
                data[sample] = numpy.tanh(data[sample] * self.gain)
        return buffer
    

class simple_delay(effect_base):
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


class chorus(effect_base):
    def __init__(self, sample_rate: int, depth: float, rate: float, wet: float):
        self.sample_rate = sample_rate
        self.depth = depth
        self.rate = rate
        self.wet = wet
        self.phase = 0.0
        self.delay_buffer = MockAudioBuffer(1, int(sample_rate * 0.05))
        self.delay_buffer.clear()
        self.delay_buffer_index = 0

    def process(self, buffer):
        num_channels = buffer.getNumChannels()
        for channel in range(num_channels):
            data = buffer.getWritePointer(channel)
            delay_data = self.delay_buffer.getWritePointer(0)
            for sample in range(buffer.getNumSamples()):
                lfo = (numpy.sin(self.phase) + 1) / 2
                delay_length = int(lfo * self.depth * self.sample_rate)
                
                read_index = (self.delay_buffer_index - delay_length) % self.delay_buffer.getNumSamples()
                delayed_sample = delay_data[read_index]

                delay_data[self.delay_buffer_index] = data[sample]
                self.delay_buffer_index = (self.delay_buffer_index + 1) % self.delay_buffer.getNumSamples()

                data[sample] = data[sample] * (1 - self.wet) + delayed_sample * self.wet

                self.phase += 2 * numpy.pi * self.rate / self.sample_rate
                if self.phase > 2 * numpy.pi:
                    self.phase -= 2 * numpy.pi
        return buffer
