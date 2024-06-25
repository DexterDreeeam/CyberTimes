#include "DataBase.hpp"

NS_BEG

void DataBase::OnInstantiate()
{
}

DataBase::UserConfig() :
    m_config(),
    m_stateValues(),
    m_varValues()
{
}

DataBase::~DataBase()
{
}

void DataBase::Load(const str& opJsonStr, const str& keyJsonStr)
{
    Unload();
    m_config.Load(opJsonStr, keyJsonStr);
    for (const auto& vs : m_config.m_states.states)
    {
        for (const auto& s : vs)
        {
            m_stateValues[s] = 0;
        }
    }
    for (const auto& [k, v] : m_varConditions)
    {
        m_varValues[k] = 0;
    }
}

void DataBase::Unload()
{
    m_stateValues = std_msi();
    m_varValues = std_msi();
    m_config.Unload();
}

NS_END
