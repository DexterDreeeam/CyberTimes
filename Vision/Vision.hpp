#pragma once

#include "common.hpp"

NS_BEG

class Vision : public InsBase<Vision>
{
    friend class InsBase;

public:
    virtual void OnInstantiate() override;
    ~Vision();

private:
    Vision();
    Vision(const Vision&) = delete;



};

NS_END
