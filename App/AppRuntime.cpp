#include <Windows.h>
#include "AppRuntime.hpp"
#include "AppDefinition.hpp"
#include "UserConfig.hpp"
#include "DataBase.hpp"
#include "VisionApp.hpp"
#include "Operator.hpp"

NS_BEG

void AppRuntime::OnInstantiate()
{
}

AppRuntime::AppRuntime() :
    m_handles(),
    m_system(),
    m_runtimeLock(),
    m_cancel(false)
{
}

AppRuntime::~AppRuntime()
{
}

void AppRuntime::Entry()
{
    if (!AppRuntime::Ins()->m_runtimeLock.try_lock())
    {
        throw new Ex("Runtime Lock retrieve failed");
    }

    AppRuntime::Ins()->m_cancel = false;
    try
    {
        AppRuntime::Ins()->Loop();
    }
    catch (...)
    {
        throw new Ex("AppRuntime::Entry running exception");
    }
    AppRuntime::Ins()->m_runtimeLock.unlock();
}

void AppRuntime::Cancel()
{
    AppRuntime::Ins()->m_cancel = true;
}

void AppRuntime::Load(const str& opJsonStr, const str& keyJsonStr)
{
    UserConfig::Ins()->Load(opJsonStr, keyJsonStr);
    DataBase::Ins()->Load();
    VisionApp::Ins()->Load(UserConfig::Ins()->m_system);
    Operator::Ins()->Load();

    std::thread t(AppRuntime::Entry);
}

void AppRuntime::Loop()
{
    using clock = std::chrono::high_resolution_clock;
    auto _iteration_clock = clock::now();

    while (!m_cancel)
    {
        int _interval = UserConfig::Ins()->m_system.cycle;
        if (_interval > 0)
        {
            auto _expected = _iteration_clock + std::chrono::milliseconds(_interval);
            auto _current = clock::now();
            if (_expected > _current)
            {
                std::this_thread::sleep_for(_expected - _current);
            }
        }

        _iteration_clock = clock::now();
        auto& stateArray = DataBase::Ins()->GetStateArray();
        VisionApp::Ins()->ScreenScan(stateArray);
        Operator::Ins()->Process();
    }
}

void AppRuntime::OutputKey(const str& key)
{
    for (auto h : m_handles)
    {
        unsigned char code = WinKeyMap[key];
        PostMessageA((HWND)h, WM_KEYDOWN, code, 0);
        PostMessageA((HWND)h, WM_KEYUP,   code, 0);
    }
}

wstr GetWindowTitle(HWND hwnd)
{
    int len = GetWindowTextLengthW(hwnd);
    if (len == 0)
    {
        return L"";
    }
    wstr s(len, '\0');
    GetWindowTextW(hwnd, s.data(), len + 1);
    return s;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    lParam;
    wstr title = GetWindowTitle(hwnd);
    for (const auto& titleSubstr : WindowTitles)
    {
        if (title.find(titleSubstr) != wstr::npos)
        {
            AppRuntime::Ins()->AddWindowHandle((u64)hwnd);
        }
    }
    return TRUE;
}

void AppRuntime::AddWindowHandle(u64 handle)
{
    m_handles.push_back(handle);
}

bool AppRuntime::LoadWindowHandles()
{
    m_handles.clear();
    EnumWindows(EnumWindowsProc, NULL);
    return m_handles.size() > 0;
}

NS_END
