#pragma once
#ifndef JY_WINDOW
#define  JY_WINDOW

#include "includes/glad/glad.h"
#include "includes/GLFW/glfw3.h"

namespace NJYWindow {
    class JYWindow
    {
    public:
        JYWindow();
        ~JYWindow();

        JYWindow* GetPointer();
        GLFWwindow* CreatWindow(const int with, const int heigth, const char* title);
        void DestroyWindow();
        GLFWwindow* DisplayWindow;
   
    };
}
#endif // JY_WINDOW