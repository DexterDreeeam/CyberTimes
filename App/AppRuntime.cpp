#include "AppRuntime.hpp"
#include "UserConfig.hpp"
#include "DataBase.hpp"
#include "VisionApp.hpp"
#include "Operator.hpp"

NS_BEG

void AppRuntime::OnInstantiate()
{
}

AppRuntime::AppRuntime() :
    m_system()
{
}

AppRuntime::~AppRuntime()
{
}

void AppRuntime::Load(const str& opJsonStr, const str& keyJsonStr)
{
    UserConfig::Ins()->Load(opJsonStr, keyJsonStr);
    DataBase::Ins()->Load();
    VisionApp::Ins()->Load(UserConfig::Ins()->m_system);
    Operator::Ins()->Load();
}

void AppRuntime::Loop(volatile bool& cancelToken)
{
    while (!cancelToken)
    {
        auto& stateArray = DataBase::Ins()->GetStateArray();
        VisionApp::Ins()->ScreenScan(stateArray);
        Operator::Ins()->Process();

        // remaining interval sleep
        // todo
    }
}

NS_END
