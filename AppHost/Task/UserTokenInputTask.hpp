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

private:
    bool                    m_FocusRender;
    char                    m_UserToken[256];
    std::mutex              m_ConfirmMtx;
    std::condition_variable m_ConfirmCv;
};

NS_END
