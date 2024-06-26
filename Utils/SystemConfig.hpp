#pragma once

#include "common.hpp"

NS_BEG

struct SystemConfig
{
    int cycle; // period of one process run
    str background_color; // render background color
    str origin_color; // render reset color
    int option_num; // bits count
};

NS_END
