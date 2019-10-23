#pragma once
#ifndef JY_WINDOW
#define  JY_WINDOW

#include "includes/glad/glad.h"
#include "includes/GLFW/glfw3.h"
#include "DataMatrix.h"
namespace NJYWindow {

    class JYWindow
    {
    public:
        JYWindow();
        ~JYWindow();

        JYWindow* GetPointer();
        GLFWwindow* CreatWindow(const int with, const int heigth, const char* title, DataMatrix * dataMatrix);
        void Display3D();
        void Close();

        GLFWwindow* DisplayWindow;
    private:
        void DestroyWindow();
    };
}
#endif // JY_WINDOW