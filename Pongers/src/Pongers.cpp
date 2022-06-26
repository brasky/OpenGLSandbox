#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Pongers", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    const char* glsl_version = "#version 130";

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR!" << std::endl;
    };

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEBUG_OUTPUT);

    float positions[] = {
       -50.0f, -50.0f, 0.0f, 0.0f, //0
        50.0f,  -50.0f, 1.0f, 0.0f, //1
        50.0f, 50.0f, 1.0f, 1.0f, //2
        -50.0f, 50.0f, 0.0f, 1.0f, //3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexArray* va = new VertexArray();
    VertexBuffer* vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va->AddBuffer(*vb, layout);
    IndexBuffer* ib = new IndexBuffer(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Shader* shader = new Shader("res/shaders/Basic.shader");

    Texture texture("res/textures/galaxy.png");
    texture.Bind();
    shader->SetUniform1i("u_Texture", 0);

    va->Unbind();
    vb->Unbind();
    ib->Unbind();
    shader->Unbind();

    Renderer* renderer = new Renderer();

    glm::vec3 translation(200, 200, 0);
    glm::vec3 translation2(300, 300, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer->Clear();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shader->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
            glm::mat4 mvp = proj * view * model;
            shader->SetUniformMat4f("u_MVP", mvp);
            renderer->Draw(*va, *ib, *shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation2);
            glm::mat4 mvp = proj * view * model;
            shader->SetUniformMat4f("u_MVP", mvp);
            renderer->Draw(*va, *ib, *shader);
        }

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::SliderFloat3("Translation 1", &translation.x, 0.0f, 960.0f);
            ImGui::SliderFloat3("Translation 2", &translation2.x, 0.0f, 960.0f);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        //glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    //glDeleteProgram(shader);

    delete vb;
    delete va;
    delete ib;
    delete shader;
    delete renderer;

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}