#pragma once

#include "common.hpp"
#include "UserConfig.hpp"

NS_BEG

class DataBase : public InsBase<DataBase>
{
    friend class InsBase;

public:
    virtual void OnInstantiate() override;
    ~DataBase();

private:
    DataBase();
    DataBase(const DataBase&) = delete;

public:
    void Load(const str& opJsonStr, const str& keyJsonStr);
    void Unload();
    std_vvi& GetStateArray();

public:
    UserConfig  m_config;
    std_vvi     m_stateArray;
    std_msi     m_stateValues;
    std_msi     m_varValues;
};

NS_END
