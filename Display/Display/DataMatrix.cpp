#include "DataMatrix.h"
using namespace std;
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
            std::string  lin_str;
            vector<vector<string>> str_arry;
            while (getline(stream, lin_str))
            {

            }

        }
        catch (const std::exception& e)
        {
            std::cout
                << "ERROR::READ DATA FAILED"
                << "Resion£º"
                << e.what()
                << std::endl;
            m_succes = false;
        }
    }

    DataMatrix::~DataMatrix()
    {

    }
}
