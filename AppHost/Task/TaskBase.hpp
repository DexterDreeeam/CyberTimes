#pragma once

#include "common.hpp"
#include "TaskType.hpp"

NS_BEG

class TaskBase
{
    friend class TaskManager;

public:
    TaskBase() = default;

    virtual void ImguiRenderHeader() {}
    virtual void ImguiRenderBody() {}
    virtual void ImguiRenderFoot() {}
    virtual void OnStart() {}
    virtual void OnFinish() {}
    virtual TaskType Type() { return TaskType::None; };

protected:
    void Start();
    void Finish();
};

NS_END
