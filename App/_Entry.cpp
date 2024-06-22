#include "common.hpp"

extern "C" {
    __declspec(dllexport) const char* __cdecl AppVersion()
    {
        return "1.2.300";
    }

    __declspec(dllexport) bool __cdecl AppStart()
    {
        printf("123");
        return true;
    }

    __declspec(dllexport) void __cdecl AppFinish()
    {
        printf("456");
    }
}
