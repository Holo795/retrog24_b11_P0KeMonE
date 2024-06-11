#include "soundmanager.h"

SoundManager::SoundManager(QObject *parent)
    : QObject(parent)
{

    loadSound("background", QUrl("qrc:/sounds/sounds/mainMusic.wav"));
    loadSound("step", QUrl("qrc:/sounds/sounds/grass_walk.wav"));

}

void SoundManager::loadSound(const QString &name, const QUrl &url)
{
    if (sounds.contains(name)) {
        delete sounds[name];
    }

    QMediaPlayer *player = new QMediaPlayer(this);
    player->setAudioOutput(new QAudioOutput(this));
    player->setSource(url);
    sounds[name] = player;
}

void SoundManager::playSound(const QString &name, bool loop)
{
    if (sounds.contains(name)) {

        if (loop) {
            sounds[name]->setLoops(QMediaPlayer::Infinite);
        } else {
            sounds[name]->setLoops(1);
        }

        sounds[name]->play();
    } else {
        qWarning() << "Sound" << name << "not found!";
    }
}

void SoundManager::stopSound(const QString &name)
{
    if (sounds.contains(name)) {
        sounds[name]->stop();
    } else {
        qWarning() << "Sound" << name << "not found!";
    }
}

bool SoundManager::isPlaying(const QString &name)
{
    if (sounds.contains(name)) {
        return sounds[name]->isPlaying();
    } else {
        qWarning() << "Sound" << name << "not found!";
        return false;
    }
}

void SoundManager::stopAllSounds()
{
    for (auto player : sounds.values()) {
        player->stop();
    }
}
