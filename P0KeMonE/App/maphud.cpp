#include "maphud.h"

MapHUD::MapHUD(Model *model, QObject *parent) : QGraphicsScene(parent) {
    this->model = model;

    setObjectName("map");

    model->loadMap(":/maps/map.txt");
    drawMap();
}

void MapHUD::drawMap()
{
    clear();
    const auto &map = model->getMap();

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            QGraphicsPixmapItem *grass = new QGraphicsPixmapItem(QPixmap(":/maps/assets/grass.png"));
            grass->setPos(x * 32, y * 32);
            addItem(grass);
        }
    }

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

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (pixmapMap.contains(map[i][j])) {
                const QPair<QString, int>& pixmapData = pixmapMap[map[i][j]];
                QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(pixmapData.first));
                item->setPos(j * 32, i * 32);
                item->setZValue(pixmapData.second);
                addItem(item);
            }
        }
    }

    player = new Player();
    addItem(player);
    player->setPos(200, 200);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

}

void MapHUD::keyPressEvent(QKeyEvent *event) {
    player->keyPressEvent(event);

    QVector<char> tallgrass = {'Y', 'H', 'L', 'G', 'M', 'D', 'Z', 'B', 'W'};

    if (tallgrass.contains(model->getMap()[player->y() / 32][player->x() / 32])) {
        if (rand() % 100 < 15) {
            emit player->startEncounterCombat();
        }
    }
}

Player * MapHUD::getPlayer() {
    return player;
}
