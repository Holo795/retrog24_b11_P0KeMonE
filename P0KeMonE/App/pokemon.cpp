#include "pokemon.h"

Pokemon::Pokemon(string itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel)
{
    this->itsName = itsName;
    this->itsType = itsType;
    this->itsHealth = itsHealth;
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
    return false;
    
}

void Pokemon::takeDamage(int damage)
{

    itsHealth -= damage;
}

void Pokemon::attack(Pokemon &target, Move move)
{

    
}
