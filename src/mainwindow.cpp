#include "mainwindow.h"
#include <QAction>
#include <QBoxLayout>
#include <QInputDialog>

#ifdef Q_OS_SYMBIAN
#include <AknGlobalMsgQuery.h>
#endif // Q_OS_SYMBIAN

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent), m_pMenuBar(new QMenuBar(this)), m_pLabel(new QLabel),
    m_pMessageLabel(new QLabel), m_pVibra(new XQVibra(this)),
    m_pBacklightKeeper(new BacklightKeeper(this))
{
    init();

    QAction *actionReset    = new QAction(tr("Reset"), this);
    QAction *actionSet      = new QAction(tr("Set"), this);
    QAction *actionSettings = new QAction(tr("Settings"), this);
    QAction *actionAbout    = new QAction(tr("About"), this);

    m_pMenuBar->addAction(actionReset);
    m_pMenuBar->addAction(actionSet);
    m_pMenuBar->addAction(actionSettings);
    m_pMenuBar->addAction(actionAbout);

    connect(actionReset,    SIGNAL(triggered()), &m_counter, SLOT(reset()));
    connect(actionSet,      SIGNAL(triggered()),  this,      SLOT(dialogSet()));
    connect(actionSettings, SIGNAL(triggered()),  this,      SLOT(showSettings()));
    connect(actionAbout,    SIGNAL(triggered()),  this,      SLOT(showAbout()));

    QBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_pLabel);
    mainLayout->addWidget(m_pMessageLabel, Qt::AlignTop);
    mainLayout->addStretch(1);

    connect(&m_counter, SIGNAL(valueChanged(int)), m_pLabel, SLOT(setNum(int)));
    connect(&m_counter, SIGNAL(valueChanged(int)), m_pMessageLabel, SLOT(hide()));
    connect(&m_counter, SIGNAL(errorDecrementLimit()), m_pMessageLabel, SLOT(show()));
    connect(&m_counter, SIGNAL(reachedZero()), m_pMessageLabel, SLOT(show()));

    setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    m_settings.setCounterValue(m_counter.value());
}

void MainWindow::dialogSet()
{
    bool ok;
    int value;
    value = QInputDialog::getInt(this, tr("Set Number"), tr("Value"),
                                 m_counter.value(), 0, 10000, 1, &ok);

    if(ok)
    {
        m_counter.setValue(value);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    m_counter.trigger();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(m_settings.volumeKeysEnabled())
    {
        switch(event->key())
        {
        case Qt::Key_VolumeUp:
            m_counter.trigger();
            break;
        case Qt::Key_VolumeDown:
            m_counter.trigger();
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
        }
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void MainWindow::showMessageBox(const QString &text, const QString &title)
{
#ifdef Q_OS_SYMBIAN
    CAknGlobalMsgQuery *pDialog = CAknGlobalMsgQuery::NewL();
    CleanupStack::PushL(pDialog);
    TRequestStatus iStatus;
    TPtrC16 txtmsg(reinterpret_cast<const TUint16*>(text.utf16()));
    TPtrC16 titlemsg(reinterpret_cast<const TUint16*>(title.utf16()));
    pDialog->ShowMsgQueryL(iStatus,
                           txtmsg,
                           R_AVKON_SOFTKEYS_OK_EMPTY,
                           titlemsg,
                           KNullDesC);
    User::WaitForRequest(iStatus);
    CleanupStack::PopAndDestroy(pDialog);
#endif // Q_OS_SYMBIAN
}

void MainWindow::init()
{
    m_counter.setValue(m_settings.counterValue());
    m_counter.setReversed(m_settings.reversed());
    connect(&m_settings, SIGNAL(reversedChanged(bool)),
            &m_counter, SLOT(setReversed(bool)));

    m_pLabel->setNum(m_settings.counterValue());
    m_pLabel->setAlignment(Qt::AlignHCenter);
    m_pLabel->setFont(QFont(font().family(), 48));

    m_pMessageLabel->setText(tr("Zero value is reached. Set new value or change "
                             "counter direction to increment mode in settings."));
    m_pMessageLabel->setAlignment(Qt::AlignHCenter);
    m_pMessageLabel->setFont(QFont(font().family(), 10));
    m_pMessageLabel->setWordWrap(true);
    m_pMessageLabel->setStyleSheet("QLabel {color: red;}");
    m_pMessageLabel->setVisible((m_counter.value() <= 0) ? true : false);

    m_pVibra->setIntensity(80);
    m_pVibra->setEnabled(m_settings.vibraEnabled());
    m_pVibra->setDuration(35);
    m_pVibra->setPause(120);
    m_pVibra->setRepeatTimes(3);
    connect(&m_counter, SIGNAL(valueChanged(int)), m_pVibra, SLOT(startDuration()));
    connect(&m_settings, SIGNAL(vibraEnabledChanged(bool)),
            m_pVibra, SLOT(setEnabled(bool)));
    connect(&m_counter, SIGNAL(reachedZero()), m_pVibra, SLOT(startRepeat()));
    connect(&m_counter, SIGNAL(errorDecrementLimit()), m_pVibra, SLOT(startRepeat()));

    m_pBacklightKeeper->setActive(m_settings.backlightAlwaysOn());
    connect(&m_settings, SIGNAL(backlightAlwaysOnChanged(bool)),
            m_pBacklightKeeper, SLOT(setActive(bool)));
}

void MainWindow::showAbout()
{
    showMessageBox("Nano Counter " + QString(APP_VERSION).remove('\"') + "\n\n" +
                   tr("Developed by") + " " + tr("Vitalii Shunkov") + "\n" +
                   "(shynkov@bigmir.net)" + "\n\n" + tr("Source code available on")
                   + " " + "Github: \n" +
                   "github.com/Vitalii17/NanoCounter", tr("About"));
}

void MainWindow::showSettings()
{
    m_pWidgetSettings = new WidgetSettings(&m_settings);
    m_pWidgetSettings->showMaximized();
}



