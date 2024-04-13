#include "cpp_std.hpp"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "imgui.h"

NS_BEG

class Gui
{
public:
    static std::shared_ptr<Gui> Ins();
    ~Gui();

private:
    Gui();
    Gui(const Gui&) = delete;

    void ImguiSetup();
    void ImguiLoop();
    void ImguiIterator(ImGuiIO& io);
    void ImguiDestroy();

private:
    WNDCLASSEX wc;
    HWND hwnd;
    std::thread loop;

    bool show_demo_window;
    bool show_another_window;
    ImVec4 clear_color;
};

NS_END
