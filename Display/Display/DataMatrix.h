#pragma once
namespace DataStruct
{
    class DataMatrix
    {
    public:
        DataMatrix(float data[], int rows, int cols,
            float xResolution, float yResolution) :DataPtr(data), Rows(rows), Cols(cols),
                                                    XResolution(XResolution), YResolution(yResolution)
        {
        };
        ~DataMatrix();

        unsigned int Rows;
        unsigned int Cols;
        float XResolution;
        float YResolution;
        float* DataPtr;

        float* ToArry()
        {          
            return DataPtr ;
        };

        DataMatrix* GetPtr()
        {
            return this;
        };

    private:
        float _data;
    };

}