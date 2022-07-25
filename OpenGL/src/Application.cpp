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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    constexpr int windowSizeW = 640;
    constexpr int windowSizeH = 480;
    
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
            -0.5f, -0.5f, 0.0f,  0.0f, //0
             0.5f, -0.5f, 1.0f,  0.0f, //1
             0.5f,  0.5f, 1.0f,  1.0f, //2
            -0.5f,  0.5f, 0.0f,  1.0f  //3
        };

        unsigned int indices_model_1[] = {
            0, 1 ,2,
            2, 3 ,0
        };

        float arrPosModel_2[]{
            -0.5f, -0.5f, //0
            -0.4f, -0.5f, //1
            -0.4f, -0.4f, //2
            -0.5f, -0.4f  //3
        };

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
        GLCall(glEnable(GL_BLEND))
        
        //Vertex Array Buffer
        VertexArray va1;
        const VertexBuffer vb(arrPosModel_1, sizeof(arrPosModel_1));
        VertexBufferLayout layout1;
        layout1.Push<float>(2);
        layout1.Push<float>(2);
        va1.AddBuffer(vb, layout1);

        // VertexArray va2;
        // const VertexBuffer vb2(arrPosModel_2, sizeof(arrPosModel_2));
        // VertexBufferLayout layout2;
        // layout2.Push<float>(2);
        // va2.AddBuffer(vb2, layout2);

        const IndexBuffer ib(indices_model_1, sizeof(indices_model_1) / sizeof(unsigned int));

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        
        Texture texture("res/textures/teste.png");
        texture.Bind(0);
        shader.SetUniforms1i("u_Texture", 0);
                
        Renderer renderer;
        
        float fRedColor = 0.0f;
        float fIncre = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            
            shader.SetUniforms4f("u_Color", fRedColor, 0.3f, 0.8f, 1.0f);
            renderer.Draw(va1, ib, shader);

            if (fRedColor > 1.0f)
                fIncre = -0.005f;
            else if (fRedColor < 0.0f)
                fIncre = 0.005f;
        
            fRedColor += fIncre;

            // shader.SetUniforms4f("u_Color", 1.0f - fRedColor, 0.3f, 0.8f, 1.0f);
            // renderer.Draw(va2, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            if (bye) break;
        }
    }

    glfwTerminate();
    return 0;
}