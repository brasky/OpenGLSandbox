#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
    Debug(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    Debug(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        Debug(glEnableVertexAttribArray(i));
        Debug(glVertexAttribPointer(i, element.count, element.type, element.normalized,
            layout.GetStride(), (const void*)offset)
        );
        offset += element.count * VertexBufferLayoutElement::GetTypeSize(element.type);
    }
}

void VertexArray::Bind() const
{
    Debug(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    Debug(glBindVertexArray(0));
}
