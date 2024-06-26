#pragma once

#include "common.hpp"

NS_BEG

class AppRuntime : public InsBase<AppRuntime>
{
    friend class InsBase;

public:
    virtual void OnInstantiate() override;
    ~AppRuntime();

private:
    AppRuntime();
    AppRuntime(const AppRuntime&) = delete;

public:
    void Load(const str& opJsonStr, const str& keyJsonStr);
    void Loop(volatile bool& cancelToken);

private:
    SystemConfig m_system;
};

NS_END
