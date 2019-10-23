#pragma once
#ifndef DATA_MATRIX_H
#define DATA_MATRIX_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>




    class DataMatrix
    {
    public:
        DataMatrix(float data[], int rows, int cols,
            float xResolution, float yResolution) :InputDataArry(data), Rows(rows), Cols(cols),
            XResolution(XResolution), YResolution(yResolution)
        {
            m_data = true;
        };

        DataMatrix(const std::string filePaht);
        ~DataMatrix();

        unsigned int Rows;
        unsigned int Cols;
        
        float XResolution;
        float YResolution;

        float* InputDataArry;

        float* VerticesArray;
        int VerticesLength;
        unsigned int* ElementIndices;
        int ElementsLength;

        float* GetVerticesArry();
        unsigned int* GetElementIndices();

        void Disposs();
        DataMatrix* GetPtr()
        {
            if (m_succes)
            {
                return this;
            }
            return nullptr;
        };

    private:
        float m_data;
        std::string m_file_path;
        bool m_succes = false;
        std::vector <std::string> Split(const std::string & str, const std::string & delim);
        void SetVerticesArry();
        void SetVerticesIndex();
    };



#endif  //  DATA_MATRIX_H