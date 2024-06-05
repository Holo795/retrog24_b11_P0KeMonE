#include "model.h"

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
 * Loads the game map from a file and stores it in a 2D character vector.
 */
void Model::loadMap(const QString& filename) {
    QFile file(filename); // Create a QFile object for the map file
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file); // Open a text stream from the file
        int rows = in.readLine().toInt(); // Read the number of rows from the first line
        int cols = in.readLine().toInt(); // Read the number of columns from the second line
        map.resize(rows, std::vector<char>(cols)); // Resize the map vector based on dimensions
        for (int i = 0; i < rows; ++i) {
            QString line = in.readLine(); // Read each line representing a row of the map
            for (int j = 0; j < cols; ++j) {
                map[i][j] = line[j].toLatin1(); // Store each character in the map array
            }
        }
    }
}

/**
 * Provides a constant reference to the game map.
 */
const std::vector<std::vector<char>>& Model::getMap() const {
    return map; // Return the map
}

/**
 * Provides access to the game's data handling class.
 */
Data * Model::getData() {
    return data; // Return the pointer to the Data instance
}
