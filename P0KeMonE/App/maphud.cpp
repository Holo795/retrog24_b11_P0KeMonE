#include "maphud.h"
#include "typeDef.h"
#include "model.h"
#include "player.h"

MapHUD::MapHUD(Model *model, QObject *parent)
    : QGraphicsScene(parent), model(model),
    gen(std::random_device{}()),
    encounterDist(1, 100)
{
    setObjectName("map");
    model->loadMap(":/map/mapPoke2.json");
    drawMap();

    connect(player, &Player::signEncounter, this, &MapHUD::signMessage);

    oldMenItem = new QGraphicsPixmapItem(QPixmap(":/map/map_assets/old_men.png"));
    ballsItem = new QGraphicsPixmapItem(QPixmap(":/map/map_assets/ball_open.png"));
    boxItem = new QGraphicsPixmapItem(QPixmap(":/hud/battlehud_assets/dialogue_box.png").scaled(280, 60));

    textItem = new QGraphicsTextItem("", boxItem); // Ajouté en tant qu'enfant de l'élément graphique
    textItem->setPos(QPointF(8, 4)); // Positionner le texte à l'intérieur de l'élément graphique
    textItem->setDefaultTextColor(Qt::black); // Définir la couleur du texte
    textItem->setFont(QFont("Minecraft", 9)); // Définir la police et la taille du texte
    textItem->setTextWidth(256); // Définir la largeur du texte pour le retour à la ligne

    boat = new Boat();
    addItem(boat);
}

MapHUD::~MapHUD() {
    delete player;
}

void MapHUD::drawMap() {
    clear();
    const auto &map = model->getMap();
    drawGrassLayer(map);
    drawDecorativeElements(map);
    initializePlayer();
}

void MapHUD::drawGrassLayer(const std::vector<std::vector<int>>& map) {
    for (int y = 0; y < static_cast<int>(map.size()); ++y) {
        for (int x = 0; x < static_cast<int>(map[y].size()); ++x) {
            QGraphicsPixmapItem *grass = new QGraphicsPixmapItem(QPixmap(":/map/map_assets/grass.png"));
            grass->setPos(x * 32, y * 32);
            addItem(grass);
        }
    }
}

void MapHUD::initializePlayer() {
    player = new Player();
    addItem(player);
    player->setPos(1040, 630);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}

void MapHUD::drawDecorativeElements(const std::vector<std::vector<int>>& map) {
    const QMap<int, QPair<QString, int>> pixmapMap = {
      {2, qMakePair(QString(":/map/map_assets/tree.png"), 3)},
      {3, qMakePair(QString(":/map/map_assets/rock.png"), 2)},
      {4, qMakePair(QString(":/map/map_assets/boss.png"), 2)},
      {6, qMakePair(QString(":/map/map_assets/launcher.png"), 0)},
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
      {73, qMakePair(QString(":/map/map_assets/boss_zone.png"), 2)},
      {76, qMakePair(QString(":/map/map_assets/tallgrass.png"), 0)},
      {77, qMakePair(QString(":/map/map_assets/sandy_tallgrass.png"), 0)},
      {83, qMakePair(QString(":/map/map_assets/montagne.png"), 2)},
      {92, qMakePair(QString(":/map/map_assets/pont.png"), 2)},
      {93, qMakePair(QString(":/map/map_assets/big_tree.png"), 2)},
      {94, qMakePair(QString(":/map/map_assets/bush.png"), 2)},
      {95, qMakePair(QString(":/map/map_assets/little_tree.png"), 2)},
      {96, qMakePair(QString(":/map/map_assets/sign.png"), 2)},};

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
                item->setZValue(pixmapData.second);
                item->setData(0, tileId);
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

    if(player->collidesWithItem(boat) && !boat->getIsStartJourney()) {
        boat->startJourney(player);
    }

    player->keyPressEvent(event);

    int x_foot = player->x() + 2;
    int y_foot = player->y() + player->pixmap().height();
    int tileType = model->getMap()[y_foot / 32][x_foot / 32];
    if (player->getCanMove()){
    handleTileInteraction(tileType);
    }
}

void MapHUD::handleTileInteraction(int tileType) {
    switch(tileType) {
    case 6: // Launcher
        enteringLauncher(player);
        break;
    case 76: // Tall grass
    case 77: // Sandy tall grass
        handleRandomEncounter();
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

void MapHUD::enteringLauncher(Player *player) {
        emit player->startEncouterBoss();
}

void MapHUD::signMessage(int x, int y) {
    if(showSignMessage) {
        showSignMessage = false;

        QGraphicsTextItem *text = new QGraphicsTextItem();
        if (x < 400 && y > 500){
        text->setPlainText(R"(                                        The Bridge
                                               ^
                                               |
        The tall-grasse's Field < -- -- > The slammed Lake)");
        text->setPos(x-105, y - 30);
        }
        else if (x > 400 && y > 500){
        text->setPlainText(R"(                                  The Mountain
                                           ^
                                           |
        The slammed Lake < -- -- > The hallway)");
        text->setPos(x-95, y - 30);
        }
        else {
        text->setPlainText(R"(Are you ready to face the Boss ?)");
        text->setPos(x-50, y - 10);
        }
        text->setZValue(3);
        text->setFont(QFont("Minecraft", 6));
        text->setDefaultTextColor(Qt::white);
        addItem(text);

        QTimer::singleShot(3000, this, [=](){
            removeItem(text);
            showSignMessage = true;
        });
    }
}

void MapHUD::showFirstScenario() {
    player->setCanMove(false);

    oldMenItem->setPos(1040, 580);

    ballsItem->setPos(1016, 560);

    boxItem->setPos(906, 670);

    oldMenItem->setZValue(10);
    ballsItem->setZValue(10);
    boxItem->setZValue(10);

    addItem(oldMenItem);
    addItem(ballsItem);
    addItem(boxItem);
}

void MapHUD::showSecondScenario() {
    player->setPos(910, 820);
    oldMenItem->setPos(910, 760);

    boxItem->setPos(776, 860);

    oldMenItem->setZValue(10);
    boxItem->setZValue(10);
}

void MapHUD::endScenario() {
    removeItem(boxItem);
    removeItem(oldMenItem);
    removeItem(ballsItem);
    player->setCanMove(true);
}


QGraphicsTextItem* MapHUD::getDialogTextItem() {
    return textItem;
}
