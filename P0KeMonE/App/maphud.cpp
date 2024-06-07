#include "maphud.h"

/**
 * Initializes the MapHUD scene, sets up the map layout based on the model's map data.
 */
MapHUD::MapHUD(Model *model, QObject *parent)
    : QGraphicsScene(parent), model(model),
    gen(std::random_device{}()), // Seed the generator with random_device
    encounterDist(1, 100) // Set the range for encounter checks
{
    setObjectName("map");
    model->loadMap(":/map/mapPoke2.json");
    drawMap();
}

/**
 * Destructor for the MapHUD class.
 */
MapHUD::~MapHUD() {
    delete player; // Delete the player object
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
            QGraphicsPixmapItem *grass = new QGraphicsPixmapItem(QPixmap(":/map/map_assets/grass.png"));
            grass->setPos(x * 32, y * 32); // Position each grass tile
            addItem(grass);
        }
    }

    // Decorative and functional map elements
    const QMap<int, QPair<QString, int>> pixmapMap = {
        {2, qMakePair(QString(":/map/map_assets/tree.png"), 2)},
        {3, qMakePair(QString(":/map/map_assets/rock.png"), 2)},
        {17, qMakePair(QString(":/map/map_assets/flower1.png"), 0)},
        {18, qMakePair(QString(":/map/map_assets/flower2.png"), 0)},
        {19, qMakePair(QString(":/map/map_assets/path_bottom.png"), 0)},
        {20, qMakePair(QString(":/map/map_assets/path_bottom_left.png"), 0)},
        {21, qMakePair(QString(":/map/map_assets/path_bottom_left_in.png"), 0)},
        {22, qMakePair(QString(":/map/map_assets/path_bottom_right.png"), 0)},
        {23, qMakePair(QString(":/map/map_assets/path_bottom_right_in.png"), 0)},
        {24, qMakePair(QString(":/map/map_assets/path_left.png"), 0)},
        {25, qMakePair(QString(":/map/map_assets/path_mid.png"), 0)},
        {26, qMakePair(QString(":/map/map_assets/path_right.png"), 0)},
        {27, qMakePair(QString(":/map/map_assets/path_top.png"), 0)},
        {28, qMakePair(QString(":/map/map_assets/path_top_left.png"), 0)},
        {29, qMakePair(QString(":/map/map_assets/path_top_left_in.png"), 0)},
        {30, qMakePair(QString(":/map/map_assets/path_top_right.png"), 0)},
        {31, qMakePair(QString(":/map/map_assets/path_top_right_in.png"), 0)},
        {32, qMakePair(QString(":/map/map_assets/sand.png"), 0)},
        {33, qMakePair(QString(":/map/map_assets/sandcastle.png"), 1)},
        {34, qMakePair(QString(":/map/map_assets/water_bottom.png"), 1)},
        {35, qMakePair(QString(":/map/map_assets/water_bottom_left.png"), 1)},
        {36, qMakePair(QString(":/map/map_assets/water_bottom_right.png"), 1)},
        {37, qMakePair(QString(":/map/map_assets/water_left.png"), 1)},
        {38, qMakePair(QString(":/map/map_assets/water_mid.png"), 1)},
        {39, qMakePair(QString(":/map/map_assets/water_right.png"), 1)},
        {40, qMakePair(QString(":/map/map_assets/water_top.png"), 1)},
        {41, qMakePair(QString(":/map/map_assets/water_top_left.png"), 1)},
        {42, qMakePair(QString(":/map/map_assets/water_top_right.png"), 1)},
        {52, qMakePair(QString(":/map/map_assets/fence_horizontal.png"), 2)},
        {53, qMakePair(QString(":/map/map_assets/fence_vertical.png"), 2)},
        {64, qMakePair(QString(":/map/map_assets/street_light_left.png"), 1)},
        {65, qMakePair(QString(":/map/map_assets/street_light_right.png"), 1)},
        {66, qMakePair(QString(":/map/map_assets/sign.png"), 1)},
        {67, qMakePair(QString(":/map/map_assets/stairs_left.png"), 2)},
        {68, qMakePair(QString(":/map/map_assets/stairs_right.png"), 2)},
        {69, qMakePair(QString(":/map/map_assets/boat_left.png"), 0)},
        {70, qMakePair(QString(":/map/map_assets/boat_right.png"), 0)},
        {71, qMakePair(QString(":/map/map_assets/ball_close.png"), 2)},
        {72, qMakePair(QString(":/map/map_assets/ball_open.png"), 2)},
        {73, qMakePair(QString(":/map/map_assets/boss_zone.png"), 2)},
        {76, qMakePair(QString(":/map/map_assets/tallgrass.png"), 1)},
        {83, qMakePair(QString(":/map/map_assets/montagne.png"), 2)},
        {92, qMakePair(QString(":/map/map_assets/pont.png"), 2)},
        {93, qMakePair(QString(":/map/map_assets/big_tree.png"), 2)},
        {94, qMakePair(QString(":/map/map_assets/bush.png"), 2)},
        {95, qMakePair(QString(":/map/map_assets/little_tree.png"), 2)},
        {96, qMakePair(QString(":/map/map_assets/sign.png"), 2)},
    };

    // Add decorative elements to the scene with appropriate z-values
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            int tileId = map[i][j];
            if (pixmapMap.contains(tileId)) {
                const QPair<QString, int>& pixmapData = pixmapMap[tileId];
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
    player->setPos(150, 950); // Set the initial position of the player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus(); // Focus the player to receive key events
}

/**
 * Handles key press events to control player movement and interactions.
 * Also handles random encounters in tall grass.
 */
void MapHUD::keyPressEvent(QKeyEvent *event) {
    player->keyPressEvent(event);

    int x_foot = player->x() + 2;
    int y_foot = player->y() + player->pixmap().height();
    int tileType = model->getMap()[y_foot / 32][x_foot / 32];

    switch(tileType) {
    case 76: // Herbe haute pour les rencontres aléatoires
        if (encounterDist(gen) < 15) {
            player->stopMoving();
            emit player->startEncounterCombat();
        }
        break;
    case 69: // Bateau gauche
        player->stopMoving();
        enteringBoat(player, "left");
        break;
    case 70: // Bateau droite
        player->stopMoving();
        enteringBoat(player, "right");
        break;
    default:
        break;
    }
}

/**
 * Retrieves the player object for interaction from other parts of the program.
 */
Player * MapHUD::getPlayer() {
    return player;
}

// Gérer l'entrée dans le bateau
void MapHUD::enteringBoat(Player *player, const std::string &direction) {
    if (direction == "left") {
        player->setPos(1100, 950);
    } else {
        player->setPos(500, 950);
    }
}
