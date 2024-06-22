#pragma once

#include "TaskBase.hpp"
#include "TaskManager.hpp"

NS_BEG

void TaskBase::Start()
{
     TaskManager::Ins()->OnTaskStart(Type());
     OnStart();
     TaskManager::Ins()->OnTaskStarted(Type());
}

void TaskBase::Finish()
{
    TaskManager::Ins()->OnTaskFinish(Type());
    OnFinish();
    TaskManager::Ins()->OnTaskFinished(Type());
}

NS_END
