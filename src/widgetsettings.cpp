#include "widgetsettings.h"
#include <QBoxLayout>
#include <QDebug>

WidgetSettings::WidgetSettings(Settings *settings, QWidget *parent) :
    QWidget(parent)
{
    m_pSettings = settings;
    init();

    QBoxLayout  *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_pButtonVibraEn, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_pButtonClose, 0, Qt::AlignHCenter);

    connect(m_pButtonVibraEn, SIGNAL(clicked()), this, SLOT(vibraOnOff()));
    connect(m_pButtonClose, SIGNAL(clicked()), this, SLOT(deleteLater()));

    setLayout(mainLayout);
}

WidgetSettings::~WidgetSettings()
{
    m_pSettings->setVibraEnabled(m_vibraEn);
}

void WidgetSettings::vibraOnOff()
{
    m_pButtonVibraEn->setText(tr("Vibra") + ": " +
                              (m_pButtonVibraEn->isChecked() ?
                                   tr("On") : tr("Off")));

    m_vibraEn = m_pButtonVibraEn->isChecked();
}

void WidgetSettings::init()
{
    m_vibraEn = m_pSettings->vibraEnabled();

    m_pButtonVibraEn = new QPushButton (tr("Vibra") + ": " +
                                        (m_vibraEn ? tr("On") : tr("Off")), this);
    m_pButtonVibraEn->setCheckable(true);
    m_pButtonVibraEn->setChecked(m_vibraEn);

    m_pButtonClose   = new QPushButton(tr("Close"), this);

    updateButtonsWidth(width() / 3 * 2);
}

void WidgetSettings::updateButtonsWidth(int newWidth)
{
    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    for(int i = 0; i < buttons.count(); i++)
    {
        buttons.at(i)->setFixedWidth(newWidth);
    }
}

void WidgetSettings::resizeEvent(QResizeEvent *event)
{
    updateButtonsWidth(event->size().width() / 3 * 2);
    event->accept();
}
