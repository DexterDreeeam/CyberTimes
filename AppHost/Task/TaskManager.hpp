#pragma once

#include "common.hpp"
#include "TaskType.hpp"
#include "Task.hpp"

NS_BEG

class TaskBase;

class TaskManager : public InsBase<TaskManager>
{
    friend class InsBase;

public:
    void OnInstantiate();
    ~TaskManager();

private:
    TaskManager();
    TaskManager(const TaskManager&) = delete;

public:
    void Life();

    void RegisterStart(TaskType taskType);
    void OnTaskStart(TaskType taskType);
    void OnTaskStarted(TaskType taskType);

    void RegisterFinish(TaskType taskType);
    void OnTaskFinish(TaskType taskType);
    void OnTaskFinished(TaskType taskType);

    std::shared_ptr<TaskBase> CurrentTask();
    void PrepareNextTask(TaskType taskType);

private:
    std::thread       m_Worker;
    TaskType          m_CurrentTaskType;
    TaskType          m_NextTaskType;
    std::mutex        m_TaskMtx;
    std::atomic_bool  m_done;
};

NS_END
