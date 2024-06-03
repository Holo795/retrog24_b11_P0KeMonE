#include "gui.h"

GUI::GUI(Model *model, QWidget *parent)
    : QGraphicsView(parent), model(model), scene(new QGraphicsScene(this)) {
    setScene(scene);
    drawMap();
    setFixedSize(300, 200);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

GUI::~GUI() {}

void GUI::drawMap() {
    scene->clear();
    const auto &map = model->getMap();
    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 'X') {
                scene->addRect(x * 20, y * 20, 20, 20, QPen(), QBrush(Qt::black));
            } else if (map[y][x] == '#') {
                scene->addRect(x * 20, y * 20, 20, 20, QPen(), QBrush(Qt::gray));
            }
        }
    }
}
