#include "include/creation/MessageManagerHelper.h"

template<typename T>
std::unique_ptr<T> createOnMessageThread(std::function<T *()> createFunction) {
//    juce::ScopedJuceInitialiser_GUI libraryInitialiser;
//    initializeJuce();
    std::cout << "[INSTANCE] CALL " << getGlobalMessagerManager() << std::endl;
//    if (createFunction != nullptr) {
//        assert(false);
//    }
    if (existsAndIsLockedByCurrentThreadGlobal()) {
        return std::unique_ptr<T>(createFunction());
    } else {
        std::promise<T *> promise;
        std::future<T *> future = promise.get_future();

        juce::MessageManager::callAsync([createFunction, &promise]() mutable {
            try {
                promise.set_value(createFunction());
            } catch (...) {
                promise.set_exception(std::current_exception());
            }
        });

        return std::unique_ptr<T>(future.get());
    }
}

template std::unique_ptr<juce::AudioProcessor>
createOnMessageThread(std::function<juce::AudioProcessor *()> createFunction);

template std::unique_ptr<juce::AudioProcessorEditor>
createOnMessageThread(std::function<juce::AudioProcessorEditor *()> createFunction);

template std::unique_ptr<juce::Slider>
createOnMessageThread(std::function<juce::Slider *()> createFunction);