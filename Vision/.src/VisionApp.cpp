#include "VisionApp.hpp"

NS_BEG

void VisionApp::OnInstantiate()
{
}

VisionApp::VisionApp() :
    m_system()
{
}

VisionApp::~VisionApp()
{
}

void VisionApp::Load(const SystemConfig& system)
{
    Unload();
    m_system = system;
}

void VisionApp::Unload()
{
}

bool VisionApp::ScreenScan(std_vvi& stateArray)
{
    // todo
    return true;
}

NS_END
