#include "maphud.h"

/**
 * Initializes the MapHUD scene, sets up the map layout based on the model's map data.
 */
MapHUD::MapHUD(Model *model, QObject *parent) : QGraphicsScene(parent), model(model) {
    setObjectName("map"); // Name the scene for reference

    model->loadMap(":/maps/map.txt"); // Load map data from a file
    drawMap(); // Draw the initial map layout
}

/**
 * Draws the map based on the layout provided by the model. It populates the scene
 * with various graphical items such as grass, trees, and other objects.
 */
void MapHUD::drawMap() {
    clear(); // Clear existing items from the scene
    const auto &map = model->getMap(); // Retrieve map data

    // Initial layer with grass tiles
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            QGraphicsPixmapItem *grass = new QGraphicsPixmapItem(QPixmap(":/maps/assets/grass.png"));
            grass->setPos(x * 32, y * 32); // Position each grass tile
            addItem(grass);
        }
    }

    // Decorative and functional map elements
    const QMap<char, QPair<QString, int>> pixmapMap = {
        {'A', qMakePair(QString(":/maps/assets/tree.png"), 1)},
        {'F', qMakePair(QString(":/maps/assets/flower.png"), 0)},
        {'V', qMakePair(QString(":/maps/assets/fence_vertical.png"), 1)},
        {'Y', qMakePair(QString(":/maps/assets/tallgrass_top_left.png"), 0)},
        {'H', qMakePair(QString(":/maps/assets/tallgrass_top.png"), 0)},
        {'L', qMakePair(QString(":/maps/assets/tallgrass_top_right.png"), 0)},
        {'G', qMakePair(QString(":/maps/assets/tallgrass_left.png"), 0)},
        {'M', qMakePair(QString(":/maps/assets/tallgrass_mid.png"), 0)},
        {'D', qMakePair(QString(":/maps/assets/tallgrass_right.png"), 0)},
        {'Z', qMakePair(QString(":/maps/assets/tallgrass_bottom_left.png"), 0)},
        {'B', qMakePair(QString(":/maps/assets/tallgrass_bottom.png"), 0)},
        {'W', qMakePair(QString(":/maps/assets/tallgrass_bottom_right.png"), 0)},
        {'T', qMakePair(QString(":/maps/assets/path_top.png"), 0)},
        {'P', qMakePair(QString(":/maps/assets/path_bottom.png"), 0)},
        {'N', qMakePair(QString(":/maps/assets/big_tree.png"), 1)}
    };

    // Add decorative elements to the scene with appropriate z-values
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (pixmapMap.contains(map[i][j])) {
                const QPair<QString, int>& pixmapData = pixmapMap[map[i][j]];
                QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(pixmapData.first));
                item->setPos(j * 32, i * 32);
                item->setZValue(pixmapData.second); // Set the stacking order
                addItem(item);
            }
        }
    }

    // Initialize and add the player to the scene
    player = new Player();
    addItem(player);
    player->setPos(290, 220); // Set the initial position of the player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus(); // Focus the player to receive key events
}

/**
 * Handles key press events to control player movement and interactions.
 * Also handles random encounters in tall grass.
 */
void MapHUD::keyPressEvent(QKeyEvent *event) {
    player->keyPressEvent(event); // Delegate key press to player

    // Random encounter logic in tall grass
    QVector<char> tallgrass = {'Y', 'H', 'L', 'G', 'M', 'D', 'Z', 'B', 'W'};
    int x_foot = player->x() + 2;
    int y_foot = player->y() + player->pixmap().height();
    if (tallgrass.contains(model->getMap()[y_foot / 32][x_foot / 32])) {
        if (rand() % 100 < 15) {
            player->stopMoving(); // Stop player movement
            emit player->startEncounterCombat(); // Signal an encounter
        }
    }
}

/**
 * Retrieves the player object for interaction from other parts of the program.
 */
Player * MapHUD::getPlayer() {
    return player;
}
