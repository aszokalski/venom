//
// Created by mszawerd on 31.05.24.
//

#ifndef _INITIALIZER_H
#define _INITIALIZER_H
#pragma once

#include <memory>
#include "juce_events/juce_events.h"

extern "C" {
void initializeJuce();
void shutdownJuce();
juce::MessageManager *getGlobalMessagerManager();
bool existsAndIsLockedByCurrentThreadGlobal();
bool globalCall(std::function<void()>);
}
#endif //_INITIALIZER_H
