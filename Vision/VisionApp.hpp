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
    bool ScreenScan(vvi& stateArray);
};

NS_END
