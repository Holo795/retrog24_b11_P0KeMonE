#include "gui.h"

#include <QApplication>

#include "model.h"
#include "game.h"
#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Model model;
    GUI gui(&model);
    Game game(&model, &gui);

    gui.show();
    return app.exec();
}
