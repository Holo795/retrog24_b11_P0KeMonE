/**
 * @file soundmanager.h
 * @brief Definition of the SoundManager class.
 */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QMap>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

/**
 * @class SoundManager
 * @brief The SoundManager class provides functionality for loading, playing, and managing sounds.
 *
 * This class extends QObject and allows for the loading, playing, stopping, and checking the status of sounds.
 */
class SoundManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a SoundManager object.
     * @param parent The parent object.
     */
    SoundManager(QObject *parent = nullptr);

    /**
     * @brief Loads a sound from a given URL and associates it with a name.
     * @param name The name to associate with the sound.
     * @param url The URL of the sound file.
     */
    void loadSound(const QString &name, const QUrl &url);

    /**
     * @brief Plays a sound associated with a given name.
     * @param name The name of the sound to play.
     * @param loop If true, the sound will loop; otherwise, it will play once.
     */
    void playSound(const QString &name, bool loop = false);

    /**
     * @brief Stops the sound associated with a given name.
     * @param name The name of the sound to stop.
     */
    void stopSound(const QString &name);

    /**
     * @brief Checks if a sound associated with a given name is playing.
     * @param name The name of the sound to check.
     * @return True if the sound is playing, false otherwise.
     */
    bool isPlaying(const QString &name);

    /**
     * @brief Stops all sounds that are currently playing.
     */
    void stopAllSounds();

private:
    QMap<QString, QMediaPlayer*> sounds; ///< A map of sound names to QMediaPlayer objects.
};

#endif // SOUNDMANAGER_H
