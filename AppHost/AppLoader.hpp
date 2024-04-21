#pragma once

#include "common.hpp"

NS_BEG

class AppLoader : public InsBase<AppLoader>
{
    friend class InsBase;

    typedef void (*FnStart)();
    typedef void (*FnFinish)();

public:
    virtual void OnInstantiate() override;
    ~AppLoader();

private:
    AppLoader();
    AppLoader(const AppLoader&) = delete;

    bool Load();
    void Unload();

private:
    HMODULE   m_dllModule;
    FnStart   m_appStart;
    FnFinish  m_appFinish;
};

NS_END
