#include "typeDef.h"

// Définition de la map avec les dialogues
std::map<int, QString> dialogues = {
    {0, "Greetings, young adventurer!"},
    {1, "Let me introduce myself, I'm the dean of this reserve"},
    {2, "I don't know where you came from, but you're just in time, I've got a mission for you!"},
    {3, "Until recently, pokemones lived in harmony with humans."},
    {4, "But to our great misfortune, a mysterious and terrifying character has arrived"},
    {5, "He made all the humans flee and the pokémones had to take refuge in the tall grass"},
    {6, "Since then, he's stopped anyone from leaving the reserve, starving us to death!"},
    {7, "(I can't stand it any longer, the Ramoloss tails are almost all fat...)"},
    {8, "Anyway, I'm not young anymore, so you'll have to take care of getting rid of this evil creature!"},
    {9, "But don't worry, I can guide you"},
    {10, "To begin with, choose your first Pokémon."},
    {11, "Now that that's done, come and join me in the high grass, but be careful moving around..."},
    {12, "Congratulations, you've successfully completed your first pokémone battle!"},
    {13, "You're ready, I believe in you and your partner!"},
    {14, "Train him, fight other pokemones and you'll see, they'll want to join your team"},
    {15, "Every victory will make you stronger and bring you closer to your goal."},
    {16, "Remember, the key is the connection between you and your pokemones."},
    {17, "Good luck, young trainer!"}
};
QMap<int, QBitmap> masks;


// Initialisation de la table d'efficacité des types
std::map<PKTYPE, std::map<PKTYPE, float>> typeEffectiveness = {
    { Normal,   {{ Rock, 0.5f }, { Ghost, 0.0f }, { Steel, 0.5f }} },
    { Fire,     {{ Fire, 0.5f }, { Water, 0.5f }, { Grass, 2.0f }, { Ice, 2.0f }, { Bug, 2.0f }, { Rock, 0.5f }, { Dragon, 0.5f }, { Steel, 2.0f }} },
    { Water,    {{ Fire, 2.0f }, { Water, 0.5f }, { Grass, 0.5f }, { Ground, 2.0f }, { Rock, 2.0f }, { Dragon, 0.5f }} },
    { Electric, {{ Water, 2.0f }, { Electric, 0.5f }, { Grass, 0.5f }, { Ground, 0.0f }, { Flying, 2.0f }, { Dragon, 0.5f }} },
    { Grass,    {{ Fire, 0.5f }, { Water, 2.0f }, { Grass, 0.5f }, { Poison, 0.5f }, { Ground, 2.0f }, { Flying, 0.5f }, { Bug, 0.5f }, { Rock, 2.0f }, { Dragon, 0.5f }, { Steel, 0.5f }} },
    { Ice,      {{ Fire, 0.5f }, { Water, 0.5f }, { Grass, 2.0f }, { Ice, 0.5f }, { Ground, 2.0f }, { Flying, 2.0f }, { Dragon, 2.0f }, { Steel, 0.5f }} },
    { Fighting, {{ Normal, 2.0f }, { Ice, 2.0f }, { Poison, 0.5f }, { Flying, 0.5f }, { Psychic, 0.5f }, { Bug, 0.5f }, { Rock, 2.0f }, { Ghost, 0.0f }, { Dark, 2.0f }, { Steel, 2.0f }, { Fairy, 0.5f }} },
    { Poison,   {{ Grass, 2.0f }, { Poison, 0.5f }, { Ground, 0.5f }, { Rock, 0.5f }, { Ghost, 0.5f }, { Steel, 0.0f }, { Fairy, 2.0f }} },
    { Ground,   {{ Fire, 2.0f }, { Electric, 2.0f }, { Grass, 0.5f }, { Poison, 2.0f }, { Flying, 0.0f }, { Bug, 0.5f }, { Rock, 2.0f }, { Steel, 2.0f }} },
    { Flying,   {{ Electric, 0.5f }, { Grass, 2.0f }, { Fighting, 2.0f }, { Bug, 2.0f }, { Rock, 0.5f }, { Steel, 0.5f }} },
    { Psychic,  {{ Fighting, 2.0f }, { Poison, 2.0f }, { Psychic, 0.5f }, { Dark, 0.0f }, { Steel, 0.5f }} },
    { Bug,      {{ Fire, 0.5f }, { Grass, 2.0f }, { Fighting, 0.5f }, { Poison, 0.5f }, { Flying, 0.5f }, { Psychic, 2.0f }, { Ghost, 0.5f }, { Dark, 2.0f }, { Steel, 0.5f }, { Fairy, 0.5f }} },
    { Rock,     {{ Fire, 2.0f }, { Ice, 2.0f }, { Fighting, 0.5f }, { Ground, 0.5f }, { Flying, 2.0f }, { Bug, 2.0f }, { Steel, 0.5f }} },
    { Ghost,    {{ Normal, 0.0f }, { Psychic, 2.0f }, { Ghost, 2.0f }, { Dark, 0.5f }} },
    { Dragon,   {{ Dragon, 2.0f }, { Steel, 0.5f }, { Fairy, 0.0f }} },
    { Dark,     {{ Fighting, 0.5f }, { Psychic, 2.0f }, { Ghost, 2.0f }, { Dark, 0.5f }, { Fairy, 0.5f }} },
    { Steel,    {{ Fire, 0.5f }, { Water, 0.5f }, { Electric, 0.5f }, { Ice, 2.0f }, { Rock, 2.0f }, { Steel, 0.5f }, { Fairy, 2.0f }} },
    { Fairy,    {{ Fire, 0.5f }, { Fighting, 2.0f }, { Poison, 0.5f }, { Dragon, 2.0f }, { Dark, 2.0f }, { Steel, 0.5f }} }
};
