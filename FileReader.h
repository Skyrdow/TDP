#include <fstream>

class FileReader
{
private:
    std::ifstream *inputFile;
    std::string countLine;
    int driverCount;
    int itemCount;
    int boatSize;

public:
    FileReader(/* args */);
    ~FileReader();

    void fillRestrMatrix(int **restrMatrix, int restrCount);
    void fillLeftMatrix(unsigned int *restrMatrix, int restrCount);
    void fillRightMatrix(unsigned int *restrMatrix, int restrCount);
    void readCountLine();
    int getDriverCount();
    int getItemCount();
    int getBoatSize();
    int readRestrictionSize();
    bool openFile(const char *fileName);
};
