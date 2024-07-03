#pragma once

#include "common.hpp"

NS_BEG

class AppRuntime : public InsBase<AppRuntime>
{
    friend class InsBase;

    static std::vector<wstr> WindowTitles;
    static std::unordered_map<str, unsigned char> WinKeyMap;

public:
    virtual void OnInstantiate() override;
    ~AppRuntime();

private:
    AppRuntime();
    AppRuntime(const AppRuntime&) = delete;

public:
    static void Entry();
    void Cancel();
    void Load(const str& opJsonStr, const str& keyJsonStr);
    void Loop();
    void OutputKey(const str& key);

private:
    static wstr GetWindowTitle(HWND hwnd);
    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
    bool LoadWindowHandles();

private:
    std::vector<u64>   m_handles;
    SystemConfig       m_system;
    std::mutex         m_runtimeLock;
    volatile bool      m_cancel;
};

#include "AppDefinition.hpp"

NS_END
