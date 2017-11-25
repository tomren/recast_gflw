#define GLEW_STATIC
extern "C"
{
#include <GL/glew.h>
#include <GLFW/glfw3.h>
}

class ShaderMgr
{
public:
    ShaderMgr();
    ~ShaderMgr();

    static GLint CreateShader();
};
