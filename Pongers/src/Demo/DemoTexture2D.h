#pragma once

#include "Demo.h"
#include "Renderer.h"
#include <ImGui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Texture.h>
#include <memory>

namespace demo
{
    class DemoTexture2D : public Demo
    {
    public:
        DemoTexture2D();
        ~DemoTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        
        glm::mat4 m_Proj, m_View;
        glm::vec3 m_Translation1, m_Translation2;
    };
}