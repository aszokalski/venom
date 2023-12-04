from juce import AudioProcessor


class PyAudioProcessor(AudioProcessor):
    def test(self):
        print("Hello from Python!")


if __name__ == "__main__":
    proc = PyAudioProcessor()
    proc.test()
