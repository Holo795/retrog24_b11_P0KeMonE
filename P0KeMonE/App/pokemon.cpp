#include "pokemon.h"

Pokemon::Pokemon(int id_pk, string itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel)
{
    this->id_pk = id_pk;
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
    return target.itsHealth <= 0;
}

void Pokemon::takeDamage(int damage)
{

    itsHealth -= damage;
}

void Pokemon::attack(Pokemon &target, Move move)
{
    
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
