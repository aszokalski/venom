# Later MockAudioBuffer will be replaced with AudioBuffer from pybind
from pathlib import Path
import sys

current_path = Path(__file__).resolve()
parent_path = current_path.parents[4]
sys.path.append(str(parent_path))

from tests.pytest.mocks.mock_audio_buffer import MockAudioBuffer


class VAudioBuffer(MockAudioBuffer):
    def __len__(self):
        return len(self._buffer)

    def __iter__(self):
        self._last_channel = 0
        return self

    def __next__(self):
        channel_id = self._last_channel
        self._last_channel += 1
        if self._last_channel > len(self):
            raise StopIteration
        return self.getWritePointer(channel_id)

    @property
    def buffer(self):
        return self._buffer
