from juce.utils import AudioBuffer
from typing import Union, List, Callable

class Module:
    """Base class for audio processing modules.
    
    Provides interface for audio processing and operator overloading for 
    creating processing chains. Modules can be chained using >> and << operators.

    Example:
        >>> delay = simple_delay(44100, 2, 0.5, 0.5)
        >>> clipper = soft_clipper(0.5)
        >>> processed = (delay >> clipper).process(buffer)
    """

    def __init__(self):
        pass

    def process(self, buffer: AudioBuffer) -> AudioBuffer:
        """Process audio buffer.
        
        Args:
            buffer: Input audio buffer to process.
            
        Returns:
            Processed audio buffer.
            
        Raises:
            NotImplementedError: If not implemented by subclass.
        """
        raise NotImplementedError

    def __rshift__(self, other: Union[List['Module'], 'Module']) -> 'Module':
        """Forward processing chain operator (>>).
        
        Args:
            other: Single module or list of modules to chain after this one.
            
        Returns:
            New Module instance that chains processing.
        """
        if isinstance(other, list):
            def chain_process(buffer):
                result = self.process(buffer)
                for module in other:
                    result = module.process(result)
                return result
        else:
            def chain_process(buffer):
                return other.process(self.process(buffer))
                
        return_module = Module()
        return_module.process = chain_process
        return return_module

    def __lshift__(self, other: Union[List['Module'], 'Module']) -> 'Module':
        """Backward processing chain operator (<<).
        
        Args:
            other: Single module or list of modules to chain before this one.
            
        Returns:
            New Module instance that chains processing.
        """
        if isinstance(other, list):
            def chain_process(buffer):
                result = buffer
                for module in reversed(other):
                    result = module.process(result)
                return self.process(result)
        else:
            def chain_process(buffer):
                return self.process(other.process(buffer))
                
        return_module = Module()
        return_module.process = chain_process
        return return_module