# Later MockAudioBuffer will be replaced with AudioBuffer from pybind
from pathlib import Path
import sys

current_path = Path(__file__).resolve()
parent_path = current_path.parents[4]
sys.path.append(str(parent_path))

from tests.pytest.mocks.mock_audio_buffer import MockAudioBuffer
import numpy as np


class VAudioBuffer(np.ndarray):
    def __new__(cls, audioBuffer: MockAudioBuffer):
        obj = np.asarray(audioBuffer._buffer).view(cls)
        obj._audio_buffer = audioBuffer
        return obj

    def __array_finalize__(self, obj):
        if obj is None: return
        self._audio_buffer = getattr(obj, '_audio_buffer', None)

    def __init__(self, audioBuffer: MockAudioBuffer):
        self._audio_buffer = audioBuffer

    def getNumChannels(self) -> int:
        return self._audio_buffer.getNumChannels()

    def getNumSamples(self) -> int:
        return self._audio_buffer.getNumSamples()

    def getWritePointer(self, channelNumber: int):
        return self._audio_buffer.getWritePointer(channelNumber)

    @property
    def buffer(self):
        return self._audio_buffer._buffer
