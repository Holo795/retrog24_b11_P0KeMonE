#include "hoverbutton.h"

HoverButton::HoverButton(const QPixmap &normalIconPath, const QPixmap &hoverIconPath, QWidget *parent)
    : QPushButton(parent), normalIcon(normalIconPath), hoverIcon(hoverIconPath)
{
    setIcon(normalIcon);
}

void HoverButton::enterEvent(QEnterEvent *event)
{
    setIcon(hoverIcon);
    QPushButton::enterEvent(event);
}

void HoverButton::leaveEvent(QEvent *event)
{
    setIcon(normalIcon);
    QPushButton::leaveEvent(event);
}
