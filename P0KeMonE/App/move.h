#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "typeDef.h"
using namespace std;

class Move
{
private:
    string itsName;
    int itsPower;
    int itsAccuracy;
    PKTYPE itsType;

public:
    Move(string itsName, int itsPower, int itsAccuracy, PKTYPE itsType);
    ~Move();

};

#endif // MOVE_H
