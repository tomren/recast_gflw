#include "main_window.hpp"
#include "input/input_mgr.hpp"
#include "shader/shader_mgr.hpp"
#include "texture/texture.hpp"
#include <stdio.h>

//float vectorBuffer[] =
//{
//    0.0f,  0.5f,  0.0f,
//    0.5f, -0.5f,  0.0f,
//    -0.5f, -0.5f,  0.0f
//};
//
//float colorBuffer[] =
//{
//    0.583f,  0.771f,  0.014f,
//    0.609f,  0.115f,  0.436f,
//    0.327f,  0.483f,  0.844f
//};

float vectorBuffer[] =
{
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

float uvBuffer[] =
{
    0.000059f, 1.0f - 0.000004f,
    0.000103f, 1.0f - 0.336048f,
    0.335973f, 1.0f - 0.335903f,
    1.000023f, 1.0f - 0.000013f,
    0.667979f, 1.0f - 0.335851f,
    0.999958f, 1.0f - 0.336064f,
    0.667979f, 1.0f - 0.335851f,
    0.336024f, 1.0f - 0.671877f,
    0.667969f, 1.0f - 0.671889f,
    1.000023f, 1.0f - 0.000013f,
    0.668104f, 1.0f - 0.000013f,
    0.667979f, 1.0f - 0.335851f,
    0.000059f, 1.0f - 0.000004f,
    0.335973f, 1.0f - 0.335903f,
    0.336098f, 1.0f - 0.000071f,
    0.667979f, 1.0f - 0.335851f,
    0.335973f, 1.0f - 0.335903f,
    0.336024f, 1.0f - 0.671877f,
    1.000004f, 1.0f - 0.671847f,
    0.999958f, 1.0f - 0.336064f,
    0.667979f, 1.0f - 0.335851f,
    0.668104f, 1.0f - 0.000013f,
    0.335973f, 1.0f - 0.335903f,
    0.667979f, 1.0f - 0.335851f,
    0.335973f, 1.0f - 0.335903f,
    0.668104f, 1.0f - 0.000013f,
    0.336098f, 1.0f - 0.000071f,
    0.000103f, 1.0f - 0.336048f,
    0.000004f, 1.0f - 0.671870f,
    0.336024f, 1.0f - 0.671877f,
    0.000103f, 1.0f - 0.336048f,
    0.336024f, 1.0f - 0.671877f,
    0.335973f, 1.0f - 0.335903f,
    0.667969f, 1.0f - 0.671889f,
    1.000004f, 1.0f - 0.671847f,
    0.667979f, 1.0f - 0.335851f
};

// ==================================================
// 构造函数
// ==================================================
MainWindow::MainWindow()
{

}

// ==================================================
// 析构函数
// ==================================================
MainWindow :: ~MainWindow()
{
    UnInit();
}

// ==================================================
// 初始化窗口
// ==================================================
int MainWindow::Init()
{
    // 设置 GLFW 错误的回调函数
    glfwSetErrorCallback(glfwErrorCallBack);

    // 初始化 GLFW
    if (!glfwInit())
        return -1;

    mState = E_STATE_INIT;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                  // 设置 OpenGL 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);                  // 设置 OpenGL 次版本号
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // MacOS 必须设置，Windows 可以忽略
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 使用核心模式

                                                                    // 创建窗体
    mWindow = glfwCreateWindow(mWinWidth, mWinHeight, "Hello World", NULL, NULL);
    if (!mWindow)
        return -1;

    // 获得当前主屏幕的信息
    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if (NULL != videoMode)
    {
        int x = (videoMode->width - mWinWidth) >> 1;
        int y = (videoMode->height - mWinHeight) >> 1;
        // 设置窗体位置
        glfwSetWindowPos(mWindow, x, y);
    }

    // 设置按键回调
    glfwSetKeyCallback(mWindow, InputMgr::KeyboardCallBack);

    // 生成窗体上下文信息
    glfwMakeContextCurrent(mWindow);

    //// 加载 GLAD
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //    return -1;

    // 加载 GLEW
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        return -1;
    }

    ShowVersion();

    Load3DData();

    programID = ShaderMgr::CreateShader();
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    return 0;
}

// ==================================================
// 显示版本
// ==================================================
void MainWindow::ShowVersion()
{
    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
}

// ==================================================
// 加载 3D数据
// ==================================================
void MainWindow::Load3DData()
{
    // 创建顶点数组对象
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // 创建顶点缓冲对象
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vectorBuffer), vectorBuffer, GL_STATIC_DRAW);

    // 创建颜色缓冲对象
    //glGenBuffers(1, &cbo);
    //glBindBuffer(GL_ARRAY_BUFFER, cbo);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(colorBuffer), colorBuffer, GL_STATIC_DRAW);

    // uv 缓冲区对象
    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvBuffer), uvBuffer, GL_STATIC_DRAW);

    // 创建贴图对象
    textureID = loadDDS("1.dds");
}

// ==================================================
// 卸载
// ==================================================
void MainWindow::UnInit()
{
    if (E_STATE_INIT != mState)
        return;

    if (NULL != mWindow)
    {
        glfwDestroyWindow(mWindow);
        mWindow = NULL;
    }

    glfwTerminate();

    mState = E_STATE_NONE;
}

// ==================================================
// 更新
// ==================================================
void MainWindow::Update()
{
    int width, height;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mWindow))
    {
        // 获得当前视窗大小
        glfwGetFramebufferSize(mWindow, &width, &height);
        glViewport(0, 0, width, height);

        // 清屏
        glClearColor(0.0, 0.0, 0.0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 使用 shader
        glUseProgram(programID);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glUniform1i(textureID, 0);

        // 启用定点属性
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // 启用颜色属性
        //glEnableVertexAttribArray(1);
        //glBindBuffer(GL_ARRAY_BUFFER, cbo);
        //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbo);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // 绘制三角形
        glDrawArrays(GL_TRIANGLES, 0, 12*3);

        // 关闭属性
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // 交换缓冲区
        glfwSwapBuffers(mWindow);

        // 处理 glfw 抛出的事件
        glfwPollEvents();
    }
}

void MainWindow::glfwErrorCallBack(int error, const char* description)
{
    printf("Error: '%s'\n", description);
}
