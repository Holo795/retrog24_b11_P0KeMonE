#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QThread>
#include <QtMultimedia/QMediaPlayer>

#include <QAudioOutput>

/**
 * @class SoundManager
 * @brief The SoundManager class manages the playback of various sounds and music in the application.
 *
 * The SoundManager class provides functionality to play jump sound effects,
 * main music, menu music, death music, win music, and level passed music.
 * It also allows setting the main and effects volume, stopping all sounds, and retrieving volume levels.
 */
class SoundManager : public QObject
{
    Q_OBJECT

public:
    explicit SoundManager(QObject *parent = nullptr);

    void playMainMusic();
    void playGrassWalk();
    void stopAllSounds();
    void setMainMusicVolume(float volume);
    void setEffectsVolume(float volume);

private:
    float itsVolume;
    float itsEffectsVolume;

    QMediaPlayer *grassWalk;
    QAudioOutput *grassWalkAudioOutput;

    QMediaPlayer *mainMusic;
    QAudioOutput *mainMusicAudioOutput;
};

#endif // SOUNDMANAGER_H
