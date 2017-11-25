#include "main_window.hpp"
#include "input/input_mgr.hpp"
#include "shader/shader_mgr.hpp"
#include <stdio.h>

float points[] = {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
};

MainWindow::MainWindow()
{

}

// ==================================================
// ��������
// ==================================================
MainWindow :: ~MainWindow()
{
    UnInit();
}

// ==================================================
// ��ʼ������
// ==================================================
int MainWindow::Init()
{
    // ���� GLFW ����Ļص�����
    glfwSetErrorCallback(glfwErrorCallBack);

    // ��ʼ�� GLFW
    if (!glfwInit())
        return -1;

    mState = E_STATE_INIT;

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                  // ���� OpenGL ���汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);                  // ���� OpenGL �ΰ汾��
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // MacOS �������ã�Windows ���Ժ���
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // ʹ�ú���ģʽ

                                                                    // ��������
    mWindow = glfwCreateWindow(mWinWidth, mWinHeight, "Hello World", NULL, NULL);
    if (!mWindow)
        return -1;

    // ��õ�ǰ����Ļ����Ϣ
    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if (NULL != videoMode)
    {
        int x = (videoMode->width - mWinWidth) >> 1;
        int y = (videoMode->height - mWinHeight) >> 1;
        // ���ô���λ��
        glfwSetWindowPos(mWindow, x, y);
    }

    // ���ð����ص�
    glfwSetKeyCallback(mWindow, InputMgr::KeyboardCallBack);

    // ���ɴ�����������Ϣ
    glfwMakeContextCurrent(mWindow);

    //// ���� GLAD
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //    return -1;

    // ���� GLEW
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        return -1;
    }

    ShowVersion();

    Load3DData();

    program = ShaderMgr::CreateShader();

    return 0;
}

// ==================================================
// ��ʾ�汾
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
// ���� 3D����
// ==================================================
void MainWindow::Load3DData()
{
    // ���������������
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // �������㻺�����
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
}

// ==================================================
// ж��
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
// ����
// ==================================================
void MainWindow::Update()
{
    int width, height;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(mWindow))
    {
        // ��õ�ǰ�Ӵ���С
        glfwGetFramebufferSize(mWindow, &width, &height);
        glViewport(0, 0, width, height);

        // ����
        glClearColor(0.0, 0.0, 0.0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        // ����������
        glfwSwapBuffers(mWindow);

        // ���� glfw �׳����¼�
        glfwPollEvents();
    }
}

void MainWindow::glfwErrorCallBack(int error, const char* description)
{
    printf("Error: '%s'\n", description);
}
