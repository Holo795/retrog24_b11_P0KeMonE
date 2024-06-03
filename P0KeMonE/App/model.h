#ifndef MODEL_H
#define MODEL_H

#include <QTextStream>
#include <QFile>

class Model
{
public:
    /**
     * @brief Model constructor
     */
    Model();
    /**
     * @brief loadMap method to load the map from a file
     * sets the map variable to the map loaded from the file
     * @param filename
     */
    void loadMap(const QString& filename);
    /**
     * @brief getMap method to get the map
     * @return the map
     */
    const std::vector<std::vector<char>>& getMap() const;

private:
    std::vector<std::vector<char>> map; ///< The map of the game

};

#endif // MODEL_H
