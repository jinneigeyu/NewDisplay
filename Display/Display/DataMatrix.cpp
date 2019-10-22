#include "DataMatrix.h"

namespace DataStruct
{
    DataMatrix::DataMatrix(const std::string filePath)
    {
        m_file_path = filePath;
        auto cstr = m_file_path.substr(m_file_path.find_last_of(".") + 1);

        if (m_file_path.empty() || cstr != "csv")
        {
            m_succes = false;
            return;
        }

        std::ifstream stream(m_file_path);
        stream.exceptions(std::ifstream::failbit);
        try
        {

            for (int i = 0; i < 2; i++)
            {

                if (i < 1)  continue;

                std::string  lin_str;
                getline(stream, lin_str);
                getline(stream, lin_str);
                std::vector<std::string> str_vec;
                str_vec = Split(lin_str, ",");
                this->XResolution = atof(str_vec[0].c_str());
                this->YResolution = atof(str_vec[1].c_str());
                this->Rows = atof(str_vec[2].c_str());
                this->Cols = atof(str_vec[3].c_str());

                float* data_arry = new float[Rows*Cols];

                int rows_cnt = 0;
                while (!stream.eof()&&getline(stream, lin_str))
                {
                    auto line_str_arry = Split(lin_str, ",");

                    for (int i = 0; i < line_str_arry.size(); i++)
                    {
                        int length = line_str_arry.size();
                        data_arry[i + rows_cnt * Cols] = atof(line_str_arry[i].c_str());
                    }
                    rows_cnt++;
                    if (rows_cnt==Rows)
                    {
                        break;
                    }
                }

                InputDataArry = data_arry;

                SetVerticesArry();
                SetVerticesIndex();
            }
        }
        catch (const std::exception& e)
        {
            std::cout
                << "ERROR::READ DATA FAILED:: "
                << "Resion��"
                << e.what()
                << std::endl;
            m_succes = false;
        }
    }

    DataMatrix::~DataMatrix()
    {

        /*delete[] InputDataArry;
        delete[] VerticesArry;
        delete[] ElementIndices;*/
    }

    float * DataMatrix::GetVerticesArry()
    {
        return VerticesArray;
    }

    unsigned  int * DataMatrix::GetElementIndices()
    {

        return ElementIndices;
    }

    std::vector <std::string> DataMatrix::Split(const std::string & str, const std::string & delim)
    {
        std::vector <std::string> res;
        if ("" == delim) return res;

        char* strs = new  char[str.length() + 1];
        strcpy(strs, str.c_str());
        char* d = new char[delim.length() + 1];
        strcpy(d, delim.c_str());

        char  * p = strtok(strs, d);
        while (p)
        {
            res.push_back(p);
            p = strtok(NULL, d);
        }

        return res;
    }

    void DataMatrix::SetVerticesArry()
    {
        float *temp_index = new float[Cols *Rows * 3];
        int index = 0;
        float mid_x_o = Rows / 2;
        float mid_y_o = Cols / 2;
        try
        {
            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Cols; j++)
                {
                    //index 0 1 2
                    temp_index[index++] = (j - mid_x_o) / mid_x_o;
                    temp_index[index++] = (j - mid_y_o) / mid_y_o;
                    temp_index[index++] = InputDataArry[j + i * Cols];
                }
            }
            this->VerticesArray = temp_index;
        }
        catch (const std::exception)
        {
            std::cout << "ERROR::SET_INDICES" << std::endl;
        }


    }
    
    /*
        x-----x-----x           ！！！！>  cols direction    5\0--------1
        |\    |\    |       |                              |        |
        | \   | \   |       |                              |        |
        |  \  |  \  |       | rows direction               4--------2/3
        |   \ |   \ |       V
        |    \|    \|
        x-----x-----x
        |\    |\    |
        | \   | \   |
        |  \  |  \  |
        |   \ |   \ |
        |    \|    \|
        x-----x-----x
    */
    void DataMatrix::SetVerticesIndex()
    {
        unsigned int* temp_indices = new unsigned int[(Cols - 1)*(Rows - 1) * 6];
        int index = 0;
        try
        {
            for (int i = 0; i < Rows - 1; i++)
            {
                for (int j = 0; j < Cols - 1; j++)
                {
                    //index 0 1 2
                    temp_indices[index++] = (j + 0) + (i + 0) * (Cols - 1);
                    temp_indices[index++] = (j + 1) + (i + 0) * (Cols - 1);
                    temp_indices[index++] = (j + 1) + (i + 1) * (Cols - 1);

                    //index 3 4 5 
                    temp_indices[index++] = (j + 0) + (i + 0) * (Cols - 1);
                    temp_indices[index++] = (j + 1) + (i + 0) * (Cols - 1);
                    temp_indices[index++] = (j + 1) + (i + 1) * (Cols - 1); 
                }
            }

            this->ElementIndices = temp_indices;
        }
        catch (const std::exception* e)
        {
            delete[]  temp_indices;
            std::cout << "ERROR::SET_INDICES" << std::endl;
        }
        delete[]  temp_indices;
    }
}
