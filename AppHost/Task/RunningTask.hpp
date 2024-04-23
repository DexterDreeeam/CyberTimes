#pragma once

#include "common.hpp"
#include "Task.hpp"

NS_BEG

class RunningTask : public Task<RunningTask>
{
public:
    RunningTask();
    RunningTask(const RunningTask&) = delete;
    ~RunningTask();

public:
    virtual void ImguiRenderHeader() override;
    virtual void ImguiRenderBody() override;
    virtual void ImguiRenderFoot() override;
    virtual void OnStart() override;
    virtual void OnFinish() override;

public:
    virtual TaskType Type() override { return TaskType::Running; }

private:
    std::mutex              m_ConfirmMtx;
    std::condition_variable m_ConfirmCv;
};

NS_END
