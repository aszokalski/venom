from venom.wrapper.module import Module
from pytest.mocks.mock_audio_buffer import MockAudioBuffer

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