#pragma once

#include "common.hpp"
#include "Task.hpp"

NS_BEG

class StoppedTask : public Task<StoppedTask>
{
public:
    StoppedTask();
    StoppedTask(const StoppedTask&) = delete;
    ~StoppedTask();

public:
    virtual void ImguiRenderHeader() override;
    virtual void ImguiRenderBody() override;
    virtual void ImguiRenderFoot() override;
    virtual void OnStart() override;
    virtual void OnFinish() override;
    virtual void Reset() override;

public:
    virtual TaskType Type() override { return TaskType::StartUp; }

private:
    std::mutex               m_ConfirmMtx;
    std::condition_variable  m_ConfirmCv;
    const char*              m_AppVersionStr;
    bool                     m_IsBack;
    bool                     m_IsToRun;
};

NS_END
