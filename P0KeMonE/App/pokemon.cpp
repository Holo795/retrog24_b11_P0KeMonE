#include <random>

#include "pokemon.h"



Pokemon::Pokemon(int id_pk, string itsName, PKTYPE itsType, int itsHealth, int itsSpeed, int itsAtk, int itsSpAtk, int itsDef, int itsSpDef, int itsLevel)
    : id_pk(id_pk), itsName(itsName), itsType(itsType), itsHealth(itsHealth), itsMaxHealth(itsHealth), itsSpeed(itsSpeed), itsAtk(itsAtk),
    itsSpAtk(itsSpAtk), itsDef(itsDef), itsSpDef(itsSpDef), itsLevel(itsLevel)
{}

bool Pokemon::isDead(Pokemon &target)
{
    return target.itsHealth <= 0;
}

void Pokemon::takeDamage(int damage)
{
    itsHealth -= damage;
    if (itsHealth < 0) {
        itsHealth = 0;
    }
}

int Pokemon::getLvl() const
{
    return itsLevel;
}

int Pokemon::getHealth() const
{
    return itsHealth;
}

int Pokemon::getSpeed() const
{
    return itsSpeed;
}

int Pokemon::getAtk() const
{
    return itsAtk;
}

int Pokemon::getSpAtk() const
{
    return itsSpAtk;
}

int Pokemon::getDef() const
{
    return itsDef;
}

int Pokemon::getSpDef() const
{
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

void Pokemon::upgradeStats() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disInt(193, 493);

    std::array<int*, 6> stats = { &itsMaxHealth, &itsSpeed, &itsAtk, &itsSpAtk, &itsDef, &itsSpDef };

    for (int* stat : stats) {
        *stat += *stat / 50 + disInt(gen) / 100;
    }

    itsHealth += itsHealth + 10 > itsMaxHealth ? itsMaxHealth - itsHealth : 10;
}

QList<Move*> Pokemon::getItsMoves() const
{
    return itsMoves;
}

void Pokemon::setItsMoves(const QList<Move*> &newItsMoves)
{
    itsMoves = newItsMoves;
}

PKTYPE Pokemon::getItsType() const
{
    return itsType;
}

void Pokemon::setLevel(int newItsLevel)
{
    itsLevel = newItsLevel;
}

Move* Pokemon::getRandMove()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, itsMoves.size() - 1);

    return itsMoves[dis(gen)];
}

