#include "gui.h"
#include "battlehud.h"
#include "player.h"

GUI::GUI(Model *model, QWidget *parent)
    : QGraphicsView(parent), model(model), scene(new QGraphicsScene(this)) {


    BattleHUD battlehud(scene);
    battlehud.displayOptions();
    setScene(scene);

    //drawMap();
    scale(1.5, 1.5);
    drawMap();
    setFixedSize(480, 320);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setRenderHint(QPainter::Antialiasing);

}

GUI::~GUI() {}

void GUI::keyPressEvent(QKeyEvent *event) {
    if (scene->focusItem() != nullptr) {
        centerOn(player);
        update();
        QGraphicsView::keyPressEvent(event);
    }
}

void GUI::mousePressEvent(QMouseEvent *event){}
void GUI::mouseDoubleClickEvent(QMouseEvent *event){}

void GUI::showEvent(QShowEvent *event) {
    QGraphicsView::showEvent(event);
    centerOn(player);
    player->setFocus();
}

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
                scene->addItem(item);
            }
        }
    }

    player = new Player();
    scene->addItem(player);
    player->setPos(200, 200);
    centerOn(player);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}
