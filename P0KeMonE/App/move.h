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
    MOVENATURE itsType;

public:
    Move(string itsName, int itsPower, int itsAccuracy, MOVENATURE itsType);
    ~Move();
    string getItsName() const;
    int getItsPower() const;
    int getItsAccuracy() const;
    MOVENATURE getItsType() const;
};

#endif // MOVE_H
