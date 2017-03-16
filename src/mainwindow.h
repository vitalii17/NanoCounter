#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMenuBar>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>

#include "counter.h"
#include "settings.h"
#include "widgetsettings.h"
#include "xqvibra.h"
#include "backlightkeeper.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void dialogSet();
    void showAbout();
    void showSettings();

protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void showMessageBox(const QString &text, const QString &title = " ");
    void init();

private:
    QMenuBar        *m_pMenuBar;
    QLabel          *m_pLabel;
    Counter          m_counter;
    Settings         m_settings;
    WidgetSettings  *m_pWidgetSettings;
    XQVibra         *m_pVibra;
    BacklightKeeper *m_pBacklightKeeper;
};

#endif // MAINWINDOW_H
