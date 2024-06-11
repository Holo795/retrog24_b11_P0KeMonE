#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMap>

class SoundManager : public QObject
{
    Q_OBJECT
public:
    explicit SoundManager(QObject *parent = nullptr);

    void loadSound(const QString &name, const QUrl &url);
    void playSound(const QString &name, bool loop = false);
    void stopSound(const QString &name);
    bool isPlaying(const QString &name);
    void stopAllSounds();

private:
    QMap<QString, QMediaPlayer*> sounds;
};

#endif // SOUNDMANAGER_H
