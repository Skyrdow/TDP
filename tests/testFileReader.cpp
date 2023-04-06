#include <iostream>
#include <string>
#include "../FileReader.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string nombreArchivo;

    cout << "Indique el nombre de archivo:  " ;
    cin >> nombreArchivo;
    FileReader *f = new FileReader();


    FileReader *fr = new FileReader();
    if (!fr->openFile(nombreArchivo.c_str()))
    {
        delete fr;
        return -1;
    }
    fr->readCountLine();

    cout << "driverCount " << fr->getDriverCount() << endl;
    cout << "itemCount " << fr->getItemCount() << endl;
    int totalItemCount = fr->getDriverCount() + fr->getItemCount();
    cout << "totalItemCount " << totalItemCount << endl;
    cout << "boatSize " << fr->getBoatSize() << endl;

    int leftRestrictionCount = fr->readRestrictionSize();
    unsigned int *leftRestrictionMatrix = new unsigned int[leftRestrictionCount];
    fr->fillRestrMatrix(leftRestrictionMatrix, leftRestrictionCount);

    int rightRestrictionCount = fr->readRestrictionSize();
    unsigned int *rightRestrictionMatrix = new unsigned int[rightRestrictionCount];
    fr->fillRestrMatrix(rightRestrictionMatrix, rightRestrictionCount);
    
    cout << endl;
    cout<<"Restricciones en formato entero:"<<endl;
    cout<<"Restricciones Izq:"<<endl;
    for(int i = 0; i < leftRestrictionCount; i++)
    {
        cout << leftRestrictionMatrix[i] << " ";
    }
    cout << endl;

    cout<<"Restricciones Der:"<<endl;
    for(int i = 0; i < rightRestrictionCount; i++)
    {
        cout << rightRestrictionMatrix[i] << " ";
    }
    cout << endl;
    delete fr;
    return 0;
}
