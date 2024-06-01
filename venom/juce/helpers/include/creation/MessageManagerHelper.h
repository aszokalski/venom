//
// Created by mszawerd on 01.06.24.
//

#ifndef _MESSAGEMANAGERHELPER_H
#define _MESSAGEMANAGERHELPER_H

#include <memory>
#include <functional>
#include "juce_events/juce_events.h"
#include "juce_audio_processors/juce_audio_processors.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "../initializer/Initializer.h"

template<typename T>
std::unique_ptr<T> createOnMessageThread(std::function<T *()> createFunction);

#endif //_MESSAGEMANAGERHELPER_H
