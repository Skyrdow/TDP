
#include <fstream>

class FileReader
{
private:
    int *allocateMatrix(int restrCount, int totalItemCount);
    void fillRestrMatrix(unsigned int *restrMatrix, unsigned int restrCount, std::ifstream *file, bool isRightSide);
    void printBits(int N);
public:
    FileReader(/* args */);
    ~FileReader();
    bool read(unsigned int *restriccionesIzq, unsigned int *restriccionesDer, int *C, int *I, int *b, int *cantidadRestriccionesIzq, int *cantidadRestriccionesDer);

};
