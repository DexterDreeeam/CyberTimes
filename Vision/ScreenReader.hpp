#pragma once

#include "common.hpp"

NS_BEG

class ScreenReader : public InsBase<ScreenReader>
{
    friend class InsBase;

    const int R1 = 80;
    const int R2 = 160;
    const int G1 = 60;
    const int G2 = 120;
    const int B1 = 80;
    const int B2 = 160;

public:
    virtual void OnInstantiate() override;
    ~ScreenReader();

private:
    ScreenReader();
    ScreenReader(const ScreenReader&) = delete;

public:
    void Load(u64 handle);
    void Unload();

public:
    bool CalculateArea();
    void ScreenScan();
    void ReadRgb(int row, int col, u8& r, u8& g, u8& b);
    bool ReadRgbChecked(int row, int col, u8& r, u8& g, u8& b);
    bool IsBorder(int row, int col);

private:
    u64              m_handle;
    int              m_windowWidth;
    int              m_windowHeight;
    int              m_areaOriginX;
    int              m_areaOriginY;
    int              m_areaWidth;
    int              m_areaHeight;
    u64              m_hdcWindow;
    u64              m_hdcMem;
    u64              m_hbm;
    std::vector<u8>  m_pixels;
};

NS_END
