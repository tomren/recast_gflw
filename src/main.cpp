#include "framework/main_window.hpp"


int main(void)
{
    MainWindow win;

    int ret = win.Init();
    if (0 != ret)
        return ret;

    win.Update();

    return 0;
}
