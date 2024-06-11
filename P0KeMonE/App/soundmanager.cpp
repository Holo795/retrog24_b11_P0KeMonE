#include "soundmanager.h"

SoundManager::SoundManager(QObject *parent) : QObject(parent)
{
    itsVolume = 0.5f;
    itsEffectsVolume = 0.5f;

    qDebug() << "Initializing SoundManager...";


    grassWalk = new QMediaPlayer(this);
    grassWalkAudioOutput = new QAudioOutput(this);
    grassWalk->setAudioOutput(grassWalkAudioOutput);
    grassWalk->setSource(QUrl::fromLocalFile(":/sounds/sounds/grass_walk.wav"));
    grassWalkAudioOutput->setVolume(itsEffectsVolume);
    qDebug() << "Loaded grass_walk.wav" << grassWalk->errorString();


    mainMusic = new QMediaPlayer(this);
    mainMusicAudioOutput = new QAudioOutput(this);
    mainMusic->setAudioOutput(mainMusicAudioOutput);
    mainMusic->setSource(QUrl::fromLocalFile(":/sounds/sounds/mainMusic.wav"));
    mainMusicAudioOutput->setVolume(itsVolume);
    qDebug() << "Loaded mainMusic.wav" << mainMusic->errorString();


    connect(mainMusic, &QMediaPlayer::playbackStateChanged, this, [this](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::StoppedState) {
            mainMusic->setPosition(0);
            mainMusic->play(); // Loop the main music
        }
    });

    qDebug() << "SoundManager initialized.";

}

void SoundManager::playMainMusic()
{
    qDebug() << "Playing main music...";
    stopAllSounds();
    mainMusic->play();
    qDebug() << "Main music state:" << mainMusic->playbackState();
}

void SoundManager::playGrassWalk()
{
    qDebug() << "Playing grass walk sound...";
    grassWalk->play();
    qDebug() << "Grass walk state:" << grassWalk->playbackState();
}

void SoundManager::stopAllSounds()
{
    if (mainMusic->isPlaying())
    {
        mainMusic->stop();
    }

    if (grassWalk->isPlaying())
    {
        grassWalk->stop();
    }
}

void SoundManager::setMainMusicVolume(float volume)
{
    itsVolume = volume;
    mainMusicAudioOutput->setVolume(volume);
}

void SoundManager::setEffectsVolume(float volume)
{
    itsEffectsVolume = volume;
    grassWalkAudioOutput->setVolume(volume);
}
