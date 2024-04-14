#pragma once

#include "common.hpp"
#include <d3d12.h>
#include <dxgi1_4.h>
#include "imgui.h"

NS_BEG

class Gui : public InsBase<Gui>
{
    friend class InsBase;

public:
    virtual void OnInstantiate() override;
    ~Gui();

private:
    Gui();
    Gui(const Gui&) = delete;

    void ImguiLife();
    void ImguiSetup();
    void ImguiLoop();
    void ImguiIterator(ImGuiIO& io);
    void ImguiDestroy();

private:
    WNDCLASSEX        m_WindowCls;
    HWND              m_Window;
    ImGuiWindowFlags  m_WindowFlag;
    ImGuiWindowFlags  m_WindowBodyFlag;
    std::thread       m_Worker;
    ImVec4            m_Background;
};

NS_END
