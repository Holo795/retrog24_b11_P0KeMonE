#ifndef PLAYERHUD_H
#define PLAYERHUD_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QProgressBar>
#include <QButtonGroup>
#include <QGraphicsProxyWidget>
#include <QKeyEvent>

#include "pokemon.h"

class PlayerHUD : public QGraphicsScene
{
    Q_OBJECT
public:
    PlayerHUD(QObject *parent = nullptr);
    void setPokemons(const std::vector<Pokemon*>& pokemons, int itsLevelPlayer);
    void setSelectionMode(bool selectionMode);
    void updateHUD();

    QGraphicsTextItem *getPokemonLabel() const;
    void setPokemonLabel(QGraphicsTextItem *newPokemonLabel);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void addCharacter(const QPixmap &characterImage, int currentHealth, int maxHealth, int xPos, int yPos);
    void updateSelectionArrow();

    std::vector<Pokemon*> pokemons;
    QList<QGraphicsPixmapItem*> characterItems;
    QList<QGraphicsTextItem*> healthTextItems;
    QList<QGraphicsProxyWidget*> healthBars;
    QGraphicsPixmapItem *selectionArrow;
    QGraphicsTextItem *pokemonLabel;
    bool selectionMode;
    int selectedIndex;
    int itsLevelPlayer;

signals:
    void pokemonSelected(Pokemon *pokemon);
};

#endif // PLAYERHUD_H
