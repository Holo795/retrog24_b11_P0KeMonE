#include "pokemon.h"


Pokemon::Pokemon(int id_pk, string itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel)
{
    this->id_pk = id_pk;
    this->itsName = itsName;
    this->itsType = itsType;
    this->itsHealth = itsHealth;
    this->itsMaxHealth = itsHealth;
    this->itsSpeed = itsSpeed;
    this->itsAtk = itsAtk;
    this->itsSpAtk = itsSpAtk;
    this->itsDef = itsDef;
    this->itsSpDef = itsSpDef;
    this->itsLevel = itsLevel;
}

Pokemon::~Pokemon()
{
    
}

bool Pokemon::isDead(Pokemon &target)
{
    return target.itsHealth <= 0;
}

void Pokemon::takeDamage(int damage)
{

    itsHealth -= damage;
    if (itsHealth < 0)
    {
        itsHealth = 0;
    }
}

int Pokemon::getLvl() const
{
    return itsLevel;
}
int Pokemon::getHealth() const {
    return itsHealth;
}

int Pokemon::getSpeed() const {
    return itsSpeed;
}

int Pokemon::getAtk() const {
    return itsAtk;
}

int Pokemon::getSpAtk() const {
    return itsSpAtk;
}

int Pokemon::getDef() const {
    return itsDef;
}

int Pokemon::getSpDef() const {
    return itsSpDef;
}

int Pokemon::getId() const
{
    return id_pk;
}

string Pokemon::getItsName() const
{
    return itsName;
}

int Pokemon::getItsMaxHealth() const
{
    return itsMaxHealth;
}

QList<Move> Pokemon::getItsMoves() const
{
    return itsMoves;
}


void Pokemon::setItsMoves(const QList<Move> &newItsMoves)
{
    itsMoves = newItsMoves;
}
