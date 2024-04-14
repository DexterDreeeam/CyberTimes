#pragma once

#include <Windows.h>
#include "TaskManager.hpp"
#include "StartUpTask.hpp"
#include "UserTokenInputTask.hpp"
#include "UserTokenVerifyingTask.hpp"

NS_BEG

void TaskManager::OnInstantiate()
{
    m_Worker = std::thread(&TaskManager::Life, this);
    m_Worker.detach();
}

TaskManager::TaskManager() :
    m_Worker(),
    m_CurrentTaskType(TaskType::None),
    m_NextTaskType(TaskType::StartUp),
    m_TaskMtx(),
    m_done(false)
{
}

TaskManager::~TaskManager()
{
    m_done = true;
    auto thread = m_Worker.native_handle();
    TerminateThread(thread, NULL);
    CloseHandle(thread);
}

void TaskManager::Life()
{
    while (true)
    {
        std::shared_ptr<TaskBase> t = nullptr;

        {
            std::lock_guard _lg(m_TaskMtx);
            m_CurrentTaskType = m_NextTaskType;
            m_NextTaskType = TaskType::None;
            t = CurrentTask();
        }

        if (!t)
        {
            return;
            throw "Current Task is null";
        }

        t->Start();
        t->Finish();
    }
}

void TaskManager::RegisterStart(TaskType taskType)
{

}

void TaskManager::OnTaskStart(TaskType taskType)
{

}

void TaskManager::OnTaskStarted(TaskType taskType)
{

}

void TaskManager::RegisterFinish(TaskType taskType)
{

}

void TaskManager::OnTaskFinish(TaskType taskType)
{

}

void TaskManager::OnTaskFinished(TaskType taskType)
{

}

void TaskManager::PrepareNextTask(TaskType taskType)
{
    std::lock_guard _lg(m_TaskMtx);
    m_NextTaskType = taskType;
}

std::shared_ptr<TaskBase> TaskManager::CurrentTask()
{
    switch (m_CurrentTaskType)
    {
    case TaskType::StartUp:
        return StartUpTask::Ins();
    case TaskType::UserTokenInput:
        return UserTokenInputTask::Ins();
    case TaskType::UserTokenVerifying:
        return UserTokenVerifyingTask::Ins();
    default:
        return nullptr;
    }
}

NS_END
