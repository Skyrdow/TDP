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

    void fillRestrMatrix(unsigned int *restrMatrix, int restrCount);
    void readCountLine();
    int getDriverCount();
    int getItemCount();
    int getBoatSize();
    int readRestrictionSize();
    bool openFile(const char *fileName);
};
