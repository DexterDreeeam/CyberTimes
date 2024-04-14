#include <Windows.h>
#include "imgui.h"
#include "UserTokenVerifyingTask.hpp"
#include "TaskManager.hpp"

NS_BEG

UserTokenVerifyingTask::UserTokenVerifyingTask() :
    Task(),
    m_FocusRender(false),
    m_UserToken(),
    m_ConfirmMtx(),
    m_ConfirmCv()
{
}

UserTokenVerifyingTask::~UserTokenVerifyingTask()
{
}

void UserTokenVerifyingTask::ImguiRenderHeader()
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

void UserTokenVerifyingTask::ImguiRenderBody()
{
    ImGui::SetWindowFontScale(1.2f);

    const char* userTipStr = "Verifying...";
    ImVec2 textSize = ImGui::CalcTextSize(userTipStr);
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 textPosition(windowSize.x / 2, windowSize.y / 3);
    textPosition.x -= textSize.x / 2;
    textPosition.y -= textSize.y;
    ImGui::SetCursorPos(textPosition);
    ImGui::Text(userTipStr);
}

void UserTokenVerifyingTask::ImguiRenderFoot()
{
    ImGui::SetWindowFontScale(1.2f);

    ImGui::BeginDisabled();
    if (ImGui::Button("Reset", ImVec2(380.0f, 40.0f)))
    {
        memset(m_UserToken, 0, sizeof(m_UserToken));
        m_FocusRender = true;
    }

    ImGui::SameLine();
    if (ImGui::Button("Confirm", ImVec2(380.0f, 40.0f)))
    {
        TaskManager::Ins()->PrepareNextTask(TaskType::UserTokenVerifiedSucceed);
        m_ConfirmCv.notify_all();
    }
    ImGui::EndDisabled();
}

void UserTokenVerifyingTask::OnStart()
{
    m_FocusRender = true;

    Sleep(3000);
}

void UserTokenVerifyingTask::OnFinish()
{

}

NS_END
