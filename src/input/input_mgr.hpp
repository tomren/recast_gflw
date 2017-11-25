extern "C"
{
#include <GLFW/glfw3.h>
}

class InputMgr
{
public:
    InputMgr();     // 构造函数
    ~InputMgr();    // 析构函数

    // 键盘回调函数
    static void KeyboardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
};
