#pragma once

#include "common.hpp"

NS_BEG

class ConfigRecorder : InsBase<ConfigRecorder>
{
public:
    ~ConfigRecorder();

private:
    ConfigRecorder();
    ConfigRecorder(const ConfigRecorder&) = delete;

public:
    void RegisterStart();
    void RegisterPause();
    void RegisterResume();
    void RegisterFinish();

private:
};

NS_END
