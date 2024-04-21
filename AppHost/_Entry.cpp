#include <Windows.h>
#include "TaskManager.hpp"
#include "Gui.hpp"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR lpCmdLine,
    int nCmdShow)
{
    ct::TaskManager::Ins();
    ct::Gui::Ins();

    ct::Gui::Deins();
    ct::TaskManager::Deins();
}
