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
};

NS_END
