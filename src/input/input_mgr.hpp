extern "C"
{
#include <GLFW/glfw3.h>
}

class InputMgr
{
public:
    InputMgr();     // ���캯��
    ~InputMgr();    // ��������

    // ���̻ص�����
    static void KeyboardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
};
