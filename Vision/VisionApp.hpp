#pragma once

#include "common.hpp"

NS_BEG

class VisionApp : public InsBase<VisionApp>
{
    friend class InsBase;

public:
    virtual void OnInstantiate() override;
    ~VisionApp();

private:
    VisionApp();
    VisionApp(const VisionApp&) = delete;

public:
    void Load(const SystemConfig& system);
    void Unload();

public:
    bool ScreenScan(std_vvi& stateArray);

private:
    SystemConfig m_system;
};

NS_END
