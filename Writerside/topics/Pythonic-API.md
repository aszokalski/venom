# Pythonic API

Further details about the Pythonic API will be added here as development progresses.

The concept of a Pythonic API is designed to simplify the creation of plugins, making programming more accessible to individuals new to coding.
Python offers an easier entry point compared to languages like C++.
Moreover, Python's syntax enhances the readability and maintainability of code.

## Dependency Injection
Our approach includes the development of interface classes.
These interfaces will be set up using constructors that insert pybind-generated classes, ensuring everything works together smoothly.

## Pythonic API example
To illustrate our vision, we present an example of how an AudioBuffer class might be utilized.

### Using AudioBuffer in Juce (C++)
<code-block lang="C++">
    <![CDATA[
    auto totalNumInputChannels = getTotalNumInputChannels();

    for (auto channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            channelData[i] *= 0.2f;
        }
    }
]]>
</code-block>
In this C++ example, iterating over each channel and sample is necessary to modify audio data.

### Using VAudioBuffer in Venom (Python)
<code-block lang="python">
    buffer *= 0.2
</code-block>
This single line of code updates all values simultaneously without the need for explicit iteration over channels and samples.
While detailed manipulation of each sample is still possible, simpler operations are much easier to write.