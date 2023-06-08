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
    // Constructor
    FileReader(/* args */);
    // Destructor
    ~FileReader();
    
    // Rellena la matriz izquierda de restricciones
    void fillRestrMatrix(unsigned int *restrMatrix, int restrCount);
    // Lee la linea que contiene la cantidad de elementos
    void readCountLine();
    // Getter de la cantidad de conductores
    int getDriverCount();
    // Getter de la cantidad de items
    int getItemCount();
    // Getter del tamaño del bote
    int getBoatSize();
    // Lee la cantidad máxima de restricciónes para la matriz
    int readRestrictionSize();
    // Abre el archivo
    bool openFile(const char *fileName);
};
