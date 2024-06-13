/**
 * @file hoverbutton.h
 * @author Paulin Paul Achile Lilian
 * @brief Definition of the HoverButton class.
 */

#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>
#include <QEnterEvent>
#include <QEvent>

/**
 * @class HoverButton
 * @brief The HoverButton class provides a QPushButton that changes its icon when hovered over.
 *
 * This class extends QPushButton and changes its icon based on mouse hover events.
 */
class HoverButton : public QPushButton
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a HoverButton object.
     * @param normalIconPath The icon to display when the button is not hovered over.
     * @param hoverIconPath The icon to display when the button is hovered over.
     * @param parent The parent widget.
     */
    HoverButton(const QPixmap &normalIconPath, const QPixmap &hoverIconPath, QWidget *parent = nullptr);

protected:
    /**
     * @brief Handles the event when the mouse enters the button.
     * @param event The enter event.
     */
    void enterEvent(QEnterEvent *event) override;

    /**
     * @brief Handles the event when the mouse leaves the button.
     * @param event The leave event.
     */
    void leaveEvent(QEvent *event) override;

private:
    QIcon normalIcon; ///< The icon to display when the button is not hovered over.
    QIcon hoverIcon; ///< The icon to display when the button is hovered over.
};

#endif // HOVERBUTTON_H
