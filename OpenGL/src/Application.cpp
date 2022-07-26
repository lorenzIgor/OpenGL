#include <windows.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

bool bye = false;

void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        bye = true;
}

int main(void)
{
    //ShowWindow(GetConsoleWindow(), SW_SHOW);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    constexpr int windowSizeW = 1920;
    constexpr int windowSizeH = 1080;
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(windowSizeW, windowSizeH, "Hello World", nullptr, nullptr);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Vsync Syncronized */
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback2);

    if(glewInit() != GLEW_OK)
        return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    {
        float arrPosModel_1[]{
            -1.0f, -1.0f, 0.0f, 0.0f, 
             1.0f, -1.0f, 1.0f, 0.0f, 
             1.0f,  1.0f, 1.0f, 1.0f, 
            -1.0f,  1.0f, 0.0f, 1.0f
        };

        unsigned int indices_model_1[] = {
            0, 1 ,2,
            2, 3 ,0
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
        GLCall(glEnable(GL_BLEND))
        
        //Vertex Array Buffer
        VertexArray va;
        const VertexBuffer vb(arrPosModel_1, sizeof(arrPosModel_1));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        const IndexBuffer ib(indices_model_1, sizeof(indices_model_1) / sizeof(unsigned int));

        // const glm::mat4 proj = glm::perspective(45.0f, static_cast<GLfloat>(windowSizeW) / static_cast<GLfloat>(windowSizeH), 1.0f, 150.0f);
        const glm::mat4 proj = glm::ortho(0.0f,
                                          static_cast<float>(windowSizeW),
                                          0.0f,
                                          static_cast<float>(windowSizeH), -1.0f, 1.0f);
        
        const glm::mat4 view = translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f ,1.0f));
        glm::vec3 translation = glm::vec3(static_cast<float>(windowSizeW) / 2, static_cast<float>(windowSizeH)/2 ,0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

        // model = glm::rotate(model, glm::radians(10.0f), glm::vec3(1, 0 ,0));
        /* Scale */
        float fScaleFactor = 0.5f;
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
        model =  glm::scale(model, scale);
        
        glm::mat4 mvp = proj * view * model;

        Shader shader("res/shaders/Basic.glsl");
        
        shader.Bind();
        shader.SetUniforms4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformsMat4f("u_MVP", mvp);
        
        Texture texture("res/textures/sample.png");
        texture.Bind(0);
        shader.SetUniforms1i("u_Texture", 0);
                
        Renderer renderer;

        shader.Unbind();
        vb.Unbind();
        va.Unbind();
        ib.Unbind();
        
        float fRedColor = 0.0f;
        float fIncre = 0.05f;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Our state
        bool show_demo_window = false;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        float fDegrees = 0; 
        
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear(clear_color.x, clear_color.y, clear_color.z);
            shader.Bind();
            renderer.Draw(va, ib, shader);
            
            model = glm::translate(glm::mat4(1.0f), translation);
            scale = glm::vec3(static_cast<float>(texture.GetWidth()) * fScaleFactor, static_cast<float>(texture.GetHeight()) * fScaleFactor, 1.0f);
            model =  glm::scale(model, scale);
            model = glm::rotate(model, glm::radians(fDegrees), glm::vec3(0, 0 ,-1));
            fDegrees += 0.1f;
            mvp = proj * view * model;            
            shader.SetUniforms4f("u_Color", fRedColor, 0.3f, 0.8f, 1.0f);
            shader.SetUniformsMat4f("u_MVP", mvp);
            
            if (fRedColor > 1.0f)
                fIncre = -0.005f;
            else if (fRedColor < 0.0f)
                fIncre = 0.005f;
            
            fRedColor += fIncre;

            /* Poll for and process events */
            glfwPollEvents();
            
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static int btnCounter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("TranslationX", &translation.x, 0.0f, (float)windowSizeW);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderFloat("TranslationY", &translation.y, 0.0f, (float)windowSizeH);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderFloat("Scale", &fScaleFactor, 0.0f, 5.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                
                ImGui::ColorEdit3("clear color", reinterpret_cast<float*>(&clear_color)); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    btnCounter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", btnCounter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            if (bye) break;
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}