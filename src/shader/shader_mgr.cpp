#include "shader_mgr.hpp"
#include <stdio.h>

const char* vertex_shader =
"#version 400\n"
"in vec3 vp;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"}";

const char* fragment_shader =
"#version 400\n"
"out vec4 color;"
"void main() {"
"  color = vec4(0.5, 0.0, 0.5, 1.0);"
"}";

// ==================================================
// 构造函数
// ==================================================
ShaderMgr::ShaderMgr()
{

}

// ==================================================
// 析构函数
// ==================================================
ShaderMgr :: ~ShaderMgr()
{

}

// ==================================================
// 创建着色器
// ==================================================
GLint ShaderMgr::CreateShader()
{
    // 创建定点着色器
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    // 创建片段着色器
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
