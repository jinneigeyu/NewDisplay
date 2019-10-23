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

        std::ifstream csv_input(m_file_path);
        csv_input.exceptions(std::ifstream::failbit);
        try
        {

            for (int i = 0; i < 2; i++)
            {

                if (i < 1)  continue;

                //±íÍ·
                std::string  lin_str;
                getline(csv_input, lin_str);
                getline(csv_input, lin_str);               

                std::istringstream readstr(lin_str);
                std::string part_str;

                //read and set xpitch ypitch
                getline(readstr, part_str, ',');
                this->XResolution = atof(part_str.c_str());
                getline(readstr, part_str, ',');
                this->YResolution = atof(part_str.c_str());
                getline(readstr, part_str, ',');
                this->Rows = atof(part_str.c_str());
                getline(readstr, part_str, ',');
                this->Cols = atof(part_str.c_str());

                //creat raw data buffer
                InputDataArry = new float[Rows*Cols];
                
                for (int i = 0; i < Rows; i++)
                {
                    getline(csv_input, lin_str);
                    std::istringstream read_line_str(lin_str);
                    for (int j = 0; j < Cols; j++)
                    {
                        // one by one read into data buffer,fix the empty data ues nan 
                        getline(read_line_str, part_str, ',');
                        InputDataArry[j + i * Cols] = part_str == "" ? NAN : atof(part_str.c_str());
                    }
                }

                SetVerticesArry();
                SetVerticesIndex();
            }
        }
        catch (const std::exception& e)
        {
            std::cout
                << "ERROR::READ DATA FAILED:: "
                << "Resion£º"
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

    void DataMatrix::Disposs()
    {
        delete[] this->ElementIndices;
        ElementIndices = nullptr;
        delete[] this->VerticesArray;
        VerticesArray = nullptr;
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
        VerticesLength = Cols * Rows * 3;
        VerticesArray = new float[VerticesLength];
        
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
                    VerticesArray[index++] = (j - mid_x_o) / mid_x_o;
                    VerticesArray[index++] = (j - mid_y_o) / mid_y_o;
                    VerticesArray[index++] = InputDataArry[j + i * Cols];
                }
            }
            
        }
        catch (const std::exception)
        {
            std::cout << "ERROR::SET_INDICES" << std::endl;
        }


    }

    /*
        x-----x-----x           ¡ª¡ª¡ª¡ª>  cols direction    5\0--------1
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
        ElementsLength = (Cols - 1)*(Rows - 1) * 6;
        ElementIndices = new unsigned int[ElementsLength];
        int index = 0;
        try
        {
            for (int i = 0; i < Rows - 1; i++)
            {
                for (int j = 0; j < Cols - 1; j++)
                {
                    //index 0 1 2
                    ElementIndices[index++] = (j + 0) + (i + 0) * (Cols - 1);
                    ElementIndices[index++] = (j + 1) + (i + 0) * (Cols - 1);
                    ElementIndices[index++] = (j + 1) + (i + 1) * (Cols - 1);

                    //index 3 4 5 
                    ElementIndices[index++] = (j + 0) + (i + 0) * (Cols - 1);
                    ElementIndices[index++] = (j + 1) + (i + 0) * (Cols - 1);
                    ElementIndices[index++] = (j + 1) + (i + 1) * (Cols - 1);
                }
            }

        }
        catch (const std::exception* e)
        {
            std::cout << "ERROR::SET_INDICES" << std::endl;
        }
        
    }
}
