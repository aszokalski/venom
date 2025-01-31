import venom_effects

class venom_plugin:
    def __init__(self, sample_rate):
        self.sample_rate = sample_rate
        self.delay = venom_effects.simple_delay(self.sample_rate, 2, 0.25, 0.3, 0.3)
        self.clipper = venom_effects.soft_clipper(30)

    def process_block(self, buffer):
        self.delay.process(buffer)
        self.clipper.process(buffer)
        return buffer
