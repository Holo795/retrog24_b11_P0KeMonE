#include "model.h"
#include "include/json.hpp"

using json = nlohmann::json;

/**
 * Initializes the Model object, setting up the data handler.
 */
Model::Model() {
    data = new Data(); // Initialize the data handler
}

/**
 * Destructor for the Model object.
 */
Model::~Model() {
    delete data; // Delete the data handler
}

/**
 * Loads the game map from a JSON file and stores it in a 2D character vector.
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

    // Initialiser la carte pour l'affichage
    map.resize(height, std::vector<int>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            map[y][x] = data[y * width + x];
        }
    }
}

/**
 * Provides a constant reference to the game map.
 */
const std::vector<std::vector<int>>& Model::getMap() const {
    return map; // Return the map
}

const std::vector<Pokemon*>& Model::getFirstTeam() const {
    return {data->randompokemon(), data->randompokemon(), data->randompokemon()}; // Return the first team of Pokémon
}

/**
 * Provides access to the game's data handling class.
 */
Data * Model::getData() {
    return data; // Return the pointer to the Data instance
}
