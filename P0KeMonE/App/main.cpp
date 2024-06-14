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

    game.show();
    return app.exec();
}
