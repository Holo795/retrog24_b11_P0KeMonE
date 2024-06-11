#include "model.h"
#include "include/json.hpp"

using json = nlohmann::json;

/**
 * @brief Constructor for the Model class.
 * Initializes the data handler.
 */
Model::Model() : data(new Data()) {}

/**
 * @brief Destructor for the Model class.
 */
Model::~Model() {
    delete data; // Delete the data handler
}

/**
 * @brief Loads the game map from a JSON file and stores it in a 2D integer vector.
 * @param filename Path to the file containing the map data.
 */
void Model::loadMap(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Cannot open file: " + filename.toStdString());
    }

    QTextStream in(&file);
    QString jsonString = in.readAll();
    file.close();

    json j = json::parse(jsonString.toStdString());

    int width = j["width"];
    int height = j["height"];
    std::vector<int> data = j["layers"][0]["data"];

    // Initialize the map for display
    map.resize(height, std::vector<int>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            map[y][x] = data[y * width + x];
        }
    }
}

/**
 * @brief Retrieves the game map.
 * @return A constant reference to the map stored as a 2D vector of integers.
 */
const std::vector<std::vector<int>>& Model::getMap() const {
    return map; // Return the map
}

/**
 * @brief Retrieves the first team of Pokémon from the database.
 * @return A vector of pointers to the Pokémon in the first team.
 */
std::vector<Pokemon*> Model::getFirstTeam() const {
    return {data->randompokemon(), data->randompokemon(), data->randompokemon()}; // Return the first team of Pokémon
}

/**
 * @brief Provides access to the game's data handling object.
 * @return Pointer to the Data instance managing database interactions.
 */
Data * Model::getData() {
    return data; // Return the pointer to the Data instance
}
