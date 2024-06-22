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

void AppLoader::Load()
{
    if (!m_dllModule)
    {
        m_dllModule = (u64)LoadLibrary("./App.dll");
    }
    if (!m_dllModule)
    {
        throw new ct::Ex("App.dll load failed");
    }

    m_appVersion = reinterpret_cast<FnVersion>(GetProcAddress((HMODULE)m_dllModule, "AppVersion"));
    if (!m_appVersion)
    {
        throw new ct::Ex("App.dll AppVersion function load failed");
    }

    m_appStart = reinterpret_cast<FnStart>(GetProcAddress((HMODULE)m_dllModule, "AppStart"));
    if (!m_appStart)
    {
        throw new ct::Ex("App.dll AppStart function load failed");
    }

    m_appFinish = reinterpret_cast<FnFinish>(GetProcAddress((HMODULE)m_dllModule, "AppFinish"));
    if (!m_appFinish)
    {
        throw new ct::Ex("App.dll AppFinish function load failed");
    }
}

void AppLoader::Unload()
{
    if (m_appFinish)
    {
        m_appFinish = nullptr;
    }
    if (m_appStart)
    {
        m_appStart = nullptr;
    }
    if (m_appVersion)
    {
        m_appVersion = nullptr;
    }
    if (m_dllModule)
    {
        FreeLibrary((HMODULE)m_dllModule);
        m_dllModule = 0;
    }
}

const char* AppLoader::Version()
{
    if (m_appVersion)
    {
        return m_appVersion();
    }
    else
    {
        return "";
    }
}

bool AppLoader::Start()
{
    if (m_appStart)
    {
        return m_appStart();
    }
    return false;
}

void AppLoader::Finish()
{
    if (m_appFinish)
    {
        m_appFinish();
    }
}

NS_END
