#pragma once

#include "common.hpp"
#include "TaskType.hpp"

NS_BEG

class TaskBase
{
    friend class TaskManager;

public:
    TaskBase() = default;

    virtual void ImguiRenderHeader() = 0;
    virtual void ImguiRenderBody() = 0;
    virtual void ImguiRenderFoot() = 0;
    virtual void OnStart() = 0;
    virtual void OnFinish() = 0;
    virtual TaskType Type() { return TaskType::None; };

protected:
    void Start();
    void Finish();
};

NS_END
