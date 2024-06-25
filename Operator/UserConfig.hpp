#pragma once

#include "common.hpp"

NS_BEG

class TaskBase;

class UserConfigStates
{
public:
    str     background_color;
    str     origin_color;
    int     option_num;
    std_vvs states;
};

enum UserConfigExpOp : int
{
    NONE,

    OP_GT,
    OP_LT,
    OP_GE,
    OP_LE,
    OP_EQ,
    OP_NE,

    OP_AND,
    OP_OR,

    OP_IS,
    OP_NOT,

    LAST,
    Num = LAST - 1
};

class UserConfigExp
{
public:
    str lhs;
    str rhs;
    UserConfigExpOp op;
};

class UserConfig : public InsBase<UserConfig>
{
    friend class InsBase;

public:
    virtual void OnInstantiate() override;
    ~UserConfig();

private:
    UserConfig();
    UserConfig(const UserConfig&) = delete;

public:
    void Load(const str& opJsonStr, const str& keyJsonStr);
    void Unload();

private:
    bool IsConstant(const str& s);
    bool IsState(const str& s);
    bool IsVar(const str& s);
    UserConfigExpOp ParseOperator(const str& s);
    UserConfigExp ParseExpression(const str& s);
    std_vs ParseInferOrder();

public:
    OpConfigStates               m_states;
    std::map<str, UserConfigExp> m_varConditions;
    std_vs                       m_varInferOrder;
    std_mss                      m_keyMap;
};

NS_END
