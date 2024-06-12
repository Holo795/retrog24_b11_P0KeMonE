#include "playerhud.h"

PlayerHUD::PlayerHUD(QObject *parent)
    : QGraphicsScene(parent), selectionArrow(nullptr), selectionMode(false), selectedIndex(0)
{
    setObjectName("PlayerHUD");
    setSceneRect(0, 0, 478, 318);

    titleLabel = new QGraphicsTextItem("");
    titleLabel->setDefaultTextColor(Qt::black);
    titleLabel->setFont(QFont("Arial", 17, QFont::Bold));
    addItem(titleLabel);
    titleLabel->setPos(90, 10);
 }

void PlayerHUD::setPokemons(const std::vector<Pokemon*>& pokemons, int itsLevelPlayer)
{
    this->pokemons = pokemons;
    this->itsLevelPlayer = itsLevelPlayer;

    qDebug() << "Pokemons set with level player:" << itsLevelPlayer;
    updateHUD();
}

void PlayerHUD::setSelectionMode(bool selectionMode)
{
    this->selectionMode = selectionMode;
    qDebug() << "Selection mode set to:" << selectionMode;
    updateHUD();
}

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
        QPixmap characterImage = QPixmap(":/sprites/pk_sprites/" + QString::number(pokemon->getId()) + "_front.png").scaled(150, 150);
        addCharacter(characterImage, pokemon->getHealth(), pokemon->getItsMaxHealth(), xOffset + i * spacing, yOffset, pokemon);
    }

    if (selectionMode) {
        updateSelectionArrow();
    } else if (selectionArrow) {
        removeItem(selectionArrow);
        delete selectionArrow;
        selectionArrow = nullptr;
    }
    if(!selectionMode)
    {

        QGraphicsTextItem *levelText = new QGraphicsTextItem(QString("Level %1").arg(itsLevelPlayer));
        healthTextItems.append(levelText);
        levelText->setDefaultTextColor(Qt::black);
        levelText->setFont(QFont("Arial", 12, QFont::Bold));
        addItem(levelText);
        levelText->setPos(10, 10);
    }
}

void PlayerHUD::setPokemonLabel(string newPokemonLabel)
{
    titleLabel->setPlainText(QString::fromStdString(newPokemonLabel));
}

void PlayerHUD::addCharacter(const QPixmap &characterImage, int currentHealth, int maxHealth, int xPos, int yPos, Pokemon* pokemon)
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
    QString statPokemon = QString("Speed: %1\nAttack: %2\nDefense: %3\nSpeAttack: %4\nSpeDefense: %5\n")
                              .arg(pokemon->getSpeed())
                              .arg(pokemon->getAtk())
                              .arg(pokemon->getDef())
                              .arg(pokemon->getSpAtk())
                              .arg(pokemon->getSpDef());



    QGraphicsTextItem *statText = new QGraphicsTextItem(QString(statPokemon));
    statText->setDefaultTextColor(Qt::black);
    statText->setFont(QFont("Arial", 12, QFont::Bold));
    addItem(statText);
    healthTextItems.append(statText);
    statText->setPos(xPos + 10, yPos + characterItem->pixmap().height() + 40);


    addItem(characterItem);
}

void PlayerHUD::updateSelectionArrow()
{
    if (!selectionArrow) {
        selectionArrow = new QGraphicsPixmapItem(QPixmap(":/hud/battlehud_assets/arrow.png").scaled(50, 50));
        addItem(selectionArrow);
    }
    int xPos = 25 + selectedIndex * 150; // Calculate x position based on selectedIndex
    selectionArrow->setPos(xPos + 50, 35); // Adjust the position of the arrow
}




void PlayerHUD::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Key pressed: " << event->key();

    if (selectionMode) {
        if ((event->key() == Qt::Key_Left || event->key() == Qt::Key_Q) && selectedIndex > 0) {
            selectedIndex--;
            updateSelectionArrow();
        } else
            if ((event->key() == Qt::Key_Right || event->key() == Qt::Key_D) && selectedIndex < static_cast<int>(pokemons.size()) - 1) {
            selectedIndex++;
            updateSelectionArrow();
        } else
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            // Handle the selection confirmation
            // Emit a signal or call a method to process the selected Pokémon
            emit pokemonSelected(pokemons[selectedIndex]);
            selectedIndex=0;
            updateSelectionArrow();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

Pokemon * PlayerHUD::getPokemonChanged() const
{
    return pokemonChanged;
}


void PlayerHUD::setPokemonChanged(Pokemon *newPokemonChanged)
{
    pokemonChanged = newPokemonChanged;
}
