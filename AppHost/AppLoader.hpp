#pragma once

#include "common.hpp"

NS_BEG

class AppLoader : public InsBase<AppLoader>
{
    friend class InsBase;

    typedef const char* (*FnVersion)();
    typedef bool (*FnStart)();
    typedef void (*FnFinish)();

public:
    virtual void OnInstantiate() override;
    ~AppLoader();

private:
    AppLoader();
    AppLoader(const AppLoader&) = delete;

public:
    void Load();
    void Unload();

    const char* Version();
    bool Start();
    void Finish();

private:
    u64        m_dllModule;
    FnVersion  m_appVersion;
    FnStart    m_appStart;
    FnFinish   m_appFinish;
};

NS_END
