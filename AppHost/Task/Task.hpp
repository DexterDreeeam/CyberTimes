#pragma once

#include "common.hpp"
#include "TaskType.hpp"
#include "TaskBase.hpp"

NS_BEG

class TaskManager;

template<typename TaskTy>
class Task : public TaskBase, public InsBase<TaskTy>
{
    friend class TaskManager;

public:
    Task() = default;
};

NS_END
