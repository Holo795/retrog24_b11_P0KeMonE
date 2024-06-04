#include "gui.h"
#include <QMap>

GUI::GUI(Model *model, QWidget *parent)
    : QGraphicsView(parent), model(model), scene(new QGraphicsScene(this)) {

    setScene(scene);
    scale(1.5, 1.5);
    drawMap();
    setFixedSize(480, 320);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

GUI::~GUI() {}

void GUI::drawMap() {
    scene->clear();
    const auto &map = model->getMap();

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
                QGraphicsPixmapItem *grass = new QGraphicsPixmapItem(QPixmap(":/maps/assets/grass.png"));
                grass->setPos(x * 32, y * 32);
                scene->addItem(grass);
        }
    }

    const QMap<char, QString> pixmapMap = {
        {'A', ":/maps/assets/tree.png"},
        {'F', ":/maps/assets/flower.png"},
        {'V', ":/maps/assets/fence_vertical.png"},
        {'Y', ":/maps/assets/tallgrass_top_left.png"},
        {'H', ":/maps/assets/tallgrass_top.png"},
        {'L', ":/maps/assets/tallgrass_top_right.png"},
        {'G', ":/maps/assets/tallgrass_left.png"},
        {'M', ":/maps/assets/tallgrass_mid.png"},
        {'D', ":/maps/assets/tallgrass_right.png"},
        {'Z', ":/maps/assets/tallgrass_bottom_left.png"},
        {'B', ":/maps/assets/tallgrass_bottom.png"},
        {'W', ":/maps/assets/tallgrass_bottom_right.png"},
        {'T', ":/maps/assets/path_top.png"},
        {'P', ":/maps/assets/path_bottom.png"},
        {'N', ":/maps/assets/big_tree.png"}

    };

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (pixmapMap.contains(map[i][j])) {
                QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap(pixmapMap[map[i][j]]));
                item->setPos(j * 32, i * 32);
                item->setZValue(1);
                scene->addItem(item);
            }
        }
    }

}


