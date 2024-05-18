import numpy as np
from copy import deepcopy


class MockAudioBuffer:
    def __init__(self, numChannels_or_audioBuffer: int = 0, numSamples: int = 0):
        if isinstance(numChannels_or_audioBuffer, MockAudioBuffer):
            audioBuffer = numChannels_or_audioBuffer
            self._numChannels = audioBuffer._numChannels
            self._numSamples = audioBuffer._numSamples
            self._buffer = deepcopy(audioBuffer._buffer)
        else:
            self._numChannels = numChannels_or_audioBuffer
            self._numSamples = numSamples
            self._buffer = np.random.rand(self._numChannels, self._numSamples)

    def getNumChannels(self) -> int:
        return self._numChannels

    def getNumSamples(self) -> int:
        return self._numSamples

    def getWritePointer(self, channelNumber: int):
        return self._buffer[channelNumber]

    def clear(self):
        self._buffer = np.zeros(self._numChannels, self._numSamples)
