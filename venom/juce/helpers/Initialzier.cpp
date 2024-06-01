#include "include/initializer/Initializer.h"

class JuceInitializer {
public:
    static JuceInitializer &getInstance() {
        static JuceInitializer instance;
        std::cout << "[INSTANCE] GET " << juce::MessageManager::getInstanceWithoutCreating() << std::endl;
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
    // Optional: Add code to properly shutdown JUCE if needed
    JuceInitializer::getInstance().shutdown();
}


extern "C" juce::MessageManager *getGlobalMessagerManager() {
    std::cout << "[INSTANCE] GLOBAL GET " << juce::MessageManager::getInstanceWithoutCreating() << " "
              << std::this_thread::get_id() << " "
              << juce::MessageManager::getInstanceWithoutCreating()->getCurrentMessageThread() << std::endl;
    return juce::MessageManager::getInstanceWithoutCreating();
}
extern "C" bool existsAndIsLockedByCurrentThreadGlobal() {
    JUCE_ASSERT_MESSAGE_MANAGER_EXISTS
    std::cout << "[INSTANCE] GLOBAL EXISTS " << juce::MessageManager::getInstanceWithoutCreating() << " "
              << std::this_thread::get_id() << " "
              << juce::MessageManager::getInstanceWithoutCreating()->getCurrentMessageThread() << std::endl;
    return juce::MessageManager::existsAndIsLockedByCurrentThread();
}


extern "C" bool globalCall(std::function<void()> fn) {
    std::cout << "[INSTANCE] GLOBAL CALL "
              << juce::MessageManager::getInstanceWithoutCreating()->getCurrentMessageThread() << " "
              << std::this_thread::get_id() << std::endl;
    return juce::MessageManager::callAsync(fn);
}


