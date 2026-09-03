#ifndef LOGFILE_H
#define LOGFILE_H

#include <QIODevice>
#include <QElapsedTimer>
#include <QTimer>
#include <QMutexLocker>
#include <QDebug>
#include <QBuffer>
#include <QFile>
#include "utils_global.h"

class QTCREATOR_UTILS_EXPORT LogFile : public QIODevice {
    Q_OBJECT
public:
    explicit LogFile(QObject *parent = 0);
    qint64 bytesAvailable() const;
    qint64 bytesToWrite() const
    {
        /* Report an empty backlog always. UAVTalk refuses to transmit
         * once a device reports more than its 2KB serial-era backlog
         * limit pending, and QFile's internal buffer legitimately sits
         * above that under a 25Hz telemetry stream -- which made the
         * logger drop objects and spam "io device full" while the disk
         * was absorbing everything without complaint. A file sink does
         * not need flow control. */
        return 0;
    };
    bool open(OpenMode mode);
    void setFileName(QString name)
    {
        m_file.setFileName(name);
    };
    void close();
    qint64 writeData(const char *data, qint64 dataSize);
    qint64 readData(char *data, qint64 maxlen);

    bool startReplay();
    bool stopReplay();
    void useProvidedTimeStamp(bool useProvidedTimeStamp)
    {
        m_useProvidedTimeStamp = useProvidedTimeStamp;
    }

    void setNextTimeStamp(quint32 nextTimestamp)
    {
        m_nextTimeStamp = nextTimestamp;
    }

public slots:
    void setReplaySpeed(double val)
    {
        m_playbackSpeed = val;
        qDebug() << "Playback speed is now" << m_playbackSpeed;
    };
    void pauseReplay();
    void resumeReplay();

protected slots:
    void timerFired();

signals:
    void readReady();
    void replayStarted();
    void replayFinished();

protected:
    QByteArray m_dataBuffer;
    QTimer m_timer;
    QElapsedTimer m_myTime;
    QFile m_file;
    qint32 m_lastTimeStamp;
    qint32 m_lastPlayed;
    QMutex m_mutex;


    int m_timeOffset;
    double m_playbackSpeed;

private:
    quint32 m_nextTimeStamp;
    bool m_useProvidedTimeStamp;
};

#endif // LOGFILE_H
