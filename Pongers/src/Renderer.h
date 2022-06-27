#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <functional>
#include <unordered_map>


#define STRINGIZE_DETAIL_(v) #v
#define STRINGIZE(v) STRINGIZE_DETAIL_(v)

#define Debug(x) glDebugMessageCallback(DebugCallback, (const void *)("\n" __FILE__ ":" STRINGIZE(__LINE__)));x

void DebugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);

class Renderer
{
public:
    Renderer(GLFWwindow& window);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
    void SetKeyCallback(std::vector<int> keys, std::function<void (int, int)> func);
    void RemoveKeyCallback(std::vector<int> keys);
private:
    GLFWwindow& m_Window;
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    std::unordered_map<int, std::function<void(int, int)>> m_KeyCallbacks;
};