#ifndef WIDGETSETTINGS_H
#define WIDGETSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QResizeEvent>
#include "settings.h"

class WidgetSettings : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSettings(Settings *settings, QWidget *parent = 0);

    ~WidgetSettings();
    
private slots:
    void vibraOnOff();
    void backlightOnOff();
    void volumeKeysOnOff();
    void incDecMode();
    void orientationToggled();

private:
    void init();
    void updateButtonsWidth(int newWidth);
    QString getOrientationString(int orientation);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QPushButton *m_pButtonVibraEn;
    QPushButton *m_pButtonBacklight;
    QPushButton *m_pButtonVolumeKeys;
    QPushButton *m_pButtonMode;
    QPushButton *m_pButtonOrientation;

    Settings *m_pSettings;

    bool m_vibraEn;
    bool m_backlightEn;
    bool m_volumeKeysEn;
    bool m_reversed;
    int  m_orientation;
};

#endif // WIDGETSETTINGS_H
