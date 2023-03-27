#include "RiverCrossing.h"
#include "FileReader.h"
#include <iostream>
#include <bitset>

using namespace std;

RiverCrossing::RiverCrossing(){}

void RiverCrossing::printInfo()
{
    cout<<"Restricciones Izq:"<<endl;
    for(int i = 0; i < leftRestrictionCount; i++)
    {
        std::bitset<sizeof(int)*8> A = leftRestrictionMatrix[i]; 
        cout << A << endl;
    }
    cout << endl;

    cout<<"Restricciones Der:"<<endl;
    for(int i = 0; i < rightRestrictionCount; i++)
    {
        std::bitset<sizeof(int)*8> A = rightRestrictionMatrix[i];
        cout << A << endl;
    }
    cout << endl;
}

void RiverCrossing::calculateFinalState(int totalItemCount)
{
    unsigned int finalState = 0;
    for (int i = 0; i < totalItemCount; i++)
    {
        finalState += 1 << i;
    }
    this->finalStateValue = finalState;
    bitset<sizeof(int)*8> bitFinalState = finalState;
    cout << "Condición final: \n" << bitFinalState << endl << endl;
}

bool RiverCrossing::isFinalState(State *checkState)
{
    if (checkState->rightSide == finalStateValue)
        return true;
    return false;
}

bool RiverCrossing::isValidState(State *checkState)
{
    unsigned int leftSide = ~(checkState->rightSide);
    for (int i = 0; i < leftRestrictionCount; i++)
    {
        if (leftSide == leftRestrictionMatrix[i])
            return false;
    }
    for (int i = 0; i < rightRestrictionCount; i++)
    {
        if (checkState->rightSide == rightRestrictionMatrix[i])
            return false;
    }
    return true;
}

bool RiverCrossing::canMove(State *checkState, int move)
{
    unsigned int moveBit = 1 << move;

    if (checkState->currentBoatSide == State::boatSide::left)
        move = ~move;
    
    if ((checkState->rightSide & moveBit) == moveBit)
    {
        return true;
    }
    return false;

}


bool RiverCrossing::getProblemInfo(const char *fileName)
{
    FileReader *fr = new FileReader();
    if (fr->openFile(fileName))
    {
        fr->readCountLine();

        driverCount = fr->getDriverCount();
        itemCount = fr->getItemCount();
        boatSize = fr->getBoatSize();
        calculateFinalState(driverCount + itemCount);

        leftRestrictionCount = fr->readRestrictionSize();
        leftRestrictionMatrix = new unsigned int[leftRestrictionCount];
        fr->fillLeftMatrix(leftRestrictionMatrix, leftRestrictionCount);

        rightRestrictionCount = fr->readRestrictionSize();
        rightRestrictionMatrix = new unsigned int[rightRestrictionCount];
        fr->fillRightMatrix(rightRestrictionMatrix, rightRestrictionCount);
        
        printInfo();
        delete fr;
        return true;
    }
    delete fr;
    return false;
}

void RiverCrossing::solve(const char *fileName)
{
    // leer el archivo, pasando las direcciones donde se almacenan las variables relevantes para el problema
    if (!getProblemInfo(fileName))
        return;

    int totalItemsCount = driverCount+itemCount;
    // Estado [0, 0, 0, ..., 0]
    State *currentState = new State(totalItemsCount);
    open = new Heap(2);
    open->push(currentState);
    while (!open->isEmpty()) 
    {
        State *s = open->pop();
        if (isFinalState(s)) {
            cout << "Solucion encontrada" << endl;
            s->printPath();
            return;
        }
        closed->push(s);
        
        if (canMove(s, 2)) {
            cout << "Puedo mover 2 de:" << endl;
            s->print();
            State *s1 = s->boatMove(nullptr, 0);
            cout << "quedando:" << endl;
            s1->print();
            if (!closed->search(s1->rightSide) && !open->search(s1->rightSide))
                open->push(s1);
            else {
                cout << "No se agrega L" << endl;
                delete s1;
            }
        }
    }
    cout << "No hay solucion" << endl;

    
}
