#include <fstream>

class FileReader
{
private:
    int **allocateMatrix(int restrCount, int totalItemCount);
    void fillRestrMatrix(int **restrMatrix, int restrCount, std::ifstream *file);
public:
    FileReader(/* args */);
    ~FileReader();
    bool read();
};

FileReader::FileReader(/* args */)
{
}

FileReader::~FileReader()
{
}
