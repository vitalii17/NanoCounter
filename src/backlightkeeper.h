#ifndef BACKLIGHTKEEPER_H
#define BACKLIGHTKEEPER_H

#include <QObject>
#include <QTimer>

class BacklightKeeper : public QObject
{
    Q_OBJECT
public:
    explicit BacklightKeeper(QObject *parent = 0);
    
signals:
    
public slots:
    void setActive(bool on);

private slots:
    void resetInactivityTime();

private:
    QTimer *m_pTimer;
};

#endif // BACKLIGHTKEEPER_H
