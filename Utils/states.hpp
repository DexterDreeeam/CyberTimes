#pragma once

#include "common.hpp"

NS_BEG

enum class Object : u64
{
    None,

    Target,
    Hover,

    Player,
    Party1,
    Party2,

    Enemy1,
    Enemy2,
    Enemy3,

    Pet1,
    Pet2,
    Pet3,
};

enum class State : u64
{
    None,

    IsTarget,
    IsFocus,
    IsExist,
    IsDead,
    IsAttackImmune,
    IsMegaImmune,
    IsChannelling,
    IsChannellingCrit,

    HealthPct,
    ManaPct,
};

NS_END
