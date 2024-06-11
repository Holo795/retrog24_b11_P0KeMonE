#include "playerhud.h"

/**
 * @brief Constructs a PlayerHUD object.
 * @param parent The parent object.
 */
PlayerHUD::PlayerHUD(QObject *parent)
    : QGraphicsScene(parent), selectionArrow(nullptr), selectionMode(false), selectedIndex(0), pokemonLabel(nullptr)
{
    setObjectName("PlayerHUD");
    setSceneRect(0, 0, 478, 318);
}

/**
 * @brief Sets the Pokémon to be displayed in the HUD.
 * @param pokemons A vector of Pokémon pointers.
 * @param itsLevelPlayer The level of the player.
 */
void PlayerHUD::setPokemons(const std::vector<Pokemon*>& pokemons, int itsLevelPlayer)
{
    this->pokemons = pokemons;
    this->itsLevelPlayer = itsLevelPlayer;

    qDebug() << "Pokemons set with level player:" << itsLevelPlayer;
    updateHUD();
}

/**
 * @brief Enables or disables the selection mode.
 * @param selectionMode If true, selection mode is enabled; otherwise, it is disabled.
 */
void PlayerHUD::setSelectionMode(bool selectionMode)
{
    this->selectionMode = selectionMode;
    qDebug() << "Selection mode set to:" << selectionMode;
    updateHUD();
}

/**
 * @brief Updates the HUD display.
 */
void PlayerHUD::updateHUD()
{
    // Clear previous items
    for (auto item : characterItems) {
        removeItem(item);
        delete item;
    }
    characterItems.clear();

    for (auto item : healthTextItems) {
        removeItem(item);
        delete item;
    }
    healthTextItems.clear();

    for (auto widget : healthBars) {
        removeItem(widget);
        delete widget;
    }
    healthBars.clear();

    if (pokemons.empty()) {
        qDebug() << "No pokemons to display.";
        return;
    }

    int xOffset = 24; // Start x position
    int yOffset = 50; // Start y position
    int spacing = 150; // Space between characters

    for (size_t i = 0; i < pokemons.size(); i++) {
        Pokemon *pokemon = pokemons[i];
        QString spritePath = ":/sprites/pk_sprites/" + QString::number(pokemon->getId()) + "_front.png";
        QPixmap characterImage = QPixmap(spritePath).scaled(150, 150);

        if (characterImage.isNull()) {
            qDebug() << "Failed to load image:" << spritePath;
        } else {
            addCharacter(characterImage, pokemon->getHealth(), pokemon->getItsMaxHealth(), xOffset + i * spacing, yOffset);
        }
    }

    if (selectionMode) {
        updateSelectionArrow();
    } else {
        if (selectionArrow) {
            removeItem(selectionArrow);
            delete selectionArrow;
            selectionArrow = nullptr;
        }

        QGraphicsTextItem *levelText = new QGraphicsTextItem(QString("Level %1").arg(itsLevelPlayer));
        levelText->setDefaultTextColor(Qt::black);
        levelText->setFont(QFont("Arial", 12, QFont::Bold));
        addItem(levelText);
        levelText->setPos(10, 10);

        if (pokemonLabel) {
            removeItem(pokemonLabel);
            delete pokemonLabel;
        }
        pokemonLabel = new QGraphicsTextItem();
        pokemonLabel->setDefaultTextColor(Qt::black);
        pokemonLabel->setFont(QFont("Arial", 17, QFont::Bold));
        addItem(pokemonLabel);
        pokemonLabel->setPos(100, 10);
    }
}

/**
 * @brief Adds a character to the HUD.
 * @param characterImage The image of the character.
 * @param currentHealth The current health of the character.
 * @param maxHealth The maximum health of the character.
 * @param xPos The x position of the character.
 * @param yPos The y position of the character.
 */
void PlayerHUD::addCharacter(const QPixmap &characterImage, int currentHealth, int maxHealth, int xPos, int yPos)
{
    QGraphicsPixmapItem *characterItem = new QGraphicsPixmapItem(characterImage);
    characterItems.append(characterItem);

    if (!selectionMode) {
        QGraphicsTextItem *healthTextItem = new QGraphicsTextItem(QString("%1/%2").arg(currentHealth).arg(maxHealth));
        addItem(healthTextItem);
        healthTextItems.append(healthTextItem);

        QProgressBar *healthBar = new QProgressBar();
        healthBar->setRange(0, maxHealth);
        healthBar->setValue(currentHealth);
        healthBar->setTextVisible(false);
        healthBar->setStyleSheet("QProgressBar::chunk { "
                                 "background-color: green; "
                                 "border-radius: 4px; "
                                 "}"
                                 "QProgressBar {"
                                 "border: 1px solid darkgreen;"
                                 "border-radius: 4px;"
                                 "}");
        healthBar->setFixedSize(120, 10);

        QGraphicsProxyWidget *proxyWidget = addWidget(healthBar);
        healthBars.append(proxyWidget);

        // Positioning
        healthTextItem->setPos(xPos + 10, yPos + characterItem->pixmap().height());
        proxyWidget->setPos(xPos + 5, yPos + characterItem->pixmap().height() + 20);
        characterItem->setPos(xPos, yPos);
    } else {
        characterItem->setPos(xPos, yPos + 50);
    }

    addItem(characterItem);
}

/**
 * @brief Updates the position of the selection arrow.
 */
void PlayerHUD::updateSelectionArrow()
{
    if (!selectionArrow) {
        selectionArrow = new QGraphicsPixmapItem(QPixmap(":/hud/battlehud_assets/arrow.png").scaled(50, 50));
        addItem(selectionArrow);
    }
    int xPos = 25 + selectedIndex * 150; // Calculate x position based on selectedIndex
    selectionArrow->setPos(xPos + 50, 35); // Adjust the position of the arrow
}

/**
 * @brief Handles key press events.
 * @param event The key event.
 */
void PlayerHUD::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key pressed: " << event->key();

    if (selectionMode) {
        if ((event->key() == Qt::Key_Left || event->key() == Qt::Key_Q) && selectedIndex > 0) {
            selectedIndex--;
            updateSelectionArrow();
        } else if ((event->key() == Qt::Key_Right || event->key() == Qt::Key_D) && selectedIndex < static_cast<int>(pokemons.size()) - 1) {
            selectedIndex++;
            updateSelectionArrow();
        } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            emit pokemonSelected(pokemons[selectedIndex]);
            selectedIndex = 0;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

/**
 * @brief Gets the label of the currently selected Pokémon.
 * @return A pointer to the QGraphicsTextItem representing the Pokémon label.
 */
QGraphicsTextItem* PlayerHUD::getPokemonLabel() const
{
    return pokemonLabel;
}

/**
 * @brief Sets the label of the currently selected Pokémon.
 * @param newPokemonLabel A pointer to the new QGraphicsTextItem to be set as the Pokémon label.
 */
void PlayerHUD::setPokemonLabel(QGraphicsTextItem *newPokemonLabel)
{
    if (pokemonLabel) {
        removeItem(pokemonLabel);
        delete pokemonLabel;
    }
    pokemonLabel = newPokemonLabel;
    addItem(pokemonLabel);
}
