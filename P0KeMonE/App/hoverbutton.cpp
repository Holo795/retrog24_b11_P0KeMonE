#include "hoverbutton.h"

/**
 * @brief Constructs a HoverButton object.
 * @param normalIconPath The icon to display when the button is not hovered over.
 * @param hoverIconPath The icon to display when the button is hovered over.
 * @param parent The parent widget.
 */
HoverButton::HoverButton(const QPixmap &normalIconPath, const QPixmap &hoverIconPath, QWidget *parent)
    : QPushButton(parent), normalIcon(normalIconPath), hoverIcon(hoverIconPath)
{
    setIcon(normalIcon);
}

/**
 * @brief Handles the event when the mouse enters the button.
 * @param event The enter event.
 */
void HoverButton::enterEvent(QEnterEvent *event) {
    setIcon(hoverIcon);
    QPushButton::enterEvent(event);
}

/**
 * @brief Handles the event when the mouse leaves the button.
 * @param event The leave event.
 */
void HoverButton::leaveEvent(QEvent *event) {
    setIcon(normalIcon);
    QPushButton::leaveEvent(event);
}
