#include <Windows.h>
#include "imgui.h"
#include "StoppedTask.hpp"
#include "TaskManager.hpp"
#include "Apploader.hpp"

NS_BEG

StoppedTask::StoppedTask() :
    Task(),
    m_ConfirmMtx(),
    m_ConfirmCv(),
    m_AppVersionStr(""),
    m_IsBack(false),
    m_IsToRun(false)
{
}

StoppedTask::~StoppedTask()
{
}

void StoppedTask::ImguiRenderHeader()
{
    ImGui::SetWindowFontScale(1.2f);

    if (ImGui::Button("Back", ImVec2(380.0f, 40.0f)))
    {
        m_IsBack = true;
        m_ConfirmCv.notify_all();
    }

    ImGui::SameLine();

    if (ImGui::Button("Close", ImVec2(380.0f, 40.0f)))
    {
        PostQuitMessage(0);
    }
}

void StoppedTask::ImguiRenderBody()
{
    ImGui::SetWindowFontScale(2.0f);

    const char* verStr = m_AppVersionStr;
    ImVec2 textSize = ImGui::CalcTextSize(verStr);
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 textPosition(windowSize.x / 2, windowSize.y / 2);
    textPosition.x -= textSize.x / 2;
    textPosition.y -= textSize.y / 2;
    ImGui::SetCursorPos(textPosition);
    ImGui::Text(verStr);
}

void StoppedTask::ImguiRenderFoot()
{
    ImGui::BeginDisabled();
    ImGui::Button("Reset", ImVec2(380.0f, 40.0f));
    ImGui::EndDisabled();

    ImGui::SameLine();

    if (ImGui::Button("Start", ImVec2(380.0f, 40.0f)))
    {
        m_IsToRun = true;
        m_ConfirmCv.notify_all();
    }
}

void StoppedTask::OnStart()
{
    AppLoader::Ins()->Load();
    m_AppVersionStr = AppLoader::Ins()->Version();

    std::unique_lock<std::mutex> _ul(m_ConfirmMtx);
    m_ConfirmCv.wait(_ul);
}

void StoppedTask::OnFinish()
{
    if (m_IsBack)
    {
        AppLoader::Ins()->Unload();
        TaskManager::Ins()->PrepareNextTask(TaskType::UserTokenInput);
    }
    else if (m_IsToRun)
    {
        TaskManager::Ins()->PrepareNextTask(TaskType::Running);
    }
    else
    {
        throw new Ex("StoppedTask::OnFinish() error state");
    }
}

void StoppedTask::Reset()
{
    m_AppVersionStr = "";
    m_IsBack = false;
    m_IsToRun = false;
}

NS_END
