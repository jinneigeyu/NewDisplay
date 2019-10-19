#include "JYWindow.h"
#include <iostream>

namespace NJYWindow {


    JYWindow::JYWindow()
    {
    }


    JYWindow::~JYWindow()
    {
       
    }

    JYWindow * JYWindow::GetPointer()
    {
        return this;
    }

    GLFWwindow * JYWindow::CreatWindow(const int with, const int heigth, const char * title,DataMatrix* dataMatrix)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
        this->DisplayWindow = glfwCreateWindow(with, heigth, title, nullptr, nullptr);

        if (DisplayWindow == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }
        glfwMakeContextCurrent(DisplayWindow);

        return DisplayWindow;
    }

    void JYWindow::Display3D()
    {
        //to do
    }

    void JYWindow::Close()
    {
        DestroyWindow();
    }

    void JYWindow::DestroyWindow()
    {
        glfwTerminate();
    }
}