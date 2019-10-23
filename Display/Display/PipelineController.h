#pragma once
#ifndef PipelineController_H
#define PipelineController_H
#include "DataMatrix.h"

class PipelineController
{
public:
    PipelineController();
    ~PipelineController();

    void CreatWindow(const int width, const int height, DataMatrix* data_matrix);
    void DrawLoop();
    void Close();
};
#endif
