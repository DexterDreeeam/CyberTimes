#pragma once

#include "common.hpp"

NS_BEG

enum class TaskType : int
{
    None,

    StartUp,

    UserTokenInput,
    UserTokenVerifying,
    UserTokenVerifiedFailed,
    UserTokenVerifiedSucceed,

    AppUpdating,

    MonitorSelect,
    MonitorSelectFailed,

    WowFolderSetup,
    WowFolderSetupFailed,

    KeyboardSetup,

    Stopped,
    Running,
};

NS_END
