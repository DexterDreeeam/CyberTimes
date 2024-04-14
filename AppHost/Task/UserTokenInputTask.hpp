#pragma once

#include "common.hpp"
#include "Task.hpp"

NS_BEG

class UserTokenInputTask : public Task<UserTokenInputTask>
{
public:
    UserTokenInputTask();
    UserTokenInputTask(const UserTokenInputTask&) = delete;
    ~UserTokenInputTask();

public:
    virtual void ImguiRenderHeader() override;
    virtual void ImguiRenderBody() override;
    virtual void ImguiRenderFoot() override;
    virtual void OnStart() override;
    virtual void OnFinish() override;

public:
    virtual TaskType Type() override { return TaskType::UserTokenInput; }
};

NS_END
