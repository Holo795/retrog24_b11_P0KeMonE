#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();
};
#endif // GUI_H
