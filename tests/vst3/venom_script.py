import sys
import os
sys.path.append(os.path.dirname(os.path.abspath(__file__)))
import venom_effects

class venom_plugin:
    def __init__(self, sample_rate):
        self.sample_rate = sample_rate
        self.chorus = venom_effects.chorus(self.sample_rate, 0.1, 0.25, 0.5)
        self.delay = venom_effects.simple_delay(self.sample_rate, 2, 0.1666, 0.3, 0.3)
        self.clipper = venom_effects.soft_clipper(40)

    def process_block(self, buffer):
        self.chorus.process(buffer)
        self.delay.process(buffer)
        # self.clipper.process(buffer)
        # num_channels = buffer.getNumChannels()
        # for channel in range(num_channels):
        #     data = buffer.getWritePointer(channel)
        #     for sample in range(buffer.getNumSamples()):
        #         data[sample] = data[sample] * 0.2
        return buffer
