#pragma once

#include "common.hpp"

NS_BEG

class JsonParser
{
public:
    JsonParser(const str& opJson, const str& keyJson);
    ~JsonParser();

public:
    std_vvs GetStates();
    std_mss GetVars();
    std_mss GetTriggers();
    std_vvs GetPipes();
    std_mss GetKeyMap();

private:
    void* m_pOp;
    void* m_pKey;
};

NS_END
