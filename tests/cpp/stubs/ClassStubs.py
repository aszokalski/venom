def create_mock_class(base_class):
    def mock_method(*args, **kwargs):
        return False
    methods = {method_name: mock_method for method_name in dir(base_class)
               if callable(getattr(base_class, method_name)) and not (method_name.startswith('__') and method_name.endswith('__'))}
    mock_class = type('Mock' + base_class.__name__, (base_class,), methods)
    return mock_class

# class PyAudioProcessorEditor(AudioProcessorEditor):
#     def __init__(self, processor):
#         super().__init__(processor)
#
#     def paint(self, graphics):
#         pass
#
#     def resized(self):
#         pass

if __name__ == '__main__':
    class Base:
        def __init__(self):
            pass

    def hello(self):
        pass
    clazz = create_mock_class(Base)
    import inspect
    print(inspect.getmro(clazz))
    print(clazz())