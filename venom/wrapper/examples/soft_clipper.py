import numpy
from venom.wrapper.module import Module

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
