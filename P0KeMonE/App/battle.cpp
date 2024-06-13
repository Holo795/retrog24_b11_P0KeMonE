#include "battle.h"


/**
 * Constructor for the Battle class.
 * Initializes a new battle instance with given player, opponent, and HUD.
 */
Battle::Battle(Pokemon *opponent1, Pokemon *opponent2, BattleHUD *battleHUD)
    : itsOpponent1(opponent1), itsOpponent2(opponent2), itsBattleHUD(battleHUD),
    gen(std::random_device{}()) // Seed the generator with random_device
{}

/**
 * Destructor for the Battle class.
 */
Battle::~Battle()
{
    delete itsOpponent1;
    delete itsOpponent2;
    delete itsBattleHUD;
}

// Ajoutez une nouvelle méthode pour gérer l'affichage différé du texte d'efficacité
void Battle::showEffectivenessText(Pokemon *attacker, float typeMultiplier) {
    if (typeMultiplier > 1.0f) {
        itsBattleHUD->setText("It's super effective!");
    } else if (typeMultiplier < 1.0f) {
        itsBattleHUD->setText("It's not very effective...");
    }
}

/**
 * Conducts an attack in a battle scenario using a specified move against a target Pokémon.
 * The function determines the damage based on move type and calculates whether the attack hits based on move accuracy.
 */
void Battle::attack(Move *move, Pokemon *target) {
    std::uniform_int_distribution<> dis(1, 100);  // Distribution for attack calculations
    int random = dis(gen);
    int successRate = move->getItsAccuracy();
    bool crit = random > 94; // 6% chance of critical hit

    Pokemon* attacker = target == itsOpponent2 ? itsOpponent1 : itsOpponent2;
    Pokemon* defender = target == itsOpponent2 ? itsOpponent2 : itsOpponent1;

    int lvl = attacker->getLvl();
    int atk = (move->getItsNature() == 0) ? attacker->getAtk() : attacker->getSpAtk();
    int def = (move->getItsNature() == 0) ? defender->getDef() : defender->getSpDef();

    // Calcul du multiplicateur de type
    PKTYPE moveType = move->getItsType();
    PKTYPE defenderType = defender->getItsType();
    float typeMultiplier = 1.0f; // Default multiplier

    if (typeEffectiveness.find(moveType) != typeEffectiveness.end() && typeEffectiveness[moveType].find(defenderType) != typeEffectiveness[moveType].end()) {
        typeMultiplier = typeEffectiveness[moveType][defenderType];
    }

    if (typeMultiplier == 0.0f) {
        // Affichage du message d'immunité
        itsBattleHUD->setText(attacker->getItsName() + " used " + move->getItsName() + " but it has no effect on " + defender->getItsName() + "!");
        return; // Aucune autre action n'est nécessaire car l'attaque est immunisée
    }

    int damage = move->calculateDamage(lvl, atk, def, crit, typeMultiplier);

    if (random <= successRate) {
        itsBattleHUD->frontDashPokemon(attacker);
        itsBattleHUD->shakePokemon(defender);
        defender->takeDamage(damage);

        // Affichage du message d'attaque
        itsBattleHUD->setText(attacker->getItsName() + " used " + move->getItsName() + "!");

        // Utilisation de QTimer pour un affichage différé du texte d'efficacité
        QTimer::singleShot(1000, [this, attacker, typeMultiplier]() {
            showEffectivenessText(attacker, typeMultiplier);
        });

    } else {
        itsBattleHUD->setText(attacker->getItsName() + " used " + move->getItsName() + " and missed !");
    }

    itsBattleHUD->updateHealthBars();
    itsBattleHUD->setPokemon(itsOpponent1, itsOpponent2);
}
