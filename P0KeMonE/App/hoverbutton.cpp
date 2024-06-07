#include "hoverbutton.h"

HoverButton::HoverButton(const QString &normalIconPath, const QString &hoverIconPath, QWidget *parent)
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
