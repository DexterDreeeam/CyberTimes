#include "Operator.hpp"
#include "UserConfig.hpp"
#include "DataBase.hpp"

NS_BEG

void Operator::OnInstantiate()
{
}

Operator::Operator()
{
}

Operator::~Operator()
{
}

void Operator::Load()
{
    Unload();
}

void Operator::Unload()
{
}

void Operator::Process()
{
    auto& var_condition = UserConfig::Ins()->m_varConditions;
    UpdateStateValues();
    for (const auto& var : UserConfig::Ins()->m_varInferOrder)
    {
        CalculateVariable(var, var_condition[var]);
    }
    ExecutePipeline();
}

bool Operator::IsConstant(const str& s)
{
    for (char c : s)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }
    return s.size() > 0;
}

void Operator::UpdateStateValues()
{
    auto& state_book = UserConfig::Ins()->m_states;
    auto& state_array = DataBase::Ins()->m_stateArray;
    auto& state_values = DataBase::Ins()->m_stateValues;
    for (int r = 0; r < state_array.size(); ++r)
    {
        auto& state_row = state_array[r];
        for (int c = 0; c < state_row.size(); ++c)
        {
            auto& name = state_book[r][c];
            state_values[name] = state_row[c];
        }
    }
}

int Operator::InferValue(const str& var, const std_msi& states, const std_msi& vars)
{
    auto iterState = states.find(var);
    if (iterState != states.end())
    {
        return iterState->second;
    }

    auto iterVar = vars.find(var);
    if (iterVar != vars.end())
    {
        return iterVar->second;
    }

    return -1;
}

int Operator::ProcessExpLogic(UserConfigExpOp op, int lhs, int rhs)
{
    switch (op)
    {
    case OP_GT:
        return lhs > rhs ? 1 : 0;
    case OP_LT:
        return lhs < rhs ? 1 : 0;
    case OP_GE:
        return lhs >= rhs ? 1 : 0;
    case OP_LE:
        return lhs <= rhs ? 1 : 0;
    case OP_EQ:
        return lhs == rhs ? 1 : 0;
    case OP_NE:
        return lhs != rhs ? 1 : 0;
    case OP_AND:
        return lhs > 0 && rhs > 0;
    case OP_OR:
        return lhs > 0 || rhs > 0;
    case OP_IS:
        return lhs;
    case OP_NOT:
        return lhs > 0 ? 0 : 1;
    default:
        return -1;
    }
}

void Operator::CalculateVariable(const str& var, const UserConfigExp& exp)
{
    auto& states = DataBase::Ins()->m_stateValues;
    auto& vars = DataBase::Ins()->m_varValues;
    int left = -1;
    int right = -1;

    // left
    const str& leftStr = exp.lhs;
    bool left_is_constant = IsConstant(leftStr);
    left = left_is_constant ?
        atoi(leftStr.c_str()) : InferValue(leftStr, states, vars);

    // right
    const str& rightStr = exp.rhs;
    bool right_is_constant = IsConstant(rightStr);
    right = right_is_constant ?
        atoi(rightStr.c_str()) : InferValue(rightStr, states, vars);

    if (left < 0)
    {
        throw new Ex("left < 0 when CalculateVariable");
    }

    int rst = ProcessExpLogic(exp.op, left, right);
    if (rst < 0)
    {
        throw new Ex("rst < 0 when CalculateVariable");
    }

    vars[var] = rst;
}

void Operator::ExecutePipeline()
{
    auto& vars = DataBase::Ins()->m_varValues;
    auto& pipes = UserConfig::Ins()->m_pipes;
    auto& triggers = UserConfig::Ins()->m_triggers;
    auto& keys = UserConfig::Ins()->m_keyMap;
    for (const auto& p : pipes)
    {
        for (const auto& v : p)
        {
            if (vars[v] > 0)
            {
                CastSkill(triggers[v], keys);
            }
        }
    }
}

void Operator::CastSkill(const str& skill, const std_mss& keys)
{
    auto iter = keys.find(skill);
    if (iter == keys.cend())
    {
        throw new Ex("iter == keys.cend() when CastSkill");
    }
    const auto& key = iter->second;
    PressKey(key);
}

void Operator::PressKey(const str& key)
{
    // todo
}

NS_END
