#pragma once

#include "common.hpp"
#include "UserConfig.hpp"

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

private:
    static bool IsConstant(const str& s);
    void UpdateStateValues();
    int  InferValue(const str& var, const std_msi& states, const std_msi& vars);
    int  ProcessExpLogic(UserConfigExpOp op, int lhs, int rhs);
    void CalculateVariable(const str& var, const UserConfigExp& exp);
    void ExecutePipeline();
    void CastSkill(const str& skill, const std_mss& keys);
    void PressKey(const str& key);
};

NS_END
