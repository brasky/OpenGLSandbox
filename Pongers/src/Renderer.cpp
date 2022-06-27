#include "Renderer.h"
#include <string>
#include <iostream>
#include "GLFW\glfw3.h"

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

Renderer::Renderer(GLFWwindow& window)
    : m_Window(window)
{
    glfwSetWindowUserPointer(&window, this);
    glfwSetKeyCallback(&m_Window, &Renderer::key_callback);
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

void Renderer::SetKeyCallback(std::vector<int> keys, std::function<void(int, int)> function)
{
    for (auto key : keys)
        m_KeyCallbacks.insert(std::make_pair(key, function));
}

void Renderer::RemoveKeyCallback(std::vector<int> keys)
{
    for (auto key : keys)
        m_KeyCallbacks.erase(key);
}

void Renderer::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto& renderer = *static_cast<Renderer*>(glfwGetWindowUserPointer(window));
    
    auto keyMap = renderer.m_KeyCallbacks.find(key);
    if (keyMap == renderer.m_KeyCallbacks.end()) return;

    keyMap->second(key, action);
}