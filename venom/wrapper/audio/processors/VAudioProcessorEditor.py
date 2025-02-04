from juce.juce_audio_processors import AudioProcessorEditor


class VAudioProcessorEditor(AudioProcessorEditor):
    def __init__(self, processor):
        super().__init__(processor)