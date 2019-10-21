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

                float* data_arry = new float[Rows*Cols * 3];
                float mid_x_o = Cols / 2;
                float mid_y_o = Rows / 2;
                int rows_cnt = 0;
                while (getline(stream, lin_str))
                {
                    auto line_str_arry = Split(lin_str, ",");

                    for (int i = 0; i < line_str_arry.size() ; i += 3)
                    {
                        data_arry[i + rows_cnt * Cols + 0] = (i - mid_x_o) / mid_x_o;
                        data_arry[i + rows_cnt * Cols + 1] = (rows_cnt - mid_y_o) / mid_y_o;
                        //failed
                        data_arry[i + rows_cnt * Cols + 2] = atof(line_str_arry[i].c_str());
                    }
                    rows_cnt++;
                }

                this->DataPtr = data_arry;
                delete[] data_arry;
                //SetVertices();

            }
        }
        catch (const std::exception& e)
        {
            std::cout
                << "ERROR::READ DATA FAILED"
                << "Resion��"
                << e.what()
                << std::endl;
            m_succes = false;
        }
    }

    DataMatrix::~DataMatrix()
    {

    }
  unsigned  int * DataMatrix::GetIndices()
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

    /*
        x-----x-----x           ！！！！>  cols direction    5\0    1
        |\    |\    |       |                              4    2/3
        | \   | \   |       |
        |  \  |  \  |       | rows direction
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
    void DataMatrix::SetVertices()
    {
        unsigned int *temp_index = new unsigned int[(Cols - 1)*(Rows - 1) * 6];

        try
        {
            for (int i = 0; i < Rows - 1; i++)
            {
                for (int j = 0; j < (Cols - 1) * 6; j += 6)
                {
                    //index 0 1 2
                    temp_index[j + i * (Cols - 1) + 0] = (j + 0) + i * (Cols - 1);
                    temp_index[j + i * (Cols - 1) + 1] = (j + 1) + i * (Cols - 1);
                    temp_index[j + i * (Cols - 1) + 2] = (j + 1) + (i + 1) * (Cols - 1);

                    //index 3 4 5
                    temp_index[j + i * (Cols - 1) + 3] = (j + 1) + (i + 1) * (Cols - 1);
                    temp_index[j + i * (Cols - 1) + 4] = (j + 0) + (i + 1) * (Cols - 1);
                    temp_index[j + i * (Cols - 1) + 5] = (j + 0) + i * (Cols - 1);
                }
            }
            ElementIndices = temp_index;
        }
        catch (const std::exception) 
        {
            delete[] temp_index;
            std::cout << "ERROR::SET_INDICES" << std::endl;
        }
        delete[] temp_index;


    }
}
