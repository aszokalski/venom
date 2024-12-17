import numpy as np


class synth:
    def __init__(self, sample_rate: int = 44100, waveform: str = 'sine'):
        self.sample_rate = sample_rate
        self.waveform = waveform
        self.frequency = 440.0
        self.amplitude = 0.5
        self.phase = 0.0

    def generate_waveform(self, num_samples: int):
        t = (np.arange(num_samples) + self.phase) / self.sample_rate
        self.phase = (self.phase + num_samples) % self.sample_rate

        if self.waveform == 'sine':
            return np.sin(2 * np.pi * self.frequency * t)
        elif self.waveform == 'square':
            return np.sign(np.sin(2 * np.pi * self.frequency * t))
        elif self.waveform == 'sawtooth':
            return 2 * (t * self.frequency - np.floor(0.5 + t * self.frequency))
        elif self.waveform == 'triangle':
            return 2 * np.abs(2 * (t * self.frequency - np.floor(t * self.frequency + 0.5))) - 1
        else:
            raise ValueError(f"Unsupported waveform: {self.waveform}")

    def process(self, buffer):
        num_samples = buffer.getNumSamples()
        waveform = self.generate_waveform(num_samples) * self.amplitude

        for channel in range(buffer.getNumChannels()):
            data = buffer.getWritePointer(channel)
            data[:] = waveform

        return buffer
