#include "maphud.h"
#include "typeDef.h" // Inclusion de la déclaration de la map de masques
#include "model.h"
#include "player.h"

MapHUD::MapHUD(Model *model, QObject *parent)
    : QGraphicsScene(parent), model(model),
    gen(std::random_device{}()), // Seed the generator with random_device
    encounterDist(1, 100) // Set the range for encounter checks
{
    setObjectName("map");
    model->loadMap(":/map/mapPoke2.json");
    drawMap();

    connect(player, &Player::signEncounter, this, &MapHUD::signMessage);
}

MapHUD::~MapHUD() {
    delete player; // Delete the player object
}

void MapHUD::drawMap() {
    clear(); // Clear existing items from the scene
    const auto &map = model->getMap(); // Retrieve map data
    drawGrassLayer(map);
    drawDecorativeElements(map);
    initializePlayer();
}

void MapHUD::drawGrassLayer(const std::vector<std::vector<int>>& map) {
    for (int y = 0; y < static_cast<int>(map.size()); ++y) {
        for (int x = 0; x < static_cast<int>(map[y].size()); ++x) {
            QGraphicsPixmapItem *grass = new QGraphicsPixmapItem(QPixmap(":/map/map_assets/grass.png"));
            grass->setPos(x * 32, y * 32); // Position each grass tile
            addItem(grass);
        }
    }
}

void MapHUD::initializePlayer() {
    player = new Player();
    addItem(player);
    player->setPos(1080, 600); // Set the initial position of the player
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus(); // Focus the player to receive key events
}

void MapHUD::drawDecorativeElements(const std::vector<std::vector<int>>& map) {
    const QMap<int, QPair<QString, int>> pixmapMap = {
                                                      {2, qMakePair(QString(":/map/map_assets/tree.png"), 3)},
                                                      {3, qMakePair(QString(":/map/map_assets/rock.png"), 2)},
                                                      {4, qMakePair(QString(":/map/map_assets/boss.png"), 2)},
                                                      {5, qMakePair(QString(":/map/map_assets/old_men.png"), 2)},
                                                      {17, qMakePair(QString(":/map/map_assets/flower1.png"), 0)},
                                                      {18, qMakePair(QString(":/map/map_assets/flower2.png"), 0)},
                                                      {19, qMakePair(QString(":/map/map_assets/path_bottom.png"), 1)},
                                                      {20, qMakePair(QString(":/map/map_assets/path_bottom_left.png"), 1)},
                                                      {21, qMakePair(QString(":/map/map_assets/path_bottom_left_in.png"), 1)},
                                                      {22, qMakePair(QString(":/map/map_assets/path_bottom_right.png"), 1)},
                                                      {23, qMakePair(QString(":/map/map_assets/path_bottom_right_in.png"), 1)},
                                                      {24, qMakePair(QString(":/map/map_assets/path_left.png"), 1)},
                                                      {25, qMakePair(QString(":/map/map_assets/path_mid.png"), 1)},
                                                      {26, qMakePair(QString(":/map/map_assets/path_right.png"), 1)},
                                                      {27, qMakePair(QString(":/map/map_assets/path_top.png"), 1)},
                                                      {28, qMakePair(QString(":/map/map_assets/path_top_left.png"), 1)},
                                                      {29, qMakePair(QString(":/map/map_assets/path_top_left_in.png"), 1)},
                                                      {30, qMakePair(QString(":/map/map_assets/path_top_right.png"), 1)},
                                                      {31, qMakePair(QString(":/map/map_assets/path_top_right_in.png"), 1)},
                                                      {32, qMakePair(QString(":/map/map_assets/sand.png"), 1)},
                                                      {33, qMakePair(QString(":/map/map_assets/sandcastle.png"), 1)},
                                                      {34, qMakePair(QString(":/map/map_assets/water_bottom.png"), 2)},
                                                      {35, qMakePair(QString(":/map/map_assets/water_bottom_left.png"), 2)},
                                                      {36, qMakePair(QString(":/map/map_assets/water_bottom_right.png"), 2)},
                                                      {37, qMakePair(QString(":/map/map_assets/water_left.png"), 2)},
                                                      {38, qMakePair(QString(":/map/map_assets/water_mid.png"), 2)},
                                                      {39, qMakePair(QString(":/map/map_assets/water_right.png"), 2)},
                                                      {40, qMakePair(QString(":/map/map_assets/water_top.png"), 2)},
                                                      {41, qMakePair(QString(":/map/map_assets/water_top_left.png"), 2)},
                                                      {42, qMakePair(QString(":/map/map_assets/water_top_right.png"), 2)},
                                                      {52, qMakePair(QString(":/map/map_assets/fence_horizontal.png"), 2)},
                                                      {53, qMakePair(QString(":/map/map_assets/fence_vertical.png"), 2)},
                                                      {64, qMakePair(QString(":/map/map_assets/street_light_left.png"), 2)},
                                                      {65, qMakePair(QString(":/map/map_assets/street_light_right.png"), 2)},
                                                      {66, qMakePair(QString(":/map/map_assets/sign.png"), 1)},
                                                      {67, qMakePair(QString(":/map/map_assets/stairs_left.png"), 2)},
                                                      {68, qMakePair(QString(":/map/map_assets/stairs_right.png"), 2)},
                                                      {69, qMakePair(QString(":/map/map_assets/boat_left.png"), 1)},
                                                      {70, qMakePair(QString(":/map/map_assets/boat_right.png"), 1)},
                                                      {71, qMakePair(QString(":/map/map_assets/ball_close.png"), 2)},
                                                      {72, qMakePair(QString(":/map/map_assets/ball_open.png"), 2)},
                                                      {73, qMakePair(QString(":/map/map_assets/boss_zone.png"), 2)},
                                                      {76, qMakePair(QString(":/map/map_assets/tallgrass.png"), 0)},
                                                      {77, qMakePair(QString(":/map/map_assets/sandy_tallgrass.png"), 0)},
                                                      {83, qMakePair(QString(":/map/map_assets/montagne.png"), 2)},
                                                      {92, qMakePair(QString(":/map/map_assets/pont.png"), 2)},
                                                      {93, qMakePair(QString(":/map/map_assets/big_tree.png"), 2)},
                                                      {94, qMakePair(QString(":/map/map_assets/bush.png"), 2)},
                                                      {95, qMakePair(QString(":/map/map_assets/little_tree.png"), 2)},
                                                      {96, qMakePair(QString(":/map/map_assets/sign.png"), 2)},
                                                      };

    for (int i = 0; i < static_cast<int>(map.size()); ++i) {
        for (int j = 0; j < static_cast<int>(map[i].size()); ++j) {
            int tileId = map[i][j];
            if (pixmapMap.contains(tileId)) {
                const auto& pixmapData = pixmapMap.value(tileId);
                QPixmap pixmap(pixmapData.first);
                QBitmap mask = pixmap.createMaskFromColor(Qt::transparent);

                // Stocker le masque
                masks[tileId] = mask;

                QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
                item->setPos(j * 32, i * 32);
                item->setZValue(pixmapData.second); // Définir l'ordre de superposition
                item->setData(0, tileId); // Stocker l'ID du tile dans l'item
                addItem(item);
            }
        }
    }
}

