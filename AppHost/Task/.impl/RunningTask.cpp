#include <Windows.h>
#include "imgui.h"
#include "RunningTask.hpp"
#include "TaskManager.hpp"
#include "Apploader.hpp"

NS_BEG

RunningTask::RunningTask() :
    Task(),
    m_ConfirmMtx(),
    m_ConfirmCv()
{
}

RunningTask::~RunningTask()
{
}

void RunningTask::ImguiRenderHeader()
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

void RunningTask::ImguiRenderBody()
{
    ImGui::SetWindowFontScale(1.2f);

    const char* userTipStr = "Running...";
    ImVec2 textSize = ImGui::CalcTextSize(userTipStr);
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 textPosition(windowSize.x / 2, windowSize.y / 3);
    textPosition.x -= textSize.x / 2;
    textPosition.y -= textSize.y;
    ImGui::SetCursorPos(textPosition);
    ImGui::Text(userTipStr);
}

void RunningTask::ImguiRenderFoot()
{
    ImGui::SetWindowFontScale(1.2f);

    ImGui::BeginDisabled();
    ImGui::Button("Reset", ImVec2(380.0f, 40.0f));
    ImGui::EndDisabled();

    ImGui::SameLine();

    if (ImGui::Button("Stop", ImVec2(380.0f, 40.0f)))
    {
        m_ConfirmCv.notify_all();
    }
}

void RunningTask::OnStart()
{
    if (!AppLoader::Ins()->Load())
    {
        // todo
    }

    std::unique_lock<std::mutex> _ul(m_ConfirmMtx);
    m_ConfirmCv.wait(_ul);
}

void RunningTask::OnFinish()
{
    AppLoader::Ins()->Unload();
    TaskManager::Ins()->PrepareNextTask(TaskType::Stopped);
}

NS_END
