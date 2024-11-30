from audio_processor.juce_audio_processors import AudioProcessorEditor

from venom.wrapper.audio.processors.VAudioProcessor import VAudioProcessor


class VAudioProcessorEditor(AudioProcessorEditor):
    def __init__(self, processor: VAudioProcessor):
        super().__init__(processor)
