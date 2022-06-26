#include "DemoClearColor.h"
#include "Renderer.h"
#include <ImGui/imgui.h>

namespace demo
{
    DemoClearColor::DemoClearColor()
        : m_ClearColor { 0.2f, 0.3f, 0.8f, 1.0f }
    {
    }
    DemoClearColor::~DemoClearColor()
    {
    }
    void DemoClearColor::OnUpdate(float deltaTime)
    {
    }
    void DemoClearColor::OnRender()
    {
        Debug(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
        Debug(glClear(GL_COLOR_BUFFER_BIT));
    }
    void DemoClearColor::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
}