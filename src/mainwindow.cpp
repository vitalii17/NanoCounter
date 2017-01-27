#include "mainwindow.h"
#include <QAction>
#include <QBoxLayout>
#include <QInputDialog>

#ifdef Q_OS_SYMBIAN
#include <AknGlobalMsgQuery.h>
#endif // Q_OS_SYMBIAN

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent), m_pMenuBar(new QMenuBar(this)),
    m_pLabel(new QLabel)
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

    connect(&m_counter, SIGNAL(valueChanged(int)), m_pLabel, SLOT(setNum(int)));

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
    m_counter.increment();

    if(m_settings.vibraEnabled())
    {
        m_vibra.start(35);
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

    m_pLabel->setNum(m_settings.counterValue());
    m_pLabel->setAlignment(Qt::AlignHCenter);
    m_pLabel->setFont(QFont(font().family(), 48));

    m_vibra.setIntensity(80);
}

void MainWindow::showAbout()
{
    showMessageBox("Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                   "Integer convallis massa urna, vel tristique metus interdum et. "
                   "Donec vulputate eget metus eget aliquet. Mauris lacinia ex at "
                   "egestas fermentum. Nam vitae sodales leo. Suspendisse vehicula "
                   "orci est, a sagittis lectus luctus vel. Vestibulum consequat "
                   "efficitur metus, nec rhoncus nibh cursus volutpat. Duis "
                   "tincidunt magna vitae sapien bibendum, at hendrerit ex "
                   "imperdiet. Mauris convallis tortor vel mauris congue rhoncus. "
                   "Nam et lorem vitae libero dapibus ornare. ", "About");
}

void MainWindow::showSettings()
{
    m_pWidgetSettings = new WidgetSettings(&m_settings);
    m_pWidgetSettings->showFullScreen();
}


