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

private:
    void init();
    void updateButtonsWidth(int newWidth);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QPushButton *m_pButtonVibraEn;
    QPushButton *m_pButtonClose;

    Settings *m_pSettings;

    bool m_vibraEn;
};

#endif // WIDGETSETTINGS_H
