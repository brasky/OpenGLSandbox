#pragma once

#include <GL\glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


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
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Clear() const;
};