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
    ImGui::SetWindowFontScale(1.2f);
    bool click = ImGui::Button("Back", ImVec2(380.0f, 40.0f));
    ImGui::SameLine();
    bool click2 = ImGui::Button("Close", ImVec2(380.0f, 40.0f));
}

void StartUpTask::ImguiRenderBody()
{
    ImGui::SetWindowFontScale(1.2f);
    for (int i = 0; i < 100; ++i)
    {
        ImGui::Text("Are You OK?");
    }
}

void StartUpTask::ImguiRenderFoot()
{
    ImGui::SetWindowFontScale(1.2f);
    bool click = ImGui::Button("Reset", ImVec2(380.0f, 40.0f));
    ImGui::SameLine();
    bool click2 = ImGui::Button("Confirm", ImVec2(380.0f, 40.0f));
}

void StartUpTask::OnStart()
{
    // Sleep(3000);
    Sleep(INFINITE);
}

void StartUpTask::OnFinish()
{
    TaskManager::Ins()->PrepareNextTask(TaskType::UserTokenInput);
}

NS_END
