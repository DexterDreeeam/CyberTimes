#pragma once

#include "common.hpp"

NS_BEG

class AppRuntime : public InsBase<AppRuntime>
{
    friend class InsBase;

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
    void AddWindowHandle(u64 handle);
    void OutputKey(const str& key);

private:
    bool LoadWindowHandles();

private:
    std::vector<u64>   m_handles;
    SystemConfig       m_system;
    std::mutex         m_runtimeLock;
    volatile bool      m_cancel;
};

NS_END
