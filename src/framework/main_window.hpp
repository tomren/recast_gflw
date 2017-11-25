#define GLEW_STATIC
extern "C"
{
#include <GL/glew.h>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
}

class MainWindow
{
public:
    MainWindow();
    ~MainWindow();

    int     Init();         // ��ʼ��
    void    UnInit();

    void    Update();       // ����

private:
    void    ShowVersion();  // ��ӡ�汾

    void    Load3DData();   // ���� 3D����

    static void glfwErrorCallBack(int error, const char* description);

    enum
    {
        E_STATE_NONE = 0,
        E_STATE_INIT = 1
    };

    int             mState      = E_STATE_NONE;     // ״̬
    // --------------------------------------------------
    int             mWinWidth   = 640;              // ���ڿ��
    int             mWinHeight  = 480;              // ���ڸ߶�
    GLFWwindow*     mWindow     = NULL;             // ����
    bool            run         = false;            // �Ƿ�����
    GLuint          vao, vbo;
    GLuint          program;
    GLint           mvp_location, vpos_location, vcol_location;
    GLuint          displayList;
};
