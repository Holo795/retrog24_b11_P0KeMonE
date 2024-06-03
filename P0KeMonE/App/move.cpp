#include "move.h"

    Move::Move(string itsName, int itsPower, int itsAccuracy, PKTYPE itsType)
{
    this->itsName = itsName;
    this->itsPower = itsPower;
    this->itsAccuracy = itsAccuracy;
    this->itsType = itsType;
}

Move::~Move()
{

}
