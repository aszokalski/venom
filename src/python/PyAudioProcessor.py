from juce import AudioProcessor


class PyAudioProcessor(AudioProcessor):
    # Todo: implement a simple plugin
    def processBlock(self, buffer, midiMessages):
        print("processBlock called")

    def test(self):
        print("Hello from Python!")


if __name__ == "__main__":
    proc = PyAudioProcessor()
    proc.test()
