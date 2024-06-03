#include "gui.h"

#include <QApplication>

#include "model.h"
#include "game.h"
#include "gui.h"
#include "data.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Model model;
    GUI gui(&model);
    Game game(&model, &gui);

    Data data;




    gui.show();
    return app.exec();
}
