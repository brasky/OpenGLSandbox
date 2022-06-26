#include "Renderer.h"
#include <string>
#include <iostream>

void DebugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    static std::string lastMessages[1];
    if (lastMessages->find(message, 0) == std::string::npos &&
        (severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_HIGH))
    {
        std::cout << message << ((const char*)userParam) << std::endl;
        lastMessages->append(message);
    }
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    Debug(glDrawElements(GL_TRIANGLES , ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    Debug(glClear(GL_COLOR_BUFFER_BIT));
}
