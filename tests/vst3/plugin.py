# import pandas
# import requests
# from pedalboard import *
from scipy.signal import butter, lfilter
#
# from pedalboard.io import AudioStream
import os
print("PYTHONPATH:", os.environ.get('PYTHONPATH'))
print("PATH:", os.environ.get('PATH'))
# import traceback
# try:
#     import numpy.core.multiarray
#     # import numpy
# except:
#     traceback.print_exc()
# # import importlib.util
# # print(importlib.util.find_spec('numpy'))
from audio_processor.juce_audio_processors import AudioProcessor
import math
import numpy as np
print("DONE")
class PyAudioProcessor(AudioProcessor):
    def __init__(self):
        super().__init__()
        self.sample_rate = 44100
        self.freq = 210.0
        self.level = 0.06
        self.value = 0

        self.chorus_delay_time = 0.03  # Base delay time in seconds
        self.chorus_depth = 0.01  # Depth of modulation in seconds
        self.chorus_rate = 0.25  # LFO rate in Hz
        self.max_delay_samples = int((self.chorus_delay_time + self.chorus_depth) * self.sample_rate)
        self.delay_buffer = np.zeros((2, self.max_delay_samples))
        self.delay_index = 0

    def prepareToPlay(self, sampleRate, samplesPerBlock):
        self.currentPhase = 0.0
        self.sample_rate = sampleRate
        self.phaseDelta = (self.freq / sampleRate) * 2.0 * math.pi
        self.value = 0

        # Initialize delay buffer for chorus effect
        self.max_delay_samples = int((self.chorus_delay_time + self.chorus_depth) * sampleRate)
        self.delay_buffer = np.zeros((2, self.max_delay_samples))
        self.delay_index = 0

    def releaseResources(self):
        pass


    def butter_lowpass(self, cutoff, fs, order=5):
        nyquist = 0.5 * fs
        normal_cutoff = cutoff / nyquist
        b, a = butter(order, normal_cutoff, btype='low', analog=False)
        return b, a

    def apply_lowpass_filter(self, audio_buffer, cutoff, fs, order=5):
        b, a = self.butter_lowpass(cutoff, fs, order=order)
        y = lfilter(b, a, audio_buffer)
        return y

    def apply_chorus(self, samples, channel):
        numSamples = samples.shape[0]
        output = np.zeros_like(samples)

        for i in range(numSamples):
            # Calculate current delay using LFO
            lfo = 0.5 * (1 + math.sin(2 * math.pi * self.chorus_rate * self.value / self.sample_rate))
            current_delay_samples = int(self.sample_rate * (self.chorus_delay_time + self.chorus_depth * lfo))

            # Get delayed sample
            read_index = (self.delay_index - current_delay_samples + self.max_delay_samples) % self.max_delay_samples
            delayed_sample = self.delay_buffer[channel, read_index]

            # Mix delayed sample with current sample
            output[i] = samples[i] + delayed_sample

            # Write current sample to delay buffer
            self.delay_buffer[channel, self.delay_index] = samples[i]
            self.delay_index = (self.delay_index + 1) % self.max_delay_samples
            self.value += 1

        return output
    # def processBlock(self, buffer, midiMessages):
    #     buffer.clear()
    #     numChannels = buffer.getNumChannels()
    #     numSamples = buffer.getNumSamples()
    #
    #     if self.value % 10000 == 0:
    #         print(numChannels)
    #         print(type(buffer.getWritePointer(0)))
    #
    #     self.value += 1
    #
    #     t = np.arange(numSamples)  # Create a time array
    #     currentPhaseArray = self.currentPhase + self.phaseDelta * t
    #
    #     for channel in range(numChannels):
    #         data = buffer.getWritePointer(channel)
    #         data[:] = np.sin(currentPhaseArray) * self.level  # Generate and fill the sine wave in place
    #
    #     self.currentPhase = (self.currentPhase + self.phaseDelta * numSamples) % (2 * math.pi)
    def processBlock(self, buffer, midiMessages):
        numChannels = buffer.getNumChannels()
        numSamples = buffer.getNumSamples()

        if self.value % 10000 == 0:
            print(f"Number of Channels: {numChannels}")
            print(f"Buffer Type: {type(buffer.getWritePointer(0))}")

        self.value += 1

        for channel in range(numChannels):
            data = buffer.getWritePointer(channel)
            # effected = self.apply_chorus(data, channel)
            # effected = self.apply_gain(data, channel)
            effected = self.apply_lowpass_filter(data, 1000.0, self.sample_rate)
            np.copyto(data, effected)

    def apply_gain(self, samples, channel):
        return samples * self.level

    def createEditor(self):
        return None

    def hasEditor(self):
        return False

    def getName(self):
        return "PyAudioProcessor"

    def acceptsMidi(self):
        return False

    def producesMidi(self):
        return False

    def getTailLengthSeconds(self):
        return 0

    def getNumPrograms(self):
        return 0

    def getCurrentProgram(self):
        return 0

    def setCurrentProgram(self, index):
        pass

    def getProgramName(self, index):
        return ""

    def changeProgramName(self, index, newName):
        pass

    def getStateInformation(self, memoryBlock):
        pass

    def setStateInformation(self, data, sizeInBytes):
        pass