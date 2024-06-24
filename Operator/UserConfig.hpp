#pragma once

#include "common.hpp"

NS_BEG

class TaskBase;

class OpConfigStates
{
public:
    std::string                   background_color;
    std::string                   origin_color;
    int                           option_num;
    std::vector<std::vector<int>> states;
};

class OpConfigVarCondition
{
public:
    std::string lhs;
    std::string op;
    std::string rhs;
};

class OpConfig : public InsBase<OpConfig>
{
    friend class InsBase;

public:
    virtual void OnInstantiate() override;
    ~OpConfig();

private:
    OpConfig();
    OpConfig(const OpConfig&) = delete;

public:
    void Load(std::string jsonStr);

public:
    OpConfigStates                              m_states;
    std::map<std::string, int>                  m_stateValues;
    std::map<std::string, OpConfigVarCondition> m_varConditions;
    std::vector<std::string>                    m_varInferOrder;
    std::map<std::string, int>                  m_varValues;
};

class KeyConfig : public InsBase<KeyConfig>
{
    friend class InsBase;

public:
    virtual void OnInstantiate() override;
    ~KeyConfig();

private:
    KeyConfig();
    KeyConfig(const KeyConfig&) = delete;

public:
    void Load(std::string jsonStr);

public:
    std::map<std::string, std::string> m_keyMap;
}

NS_END
