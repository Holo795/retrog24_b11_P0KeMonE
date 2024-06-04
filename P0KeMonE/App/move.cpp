#include "move.h"

string Move::getItsName() const
{
    return itsName;
}

int Move::getItsPower() const
{
    return itsPower;
}

int Move::getItsAccuracy() const
{
    return itsAccuracy;
}

PKTYPE Move::getItsType() const
{
    return itsType;
}

Move::Move(string itsName, int itsPower, int itsAccuracy, MOVENATURE itsType)
{
    this->itsName = itsName;
    this->itsPower = itsPower;
    this->itsAccuracy = itsAccuracy;
    this->itsType = itsType;
}

Move::~Move()
{

}


