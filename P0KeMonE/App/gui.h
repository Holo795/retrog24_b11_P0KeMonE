/**
 * @file gui.h
 * @brief Defines the GUI class responsible for the graphical user interface of the game.
 */

#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

#include "model.h"
#include "player.h"

/**
 * @class GUI
 * @brief The GUI class is responsible for the graphical user interface of the game.
 *
 * This class handles the rendering of the game scene, including the map and player,
 * and processes user input such as key presses and mouse events.
 */
class GUI : public QGraphicsView
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a GUI object.
     *
     * Initializes the graphics view, sets up the scene, scales the view, and draws the map.
     * Also sets fixed size for the window and disables scroll bars.
     *
     * @param model Pointer to the model.
     * @param parent Pointer to the parent widget, default is nullptr.
     */
    GUI(Model *model, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the GUI class.
     *
     * Cleans up any resources used by the GUI class.
     */
    ~GUI();

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
    QGraphicsScene *scene; ///< Pointer to the scene.
    Player *player; ///< Pointer to the player.

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

    /**
     * @brief Handles show events.
     *
     * When the view is shown, centers the view on the player and sets focus on the player.
     *
     * @param event The show event.
     */
    void showEvent(QShowEvent *event) override;

public slots:
    /**
     * @brief Updates the view to center on the player.
     *
     * Called periodically to refresh the scene and ensure the player remains centered in the view.
     */
    void updateView();
};

#endif // GUI_H
