#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);
    ~Settings();
    
signals:
    void counterValueChanged     (int arg);
    void vibraEnabledChanged     (bool arg);
    void backlightAlwaysOnChanged(bool arg);
    void volumKeysEnabledChanged (bool arg);
    
public slots:
    void setCounterValue     (int arg);
    void setVibraEnabled     (bool arg);
    void setBacklightAlwaysOn(bool arg);
    void setVolumKeysEnabled (bool arg);

public:
    int  counterValue()               const;
    bool vibraEnabled()               const;
    bool backlightAlwaysOn()          const;
    bool volumeKeysEnabled()          const;

private:
    QSettings          *m_pSettings;
    int                 m_counterValue;
    bool                m_vibraEnabled;
    bool                m_backlightAlwaysOn;
    bool                m_volumeKeysEnabled;
};

#endif // SETTINGS_H
