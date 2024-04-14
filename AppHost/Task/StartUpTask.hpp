#pragma once

#include "common.hpp"
#include "Task.hpp"

NS_BEG

class StartUpTask : public Task<StartUpTask>
{
public:
    StartUpTask();
    StartUpTask(const StartUpTask&) = delete;
    ~StartUpTask();

public:
    virtual void ImguiRenderHeader() override;
    virtual void ImguiRenderBody() override;
    virtual void ImguiRenderFoot() override;
    virtual void OnStart() override;
    virtual void OnFinish() override;

public:
    virtual TaskType Type() override { return TaskType::StartUp; }
};

NS_END
