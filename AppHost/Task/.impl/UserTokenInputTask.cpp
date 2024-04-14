#include <Windows.h>
#include "imgui.h"
#include "UserTokenInputTask.hpp"
#include "TaskManager.hpp"

NS_BEG

UserTokenInputTask::UserTokenInputTask() :
    Task()
{
}

UserTokenInputTask::~UserTokenInputTask()
{
}

void UserTokenInputTask::ImguiRenderHeader()
{
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.1f, 0.5f, 1.0f));
    bool click = ImGui::Button("Back", ImVec2(300.0f, 40.0f));
    ImGui::PopStyleColor(1);
}

void UserTokenInputTask::ImguiRenderBody()
{
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.1f, 0.5f, 1.0f));
    bool click = ImGui::Button("Back", ImVec2(300.0f, 40.0f));
    ImGui::PopStyleColor(1);
}

void UserTokenInputTask::ImguiRenderFoot()
{
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.1f, 0.5f, 1.0f));
    bool click = ImGui::Button("Back", ImVec2(300.0f, 40.0f));
    ImGui::PopStyleColor(1);
}

void UserTokenInputTask::OnStart()
{
    Sleep(INFINITE);
}

void UserTokenInputTask::OnFinish()
{

}

NS_END
