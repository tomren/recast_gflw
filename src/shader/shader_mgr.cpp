#include "shader_mgr.hpp"
#include <stdio.h>

//const char* vertex_shader =
//"#version 440\n"
//"layout (location = 0) in vec3 vecPos;"
//"layout (location = 1) in vec3 vecCol;"
//"out vec3 framCol;"
//"void main() {"
//"  gl_Position.xyz = vecPos;"
//"  gl_Position.w = 1.0;"
//"  framCol = vecCol;"
//"}";
//
//const char* fragment_shader =
//"#version 440\n"
//"in vec3 framCol;"
//"out vec4 color;"
//"void main() {"
//"  color.xyz = framCol;"
//"  color.w = 1.0;"
//"}";

const char* vertex_shader =
"#version 330 core\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;"
"layout(location = 1) in vec2 vertexUV;"
"out vec2 UV;"
//"uniform mat4 MVP;"
"void main(){"
//"gl_Position =  MVP * vec4(vertexPosition_modelspace,1);"
"gl_Position =  vec4(vertexPosition_modelspace,1);"
"UV = vertexUV;"
"}";

const char* fragment_shader =
"#version 330 core\n"
"in vec2 UV;"
"out vec3 color;"
"uniform sampler2D myTextureSampler;"
"void main(){"
"color = texture( myTextureSampler, UV ).rgb;"
"}";

//const char* vertex_shader =
//"#version 440\n"
//"layout (location = 0) in vec3 vecPos;"
//"layout (location = 1) in vec2 vecUV;"
//"out vec2 UV;"
//"uniform mat4 MVP;"
//"void main() {"
//"  gl_Position = MVP * vec4(vecPos, 1);"
//"  UV = vecUV;"
//"}";

//const char* fragment_shader =
//"#version 440\n"
//"in vec2 UV;"
//"out vec3 color;"
//"uniform sampler2D tex;"
//"void main() {"
//"  color = texture(tex, UV).rgb"
//"}";

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
    GLint success;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (GL_FALSE == success)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(vs, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d:'%s'\n", GL_VERTEX_SHADER, InfoLog);
    }

    // 创建片段着色器
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (GL_FALSE == success)
    {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(vs, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d:'%s'\n", GL_FRAGMENT_SHADER, InfoLog);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (GL_FALSE == success)
    {
        GLchar InfoLog[1024];
        glGetProgramInfoLog(program, sizeof(InfoLog), NULL, InfoLog);
        fprintf(stderr, "Error linking shader program:'%s'\n", InfoLog);
    }

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
