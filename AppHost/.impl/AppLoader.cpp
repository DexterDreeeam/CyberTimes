#include "AppLoader.hpp"
#include <Windows.h>

NS_BEG

void AppLoader::OnInstantiate()
{
}

AppLoader::AppLoader() :
    m_dllModule(0),
    m_appStart(nullptr),
    m_appFinish(nullptr)
{
}

AppLoader::~AppLoader()
{
}

bool AppLoader::Load()
{
    if (m_dllModule)
    {
        throw new ct::Ex("App.dll already loaded");
    }

    m_dllModule = (u64)LoadLibrary("./App.dll");
    if (!m_dllModule)
    {
        return false;
    }

    m_appStart = reinterpret_cast<FnStart>(GetProcAddress((HMODULE)m_dllModule, "AppStart"));
    if (!m_appStart)
    {
        throw new ct::Ex("App.dll AppStart function load failed");
    }

    m_appFinish = reinterpret_cast<FnStart>(GetProcAddress((HMODULE)m_dllModule, "AppFinish"));
    if (!m_appFinish)
    {
        throw new ct::Ex("App.dll AppFinish function load failed");
    }

    m_appStart();
    return true;
}

void AppLoader::Unload()
{
    if (m_appFinish)
    {
        m_appFinish();
        m_appFinish = nullptr;
    }
    if (m_appStart)
    {
        m_appStart = nullptr;
    }
    if (m_dllModule)
    {
        FreeLibrary((HMODULE)m_dllModule);
        m_dllModule = 0;
    }
}

NS_END
