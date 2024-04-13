#include <Windows.h>
#include "Gui.hpp"

int WINAPI WinMain(
    HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{
    auto gui = ct::Gui::Ins();
    gui;
}
