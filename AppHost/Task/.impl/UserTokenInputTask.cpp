#include <Windows.h>
#include "imgui.h"
#include "UserTokenInputTask.hpp"
#include "TaskManager.hpp"

NS_BEG

UserTokenInputTask::UserTokenInputTask() :
    Task(),
    m_FocusRender(false),
    m_UserToken(),
    m_ConfirmMtx(),
    m_ConfirmCv()
{
}

UserTokenInputTask::~UserTokenInputTask()
{
}

void UserTokenInputTask::ImguiRenderHeader()
{
    ImGui::SetWindowFontScale(1.2f);

    ImGui::BeginDisabled();
    ImGui::Button("Back", ImVec2(380.0f, 40.0f));
    ImGui::EndDisabled();

    ImGui::SameLine();

    if (ImGui::Button("Close", ImVec2(380.0f, 40.0f)))
    {
        PostQuitMessage(0);
    }
}

void UserTokenInputTask::ImguiRenderBody()
{
    ImGui::SetWindowFontScale(1.2f);

    const char* userTipStr = "Input User Token";
    ImVec2 textSize = ImGui::CalcTextSize(userTipStr);
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 textPosition(windowSize.x / 2, windowSize.y / 3);
    textPosition.x -= textSize.x / 2;
    textPosition.y -= textSize.y;
    ImGui::SetCursorPos(textPosition);
    ImGui::Text(userTipStr);

    if (m_FocusRender)
    {
        m_FocusRender = false;
        ImGui::SetKeyboardFocusHere(0);
    }
    ImGui::InputTextMultiline(
        "UserToken", m_UserToken, IM_ARRAYSIZE(m_UserToken), ImVec2(-1.0f, 120.0f));
}

void UserTokenInputTask::ImguiRenderFoot()
{
    ImGui::SetWindowFontScale(1.2f);

    if (ImGui::Button("Reset", ImVec2(380.0f, 40.0f)))
    {
        memset(m_UserToken, 0, sizeof(m_UserToken));
        m_FocusRender = true;
    }

    ImGui::SameLine();
    if (ImGui::Button("Confirm", ImVec2(380.0f, 40.0f)))
    {
        m_ConfirmCv.notify_all();
    }
}

void UserTokenInputTask::OnStart()
{
    m_FocusRender = true;

    std::unique_lock<std::mutex> _ul(m_ConfirmMtx);
    m_ConfirmCv.wait(_ul);
}

void UserTokenInputTask::OnFinish()
{
    TaskManager::Ins()->PrepareNextTask(TaskType::UserTokenVerifying);
}

NS_END
