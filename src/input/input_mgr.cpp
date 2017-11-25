#include "input_mgr.hpp"
#include <stdio.h>

// ==================================================
// ���캯��
// ==================================================
InputMgr::InputMgr()
{

}

// ==================================================
// ��������
// ==================================================
InputMgr :: ~InputMgr()
{

}

// ==================================================
// ���̻ص�
// ==================================================
void InputMgr::KeyboardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