void MapHUD::keyPressEvent(QKeyEvent *event) {

    QList<int> keys = {Qt::Key_Up, Qt::Key_Down, Qt::Key_Left, Qt::Key_Right,
                       Qt::Key_Z, Qt::Key_S, Qt::Key_Q, Qt::Key_D};

    if (!keys.contains(event->key())) {
        return;
    }

    player->keyPressEvent(event);

    int x_foot = player->x() + 2;
    int y_foot = player->y() + player->pixmap().height();
    int tileType = model->getMap()[y_foot / 32][x_foot / 32];

    handleTileInteraction(tileType);
}

void MapHUD::handleTileInteraction(int tileType) {
    switch(tileType) {
    case 4:
        enteringBossZone(player);
        break;
    case 5:
        enteringOldMenZone(player);
        break;
    case 76: // Tall grass for random encounters
    case 77: // Sandy tall grass for random encounters
        handleRandomEncounter();
        break;
    case 69: // Left boat
        enteringBoat(player, "left");
        break;
    case 70: // Right boat
        enteringBoat(player, "right");
        break;
    default:
        break;
    }
}

void MapHUD::handleRandomEncounter() {
    if (encounterDist(gen) < 15) {
        player->stopMoving();
        emit player->startEncounterCombat();
    }
}

Player* MapHUD::getPlayer() {
    return player;
}

void MapHUD::enteringBoat(Player *player, const std::string &direction) {
    player->stopMoving();
    qDebug() << player->x() << player->y();

    QVector<int> leftLimits = {608, 864};
    QVector<int> leftPositionsX = {780, 1080};

    QVector<int> rightLimits = {992, 672};
    QVector<int> rightPositionsX = {780, 560};

    if (direction == "left") {
        for (int i = 0; i < leftLimits.size(); ++i) {
            if (player->x() < leftLimits[i]) {
                player->setPos(leftPositionsX[i], 924);
                break;
            }
        }
    } else if (direction == "right") {
        for (int i = 0; i < rightLimits.size(); ++i) {
            if (player->x() > rightLimits[i]) {
                player->setPos(rightPositionsX[i], 984);
                break;
            }
        }
    }
}

void MapHUD::enteringBossZone(Player *player) {
    player->stopMoving();
    qDebug() << player->x() << player->y();
    emit player->startEncouterBoss();
}

void MapHUD::enteringOldMenZone(Player *player) {
    player->stopMoving();
    qDebug() << player->x() << player->y();
    emit player->startEncouterOldMen();
}

void MapHUD::signMessage(int x, int y) {
    if(showSignMessage) {
        showSignMessage = false;

        QGraphicsTextItem *text = new QGraphicsTextItem();
        text->setZValue(3);
        text->setPos(x, y - 20);
        text->setTextWidth(200);
        text->setPlainText("8===D");
        text->setDefaultTextColor(Qt::white);
        addItem(text);

        QTimer::singleShot(3000, this, [=](){
            removeItem(text);
            showSignMessage = true;
        });
    }
}

