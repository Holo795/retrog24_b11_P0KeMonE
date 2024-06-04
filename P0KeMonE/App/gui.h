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
 * @brief The GUI class
 * This class is responsible for the graphical user interface of the game.
 */
class GUI : public QGraphicsView
{
    Q_OBJECT

public:
    /**
     * @brief GUI Constructor
     * @param model Pointer to the model
     * @param parent Pointer to the parent widget
     */
    GUI(Model *model, QWidget *parent = nullptr);
    ~GUI(); ///< Destructor
    /**
     * @brief drawMap method to draw the map on the scene
     */
    void drawMap();

private:
    Model *model; ///< Pointer to the model
    QGraphicsScene *scene; ///< Pointer to the scene
    Player *player;

protected:
    void keyPressEvent(QKeyEvent *event) override;

};

#endif
