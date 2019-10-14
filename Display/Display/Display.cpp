#include "pch.h"
#include <iostream>
#include "includes/glad/glad.h"
#include "includes/GLFW/glfw3.h"
#include "Shader.h"

#include "DataMatrix.h"
using namespace DataStruct;

int main()
{   

    Shader shader("shader.vs", "shader.fs");
    return 0;
}

