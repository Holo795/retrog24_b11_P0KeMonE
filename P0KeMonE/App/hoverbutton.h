#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>
#include <QEnterEvent>
#include <QEvent>



class HoverButton : public QPushButton
{
    Q_OBJECT

public:
    HoverButton(const QPixmap &normalIconPath, const QPixmap &hoverIconPath, QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QIcon normalIcon;
    QIcon hoverIcon;
};

#endif // HOVERBUTTON_H
