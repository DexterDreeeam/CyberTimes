#include "UserConfig.hpp"
#include "JsonParser.hpp"

NS_BEG

void UserConfig::OnInstantiate()
{
}

UserConfig::UserConfig() :
    m_states(),
    m_varConditions(),
    m_varInferOrder(),
    m_keyMap()
{
}

UserConfig::~UserConfig()
{
}

void UserConfig::Load(const str& opJsonStr, const str& keyJsonStr)
{
    Unload();
    JsonParser jp(opJsonStr, keyJsonStr);

    m_states.states = jp.GetStates();
    for (const auto& [k, v] : jp.GetVars())
    {
        m_varConditions[k] = ParseExpression(v);
    }
    for (const auto& [k, v] : jp.GetTriggers())
    {
        m_varConditions[k] = ParseExpression(v);
    }
    for (const auto& [k, v] : jp.GetKeyMap())
    {
        m_keyMap[k] = v;
    }
    ParseInferOrder();
}

void UserConfig::Unload()
{
    m_states = UserConfigStates();
    m_varConditions = std::map<str, UserConfigExp>();
    m_varInferOrder = std_vs();
    m_keyMap = std_mss();
}

bool UserConfig::IsConstant(const str& s)
{
    for (char c : s)
    {
        if (c >= '0' && c <= '9')
        {
            continue;
        }
        return false;
    }
    return s.size() > 0;
}

bool UserConfig::IsState(const str& s)
{
    return s.find("s-") == 0;
}

bool UserConfig::IsVar(const str& s)
{
    return s.find("v-") == 0;
}

UserConfigExpOp UserConfig::ParseOperator(const str& s)
{
    if      (s == ">")   return OP_GT;
    else if (s == "<")   return OP_LT;
    else if (s == ">=")  return OP_GE;
    else if (s == "<=")  return OP_LE;
    else if (s == "==")  return OP_EQ;
    else if (s == "!=")  return OP_NE;
    else if (s == "and") return OP_AND;
    else if (s == "or")  return OP_OR;
    else if (s == "is")  return OP_IS;
    else if (s == "not") return OP_NOT;
    else return NONE;
}

UserConfigExp UserConfig::ParseExpression(const str& s)
{
    UserConfigExp exp;
    std::regex binary_regex(R"((\S+)\s*(>|<|>=|<=|==|!=)\s*(\S+))");
    std::regex binary_logical_regex(R"((\S+)\s+(and|or)\s+(\S+))");
    std::regex unary_logical_regex(R"(\s*(is|not)\s+(\S+))");
    std::smatch match;
    if (std::regex_match(s, match, binary_regex))
    {
        exp.op = ParseOperator(match[2].str());
        exp.lhs = match[1].str();
        exp.rhs = match[3].str();
    }
    else if (std::regex_match(s, match, binary_logical_regex))
    {
        exp.op = ParseOperator(match[2].str());
        exp.lhs = match[1].str();
        exp.rhs = match[3].str();
    }
    else if (std::regex_match(s, match, unary_logical_regex))
    {
        exp.op = ParseOperator(match[1].str());
        exp.lhs = "";
        exp.rhs = match[2].str();
    }
    else {
        throw new Ex("Invalid expression format");
    }
    return exp;
}

std_vs UserConfig::ParseInferOrder()
{
    std::unordered_map<str, std::unordered_set<str>> graph;
    std::unordered_map<str, int> in_degree;
    std::stack<str> zero_in_degree;
    std_vs result;

    for (const auto& [var, exp] : m_varConditions)
    {
        in_degree[var] = 0;
        if (IsVar(exp.lhs))
        {
            graph[exp.lhs].insert(var);
            in_degree[var]++;
        }
        if (IsVar(exp.rhs))
        {
            graph[exp.rhs].insert(var);
            in_degree[var]++;
        }
    }

    for (const auto& [var, degree] : in_degree)
    {
        if (degree == 0)
        {
            zero_in_degree.push(var);
        }
    }

    while (!zero_in_degree.empty())
    {
        str var = zero_in_degree.top();
        zero_in_degree.pop();
        result.push_back(var);
        for (const auto& dependent_var : graph[var])
        {
            in_degree[dependent_var]--;
            if (in_degree[dependent_var] == 0)
            {
                zero_in_degree.push(dependent_var);
            }
        }
    }

    if (result.size() != m_varConditions.size())
    {
        throw new Ex("Cycle detected in variable dependencies");
    }
    return result;
}

NS_END
