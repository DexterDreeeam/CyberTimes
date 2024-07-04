#include "ScreenReader.hpp"
#include <Windows.h>

NS_BEG

void ScreenReader::OnInstantiate()
{
}

ScreenReader::ScreenReader() :
    m_handle(0),
    m_windowWidth(0),
    m_windowHeight(0),
    m_areaOriginX(0),
    m_areaOriginY(0),
    m_areaWidth(0),
    m_areaHeight(0),
    m_hdcWindow(0),
    m_hdcMem(0),
    m_hbm(0),
    m_pixels()
{
}

ScreenReader::~ScreenReader()
{
}

void ScreenReader::Load(u64 handle)
{
    Unload();

    RECT rect;
    GetClientRect((HWND)handle, &rect);
    m_handle = handle;
    m_windowWidth = abs(rect.right - rect.left);
    m_windowHeight = abs(rect.bottom - rect.top);
    m_areaOriginX = 0;
    m_areaOriginY = 0;
    m_areaWidth = m_windowWidth;
    m_areaHeight = m_windowHeight;
    m_hdcWindow = (u64)GetDC((HWND)m_handle);
    m_hdcMem = (u64)CreateCompatibleDC((HDC)m_hdcWindow);
    m_hbm = (u64)CreateCompatibleBitmap((HDC)m_hdcWindow, m_areaWidth, m_areaHeight);
    m_pixels.resize(m_areaWidth * m_areaHeight * 4);
    SelectObject((HDC)m_hdcMem, (HBITMAP)m_hbm);

    if (!CalculateArea())
    {
        Unload();
    }
}

void ScreenReader::Unload()
{
    if (m_hbm)
    {
        DeleteObject((HBITMAP)m_hbm);
        m_hbm = 0;
    }
    if (m_hdcMem)
    {
        DeleteDC((HDC)m_hdcMem);
        m_hdcMem = 0;
    }
    if (m_hdcWindow)
    {
        ReleaseDC((HWND)m_handle, (HDC)m_hdcWindow);
        m_hdcWindow = 0;
    }

    m_handle = 0;
    m_windowWidth = 0;
    m_windowHeight = 0;
    m_areaOriginX = 0;
    m_areaOriginY = 0;
    m_areaWidth = 0;
    m_areaHeight = 0;
    m_pixels.clear();
}

bool ScreenReader::CalculateArea()
{
    ScreenScan();
    int e = 0;
    u8 r, g, b;
    while (true)
    {
        if (ReadRgbChecked(e, e, r, g, b))
        {
            if (IsBorder(e, e))
            {
                ++e;
                break;
            }
        }
        else
        {
            return false;
        }
    }

    // search for right top corner from [e, e]
    int top = e;
    int right = e;
    while (true)
    {
        if (!IsBorder(top, right + 1))
        {
            break;
        }
        ++right;
    }

    // search for right bottom corner from [top, right]
    int bottom = top;
    while (true)
    {
        if (!IsBorder(bottom + 1, right))
        {
            break;
        }
        ++bottom;
    }

    // search for left bottom corner from [bottom, right]
    int left = right;
    while (true)
    {
        if (!IsBorder(bottom, left - 1))
        {
            break;
        }
        --left;
    }

    if (m_hdcWindow == 0 || m_hdcMem == 0)
    {
        return false;
    }

    m_areaOriginX = left;
    m_areaOriginY = top;
    m_areaWidth = right - left;
    m_areaHeight = bottom - top;
    if (m_hbm)
    {
        DeleteObject((HBITMAP)m_hbm);
        m_hbm = 0;
    }
    m_hbm = (u64)CreateCompatibleBitmap((HDC)m_hdcWindow, m_areaWidth, m_areaHeight);
    m_pixels.resize(m_areaWidth * m_areaHeight * 4);
    SelectObject((HDC)m_hdcMem, (HBITMAP)m_hbm);
    return true;
}

void ScreenReader::ScreenScan()
{
    BitBlt(
        // dst
        (HDC)m_hdcMem, 0, 0, m_areaWidth, m_areaHeight,
        // src
        (HDC)m_hdcWindow, m_areaOriginX, m_areaOriginY, SRCCOPY);

    BITMAPINFOHEADER bi =
    {
        sizeof(BITMAPINFOHEADER),
        m_areaWidth, -m_areaHeight,
        1, 32, BI_RGB, 0, 0, 0, 0, 0
    };
    GetDIBits(
        (HDC)m_hdcMem, (HBITMAP)m_hbm, 0, m_areaHeight,
        m_pixels.data(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
}

void ScreenReader::ReadRgb(int row, int col, u8& r, u8& g, u8& b)
{
    int idx = row * m_areaWidth + col;
    idx = idx << 2;
    r = m_pixels[idx + 2]; r = r < R1 ? 0 : r < R2 ? 1 : 2;
    g = m_pixels[idx + 1]; g = g < G1 ? 0 : g < G2 ? 1 : 2;
    b = m_pixels[idx];     b = b < B1 ? 0 : b < B2 ? 1 : 2;
}

bool ScreenReader::ReadRgbChecked(int row, int col, u8& r, u8& g, u8& b)
{
    int idx = row * m_areaWidth + col;
    idx = idx << 2;
    if (idx + 2 >= m_pixels.size())
    {
        return false;
    }
    r = m_pixels[idx + 2]; r = r < R1 ? 0 : r < R2 ? 1 : 2;
    g = m_pixels[idx + 1]; g = g < G1 ? 0 : g < G2 ? 1 : 2;
    b = m_pixels[idx];     b = b < B1 ? 0 : b < B2 ? 1 : 2;
    return true;
}

bool ScreenReader::IsBorder(int row, int col)
{
    u8 r, g, b;
    ReadRgb(row, col, r, g, b);
    return r == 0 && g == 2 && b == 0;
}

NS_END
