#pragma once
#include "Screen.h"
class Window_mgr
{
public:
    using ScreenIndex = std::vector<Screen>::size_type;
public:
    Window_mgr();
    ~Window_mgr();

    void clear(ScreenIndex index);
private:
    std::vector<Screen> screens{ Screen(24, 80, ' ') };
};

inline void Window_mgr::clear(ScreenIndex index)
{
    screens[index].clear();
}