#include "DataBase.hpp"

NS_BEG

void DataBase::OnInstantiate()
{
}

DataBase::DataBase() :
    m_stateArray(),
    m_stateValues(),
    m_varValues()
{
}

DataBase::~DataBase()
{
}

void DataBase::Load()
{
    Unload();
    for (const auto& vs : UserConfig::Ins()->m_states)
    {
        for (const auto& s : vs)
        {
            m_stateValues[s] = 0;
        }
    }
    for (const auto& [k, v] : UserConfig::Ins()->m_varConditions)
    {
        m_varValues[k] = 0;
    }
}

void DataBase::Unload()
{
    m_stateArray = std_vvi();
    m_stateValues = std_msi();
    m_varValues = std_msi();
}

NS_END
