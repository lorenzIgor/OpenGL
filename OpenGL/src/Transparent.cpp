#define GLFW_EXPOSE_NATIVE_WIN32
#include <windows.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>

bool _exit1 = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        _exit1 = 1;
}

// change this to int main() to allow the console
int main1()
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    GLFWwindow* window;
    //int windowSizeW = 1920, windowSizeH = 1080;
    //int windowSizeW = 640, windowSizeH = 480;
    int windowSizeW = 320, windowSizeH = 240;
    // initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    int count, windowWidth, windowHeight, monitorX, monitorY;

    // I am assuming that main monitor is in the 0 position
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);
    // width: 75% of the screen
    windowWidth = static_cast<int>(videoMode->width / 1.5);
    // aspect ratio 16 to 9
    windowHeight = static_cast<int>(videoMode->height / 16 * 9);

    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);

    // set the visibility window hint to false for subsequent window creation
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    //glfwWindowHint(GLFW_REFRESH_RATE, 240);
    
    // create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(windowSizeW, windowSizeH, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    auto hwnd = glfwGetWin32Window(window);
    ShowWindow(hwnd, SW_HIDE);
    SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
    ShowWindow(hwnd, SW_SHOW);

    // make the window's context current
    glfwMakeContextCurrent(window);

    // reset the window hints to default
    glfwDefaultWindowHints();

    //glfwSetWindowPos(window,
    //    monitorX + (videoMode->width - windowWidth) / 2,
    //    monitorY + (videoMode->height - windowHeight) / 2);

    glfwSetWindowPos(window, 0, 0);
    //glfwSetWindowSize(window, 1920, 1080);

    // show the window
    glfwShowWindow(window);

    // uncomment following line to see the border of window
    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    glfwSetWindowAttrib(window, GLFW_FLOATING, GLFW_TRUE);

    float fAngle = 0.0f;
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        if (_exit1) break;

        // render
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glRotatef(fAngle, 0, 0, 1);
        glBegin(GL_QUADS);
        glColor3f(0, 0, 1);
        glVertex3f(-.5, -.5, -1);
        glColor3f(0, .5, 0);
        glVertex3f(.5, -.5, -1);
        glColor3f(.5, 0, 1);
        glVertex3f(.5, .5, -1);
        glColor3f(.5, .5, 0);
        glVertex3f(-.5, .5, -1);
        glEnd();

        fAngle += 0.01;  // at some point this will explote! overflow: put the corresponding of

        // swap front and back buffers
        glfwSwapBuffers(window);

        // poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}