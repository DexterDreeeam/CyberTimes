#pragma once

#include "cpp_std.hpp"

NS_BEG

class Ex : public std::exception
{
public:
    Ex(const char* msg) :
        std::exception(msg)
    {
    }

    ~Ex() = default;
};

NS_END
