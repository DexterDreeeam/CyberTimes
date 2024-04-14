#include <Windows.h>
#include "imgui.h"
#include "StartUpTask.hpp"
#include "TaskManager.hpp"

NS_BEG

StartUpTask::StartUpTask() :
    Task()
{
}

StartUpTask::~StartUpTask()
{
}

void StartUpTask::ImguiRenderHeader()
{
}

void StartUpTask::ImguiRenderBody()
{
    ImGui::SetWindowFontScale(2.0f);
    ImVec2 textSize = ImGui::CalcTextSize(AppTitleStr);
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 textPosition(windowSize.x / 2, windowSize.y / 2);
    textPosition.x -= textSize.x / 2;
    textPosition.y -= textSize.y / 2;
    ImGui::SetCursorPos(textPosition);
    ImGui::Text(AppTitleStr);
}

void StartUpTask::ImguiRenderFoot()
{
}

void StartUpTask::OnStart()
{
    Sleep(1500);
}

void StartUpTask::OnFinish()
{
    TaskManager::Ins()->PrepareNextTask(TaskType::UserTokenInput);
}

NS_END
