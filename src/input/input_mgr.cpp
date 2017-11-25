#include "input_mgr.hpp"
#include <stdio.h>

// ==================================================
// 构造函数
// ==================================================
InputMgr::InputMgr()
{

}

// ==================================================
// 析构函数
// ==================================================
InputMgr :: ~InputMgr()
{

}

// ==================================================
// 键盘回调
// ==================================================
void InputMgr::KeyboardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
