#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Shape.h"
#include "Shader.h"
#include "TestClearColor.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <ft2build.h>
#include <map>

#include FT_FREETYPE_H

bool bye = false;

struct Quad
{
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::vec3 scale    = {0.0f, 0.0f, 0.0f};
    glm::vec3 speed    = {0.0f, 0.0f, 0.0f};

    float buffer[30] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f
    };

};

#define USE_MAIN_2

void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        bye = true;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void update(float dt);

#ifdef USE_MAIN_1

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
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback2);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if(glewInit() != GLEW_OK)
        return -1;

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    {
        float vertices[]{
            -1.0f, -1.0f, 0.0f, 0.0f, 
             1.0f, -1.0f, 1.0f, 0.0f, 
             1.0f,  1.0f, 1.0f, 1.0f, 
            -1.0f,  1.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1 ,2,
            2, 3 ,0
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
        GLCall(glEnable(GL_BLEND))
        
        //Vertex Array Buffer
        VertexArray va;
        const VertexBuffer vb(vertices, sizeof(vertices));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        const IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

        const glm::mat4 proj = glm::ortho(0.0f,
                                          static_cast<float>(windowSizeW),
                                          0.0f,
                                          static_cast<float>(windowSizeH), -1.0f, 1.0f);
        
        const glm::mat4 view = translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f ,0.0f));
        glm::vec3 translation = glm::vec3(static_cast<float>(windowSizeW) / 2, static_cast<float>(windowSizeH)/2 ,0);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

        /* Scale */
        float fScaleFactor = 0.5f;
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
        model =  glm::scale(model, scale);
        
        glm::mat4 mvp = proj * view * model;

        Shader shader("res/shaders/Basic1.glsl");
        
        shader.Bind();
        shader.SetUniforms4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.SetUniformsMat4f("u_MVP", mvp);
        
        Texture texture("res/textures/sample.png");
        texture.Bind(0);
        shader.SetUniforms1i("u_Texture", 0);
        shader.SetUniforms1i("u_HasTexture", 1);
                        
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
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        // Our state
        bool show_demo_window = false;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        float fDegrees = 0;

        test::Test* currTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currTest);
        currTest = testMenu;

        testMenu->Register<test::TestClearColor>("Clear Color");

                      
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            shader.Bind();
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
            
            renderer.Draw(va, ib, shader);
            
            /* Poll for and process events */
            glfwPollEvents();
            
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            
            ImGui::NewFrame();

            if(currTest)
            {
                currTest->OnUpdate(0.0f);
                currTest->OnRender();
                ImGui::Begin("Test");
                if(currTest != testMenu && ImGui::Button("<-"))
                {
                    delete currTest;
                    currTest = testMenu;
                }
                currTest->OnImGuiRender();
                ImGui::End();
            }
          
            // // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            // if (show_demo_window)
            //     ImGui::ShowDemoWindow(&show_demo_window);
            //
            // // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            // {
            //     static int btnCounter = 0;
            //
            //     ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            //
            //     ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            //     ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            //     ImGui::Checkbox("Another Window", &show_another_window);
            //
            //     ImGui::SliderFloat("TranslationX", &translation.x, 0.0f, (float)windowSizeW);            // Edit 1 float using a slider from 0.0f to 1.0f
            //     ImGui::SliderFloat("TranslationY", &translation.y, 0.0f, (float)windowSizeH);            // Edit 1 float using a slider from 0.0f to 1.0f
            //     
            //     ImGui::SliderFloat("Scale", &fScaleFactor, 0.0f, 5.0f);                                  // Edit 1 float using a slider from 0.0f to 1.0f
            //     ImGui::ColorEdit3("clear color", reinterpret_cast<float*>(&clear_color)); // Edit 3 floats representing a color
            //
            //     if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            //         btnCounter++;
            //     
            //     ImGui::SameLine();
            //     ImGui::Text("counter = %d", btnCounter);
            //
            //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            //     ImGui::End();
            // }
            //
            // // 3. Show another simple window.
            // if (show_another_window)
            // {
            //     ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            //     ImGui::Text("Hello from another window!");
            //     if (ImGui::Button("Close Me"))
            //         show_another_window = false;
            //     ImGui::End();
            // }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            if (bye) break;
        }
        delete currTest;
        if(currTest != testMenu)
            delete testMenu;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

#endif
#ifdef USE_MAIN_2

int main(void)
{

    if (!glfwInit())
        return -1;
    
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    constexpr int windowSizeW = 1920;
    constexpr int windowSizeH = 1080;
    
    GLFWwindow* window = glfwCreateWindow(windowSizeW, windowSizeH, "_h", nullptr, nullptr);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);
   
    if(glewInit() != GLEW_OK)
        return -1;

    char title [256];
    float avgDelta = 0.0f;
   
    std::cout << glGetString(GL_VERSION) << std::endl;
        
    {
        Renderer renderer;
        
        for(int i=0; i<100;i++)
        {
            Shape* shape = new Shape();
            renderer.AddShape(shape);

            float scale = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 20;
            float speed_y = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 8;
            float speed_x = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))) / 20;
            
            shape->setPosition({0.0f, -0.5f, 1.0f});
            shape->setScale({scale, scale, 1.0f});
            shape->setSpeed({speed_x, speed_y, 1.0f});            
        }

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;
        float maxTicks = 100;
        float ticks = maxTicks;
        while (!glfwWindowShouldClose(window))
        {
            // calculate delta time
            // --------------------
            float currentFrame = static_cast <float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            if(ticks++ >= maxTicks)
            {
                title [255] = '\0';
                snprintf ( title, 255, "[FPS: %3.2f]", avgDelta / maxTicks);            
                glfwSetWindowTitle(window, title);
                ticks = 0;
                avgDelta = 0;
            }else
            {
                avgDelta += (1 / deltaTime);
            }
            
            renderer.Clear();            
            processInput(window);
            update(deltaTime);
            
            for(auto& shape: renderer.getShapes())
            {
                auto _pos = shape->getPosition();
                
                if(_pos.y < -10.0f)
                {
                    float scale = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 20;
                    float speed_y = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) / 8;
                    float speed_x = ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))) / 20;
            
                    shape->setPosition({0.0f, -0.5f, 1.0f});
                    shape->setScale({scale, scale, 1.0f});
                    shape->setSpeed({speed_x, speed_y, 1.0f});
                    
                    _pos = shape->getPosition();
                }

                auto _speed = shape->getSpeed();
                
                _pos.x += _speed.x;
                _speed.y -= 0.00058f; 
                _pos.y += _speed.y;
                
                shape->setSpeed(_speed);
                shape->setPosition(_pos);
            }

            renderer.Draw();
            
            glfwPollEvents();
            glfwSwapBuffers(window);
    
        }

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

#endif


void update(float dt)
{
    // std::cout << dt << std::endl;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}