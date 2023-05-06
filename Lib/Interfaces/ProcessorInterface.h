//
// Created by Scott Cohen on 5/5/23.
//

#pragma once

#include "JuceHeader.h"


class ParameterManager;

class ProcessorInterface {

public:

    virtual ~ProcessorInterface() = default;

    virtual ParameterManager *getParameterManager() = 0;

    virtual AudioProcessor *getAudioProcessor() = 0;
};
