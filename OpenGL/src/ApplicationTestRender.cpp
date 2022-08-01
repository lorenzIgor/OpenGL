// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
//
// #include <iostream>
//
// #include "Renderer.h"
// #include "Shape.h"


int main2(void)
{
    // if (!glfwInit())
    //     return -1;
    //
    // const char* glsl_version = "#version 130";
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //
    // constexpr int windowSizeW = 1920;
    // constexpr int windowSizeH = 1080;
    //
    // GLFWwindow* window = glfwCreateWindow(windowSizeW, windowSizeH, "Hello World", nullptr, nullptr);
    //
    // if (!window)
    // {
    //     glfwTerminate();
    //     return -1;
    // }
    //
    // glfwMakeContextCurrent(window);
    // glfwSwapInterval(1);
    //
    // if(glewInit() != GLEW_OK)
    //     return -1;
    //
    // std::cout << glGetString(GL_VERSION) << std::endl;
    //     
    // {
    //     Renderer renderer;
    //     Shape shape("res/textures/sample.png");
    //     Shape shape2("res/textures/linux.png");
    //    
    //     renderer.AddShape(&shape);
    //     renderer.AddShape(&shape2);
    //     
    //     shape2.setPosition({5.0f, 0.0f, 1.0f});
    //     
    //     while (!glfwWindowShouldClose(window))
    //     {
    //         renderer.Clear();
    //         renderer.Draw();
    //
    //         glfwPollEvents();
    //         glfwSwapBuffers(window);
    //
    //     }
    // }
    //
    // glfwDestroyWindow(window);
    // glfwTerminate();
    return 0;
}
