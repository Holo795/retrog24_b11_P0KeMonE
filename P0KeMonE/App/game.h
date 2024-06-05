#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QKeyEvent>

#include "model.h"
#include "gui.h"


class Game : public QGraphicsView
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a Game object.
     *
     * Initializes the graphics view, sets up the scene, scales the view, and draws the map.
     * Also sets fixed size for the window and disables scroll bars.
     *
     * @param model Pointer to the model.
     * @param gui Pointer to the GUI.
     * @param parent Pointer to the parent widget, default is nullptr.
     */
    Game(Model *model, GUI *gui, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the Game class.
     *
     * Cleans up any resources used by the Game class.
     */
    ~Game();

    /**
     * @brief Draws the map on the scene.
     *
     * Clears the scene, then iterates over the map data from the model to add graphical items
     * to the scene. This includes grass, trees, flowers, fences, and other map elements.
     * Also initializes the player character and centers the view on the player.
     */
    void drawMap();

private:
    Model *model; ///< Pointer to the model.
    GUI *gui; ///< Pointer to the GUI.

protected:
    /**
     * @brief Handles key press events.
     *
     * If there is an item in the scene with focus, centers the view on the player and updates the view.
     * Passes the event to the base class implementation.
     *
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Handles mouse press events.
     *
     * Prevents loss of focus on mouse press.
     *
     * @param event The mouse event.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Handles mouse double-click events.
     *
     * Prevents loss of focus on mouse double-click.
     *
     * @param event The mouse event.
     */
    void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:
    /**
     * @brief Updates the view to center on the player.
     *
     * Called periodically to refresh the scene and ensure the player remains centered in the view.
     */
    void updateView();
};

#endif // GAME_H
