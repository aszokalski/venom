from venom.juce.juce_gui_basics import Slider
from venom.wrapper.audio.processors.VAudioProcessor import VAudioProcessor
from venom.wrapper.audio.processors.VAudioProcessorEditor import VAudioProcessorEditor


class BaseAudioProcessorEditor(VAudioProcessorEditor):
    def __init__(self, processor: VAudioProcessor):
        super().__init__(processor)
        self.slider = Slider("Gain")
        self.slider.setRange(-48, 48)
        self.slider.setSliderStyle(Slider.SliderStyle.linearVertical)
        self.slider.setTextBoxStyle(Slider.TextBoxBelow, True, 50, 20)
        self.slider.onValueChange = self.onSliderValueChanged
        self.addAndMakeVisible(self.slider)
        self.setSize(200, 200)

    def onSliderValueChanged(self, value):
        self.getProcessor().gain = value

    def paint(self, graphics):
        graphics.fillAll(self.findColour(0x1000000))

    def resized(self):
        self.slider.setBounds(40, 40, 20, 80)


class BaseAudioProcessor(VAudioProcessor):
    pass
