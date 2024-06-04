#include "gui.h"
#include "player.h"

GUI::GUI(Model *model, QWidget *parent)
    : QGraphicsView(parent), model(model), scene(new QGraphicsScene(this)) {

    setScene(scene);
    drawMap();
    setFixedSize(300, 200);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

GUI::~GUI() {}

void GUI::keyPressEvent(QKeyEvent *event) {
    if (scene->focusItem() != nullptr) {
        centerOn(player);
        QGraphicsView::keyPressEvent(event);
    }
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

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == 'A') {
                QGraphicsPixmapItem *tree = new QGraphicsPixmapItem(QPixmap(":/maps/assets/tree.png"));
                tree->setPos(j * 32, i * 32);
                tree->setZValue(1);
                scene->addItem(tree);
            }
        }
    }
    player = new Player();

    scene->addItem(player);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
}
