#include "include/initializer/Initializer.h"

class JuceInitializer {
public:
    static JuceInitializer &getInstance() {
        static JuceInitializer instance;
        return instance;
    }

    void shutdown() {
        juce::DeletedAtShutdown::deleteAll();
        juce::MessageManager::deleteInstance();
    }

private:
    juce::ScopedJuceInitialiser_GUI juceInitialiser;

    JuceInitializer() = default;

    ~JuceInitializer() = default;

    JuceInitializer(const JuceInitializer &) = delete;

    JuceInitializer &operator=(const JuceInitializer &) = delete;
};

extern "C" void initializeJuce() {
    JuceInitializer::getInstance();
}

extern "C" void shutdownJuce() {
    JuceInitializer::getInstance().shutdown();
}


extern "C" juce::MessageManager *getGlobalMessagerManager() {
    return juce::MessageManager::getInstanceWithoutCreating();
}
extern "C" bool existsAndIsLockedByCurrentThreadGlobal() {
    JUCE_ASSERT_MESSAGE_MANAGER_EXISTS
    return juce::MessageManager::existsAndIsLockedByCurrentThread();
}


extern "C" bool globalCall(std::function<void()> fn) {
    return juce::MessageManager::callAsync(fn);
}


