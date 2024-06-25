#include "JsonParser.hpp"
#include <.nlohmann/json.hpp>

using nj = nlohmann::json;

NS_BEG

nj::json* ToJsonPtr(void* p)
{
    return (nj::json*)p;
}

nj::json& ToJson(void* p)
{
    return *ToJsonPtr(p);
}

JsonParser::JsonParser(const str& opJson, const str& keyJson) :
    m_pOp(nullptr),
    m_pKey(nullptr)
{
    m_pOp = new char[sizeof(nj::json)];
    m_pKey = new char[sizeof(nj::json)];

    ToJson(m_pOp) = nj::parse(opJson);
    ToJson(m_pKey) = nj::parse(keyJson);
}

JsonParser::~JsonParser()
{
    if (m_pOp)
    {
        ToJsonPtr(m_pOp)->~json();
        delete[] m_pOp;
        m_pOp = nullptr;
    }
    if (m_pKey)
    {
        ToJsonPtr(m_pKey)->~json();
        delete[] m_pKey;
        m_pKey = nullptr;
    }
}

std_vvs JsonParser::GetStates()
{
    std_vvs states;
    auto& j = ToJson(m_pOp);
    if (j.contains("states") && j["states"].contains("rows"))
    {
        for (const auto& r : j["states"]["rows"])
        {
            std_vs sCol;
            for (const auto& c : r["cols"])
            {
                sCol.push_back(c.get<str>());
            }
            states.push_back(sCol);
        }
    }
    return states;
}

std_mss JsonParser::GetVars()
{
    std_mss vars;
    auto& j = ToJson(m_pOp);
    if (j.contains("vars"))
    {
        for (const auto& [k, v] : j["vars"].items())
        {
            vars[k] = v;
        }
    }
    return vars;
}

std_mss JsonParser::GetTriggers()
{
    std_mss triggers;
    auto& j = ToJson(m_pOp);
    if (j.contains("triggers"))
    {
        for (const auto& [k, v] : j["triggers"].items())
        {
            triggers[k] = v;
        }
    }
    return triggers;
}

std_vvs JsonParser::GetPipes()
{
    std_vvs pipes;
    auto& j = ToJson(m_pOp);
    if (j.contains("op_pipes"))
    {
        for (const auto& pipe : j["op_pipes"])
        {
            std_vs ops;
            for (const auto& op : pipe["ops"])
            {
                ops.push_back(op.get<str>());
            }
            pipes.push_back(ops);
        }
    }
    return pipes;
}

std_mss JsonParser::GetKeyMap()
{
    std_mss keyMap;
    auto& j = ToJson(m_pKey);
    for (const auto& [k, v] : j.items())
    {
        keyMap[k] = v.get<str>();
    }
    return keyMap;
}

NS_END
