#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMenuBar>
#include <QLabel>
#include <QMouseEvent>

#include "counter.h"
#include "settings.h"
#include "widgetsettings.h"
#include "xqvibra.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void dialogSet();

private slots:
    void showAbout();
    void showSettings();

protected:
    virtual void mousePressEvent(QMouseEvent *event);

private:
    void showMessageBox(const QString &text, const QString &title = " ");
    void init();

private:
    QMenuBar       *m_pMenuBar;
    QLabel         *m_pLabel;
    Counter         m_counter;
    Settings        m_settings;
    WidgetSettings *m_pWidgetSettings;
    XQVibra         m_vibra;
};

#endif // MAINWINDOW_H
