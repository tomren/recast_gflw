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

    int     Init();         // 初始化
    void    UnInit();

    void    Update();       // 更新

private:
    void    ShowVersion();  // 打印版本

    void    Load3DData();   // 加载 3D数据

    static void glfwErrorCallBack(int error, const char* description);

    enum
    {
        E_STATE_NONE = 0,
        E_STATE_INIT = 1
    };

    int             mState      = E_STATE_NONE;     // 状态
    // --------------------------------------------------
    int             mWinWidth   = 640;              // 窗口宽度
    int             mWinHeight  = 480;              // 窗口高度
    GLFWwindow*     mWindow     = NULL;             // 窗体
    bool            run         = false;            // 是否运行
    GLuint          vao, vbo;
    GLuint          program;
    GLint           mvp_location, vpos_location, vcol_location;
    GLuint          displayList;
};
