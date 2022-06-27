#include "Pong.h"

namespace demo
{
    Pong::Pong(Renderer& renderer)
        : m_Renderer(renderer), 
        m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
        m_Translation1(200, 200, 0), 
        m_Translation2(200, 300, 0)
    {
        float paddlePositions[] = {
           0.0f, 0.0f, 0.0f, 0.0f, //0
            300.0f, 0.0f, 1.0f, 0.0f, //1
            300.0f, 50.0f, 1.0f, 1.0f, //2
            0.0f, 50.0f, 0.0f, 1.0f, //3
        };

        float ballPositions[] = {
           0.0f, 0.0f, 0.0f, 0.0f, //0
            50.0f, 0.0f, 1.0f, 0.0f, //1
            50.0f, 50.0f, 1.0f, 1.0f, //2
            0.0f, 50.0f, 0.0f, 1.0f, //3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(paddlePositions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_Shader->Bind();
        m_Texture = std::make_unique<Texture>("res/textures/galaxy.png");
        m_Shader->SetUniform1i("u_Texture", 0);

        auto keys = std::vector<int>{ GLFW_KEY_A, GLFW_KEY_D};
        m_Renderer.SetKeyCallback(keys, [=](int key, int action) {this->MovementCallback(key, action); });
    }

    Pong::~Pong()
    {
        auto keys = std::vector<int>{ GLFW_KEY_A, GLFW_KEY_D };
        m_Renderer.RemoveKeyCallback(keys);
    }

    void Pong::OnUpdate(float deltaTime)
    {
    }

    void Pong::OnRender()
    {
        Debug(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        Debug(glClear(GL_COLOR_BUFFER_BIT));

        m_Texture->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation1);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation2);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            m_Renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
    }
    void Pong::OnImGuiRender()
    {
        ImGui::Begin("Pong Demo");

        ImGui::SliderFloat3("Translation 1", &m_Translation1.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation 2", &m_Translation2.x, 0.0f, 960.0f);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    void Pong::MovementCallback(int inputKey, int action)
    {
        if (action != GLFW_RELEASE)
        {
            if (inputKey == GLFW_KEY_A)
            {
                std::cout << "LEFT" << std::endl;
                m_Translation1.x -= 10;
            }
            if (inputKey == GLFW_KEY_D)
            {
                std::cout << "RIGHT" << std::endl;
                m_Translation1.x += 10;
            }
        }
    }
}