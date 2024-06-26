#pragma once

#include "common.hpp"

NS_BEG

class Operator : public InsBase<Operator>
{
    friend class InsBase;

public:
    virtual void OnInstantiate() override;
    ~Operator();

private:
    Operator();
    Operator(const Operator&) = delete;

public:
    void Load();
    void Unload();
    void Process();
};

NS_END
