#include <QApplication>

#include "model.h"
#include "game.h"
#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Initialize the Qt application with command line arguments.

    Model model; // Create an instance of the Model class. This class likely handles game logic and data.
    GUI gui(&model); // Create an instance of the GUI class, passing a pointer to the model. This setup allows the GUI to interact with the data and state stored in the model.
    Game game(&model, &gui); // Create an instance of the Game class, passing pointers to both the model and the GUI. This allows the game to manage interactions between the game logic (model) and the graphical interface (gui).

    game.show(); // Display the main game window.
    return app.exec(); // Enter the main event loop of the application. This call will block until the application exits, handling all events and interactions.
}
