#include "pch.h"
#include <iostream>

#include "JYWindow.h"
#include "Shader.h"
#include "DataMatrix.h"

const int win_width = 800;
const int win_height = 600;


using namespace DataStruct;
using namespace NJYWindow;


int main()
{
    // open data
    DataStruct::DataMatrix data_matrix("DemoMatrix.csv");

    JYWindow* window=JYWindow().GetPointer();    
    auto rec = window->CreatWindow(win_width, win_height, "testwindow",nullptr);
    if (rec == nullptr)
    {
        std::cout << "Fail to Creat Window" << std::endl;
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 

    Shader shader("shader.vs", "shader.fs");

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data_matrix.VerticesArray),data_matrix.VerticesArray,GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //todo

    

    while (!glfwWindowShouldClose(window->DisplayWindow))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window->DisplayWindow);
        glfwPollEvents();
    }
    window->Close();
    return 0;
}

