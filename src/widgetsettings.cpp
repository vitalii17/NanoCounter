#include "widgetsettings.h"
#include <QBoxLayout>
#include <QAction>

WidgetSettings::WidgetSettings(Settings *settings, QWidget *parent) :
    QWidget(parent)
{
    m_pSettings = settings;
    init();

    QBoxLayout  *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_pButtonVibraEn, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_pButtonBacklight, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_pButtonVolumeKeys, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_pButtonMode, 0, Qt::AlignHCenter);
    mainLayout->addWidget(m_pButtonOrientation, 0, Qt::AlignHCenter);

    connect(m_pButtonVibraEn, SIGNAL(clicked()), this, SLOT(vibraOnOff()));
    connect(m_pButtonBacklight, SIGNAL(clicked()), this, SLOT(backlightOnOff()));
    connect(m_pButtonVolumeKeys, SIGNAL(clicked()), this, SLOT(volumeKeysOnOff()));
    connect(m_pButtonMode, SIGNAL(clicked()), this, SLOT(incDecMode()));
    connect(m_pButtonOrientation, SIGNAL(clicked()), this, SLOT(orientationToggled()));

    QAction *closeAction = new QAction(tr("Save"), this);
    closeAction->setSoftKeyRole(QAction::NegativeSoftKey);
    addAction(closeAction);

    connect(closeAction, SIGNAL(triggered()), this, SLOT(deleteLater()));

    setLayout(mainLayout);
}

WidgetSettings::~WidgetSettings()
{
    m_pSettings->setVibraEnabled(m_vibraEn);
    m_pSettings->setBacklightAlwaysOn(m_backlightEn);
    m_pSettings->setVolumKeysEnabled(m_volumeKeysEn);
    m_pSettings->setReversed(m_reversed);
    m_pSettings->setOrientation(m_orientation);
}

void WidgetSettings::vibraOnOff()
{
    m_pButtonVibraEn->setText(tr("Vibra") + ": " +
                              (m_pButtonVibraEn->isChecked() ?
                                   tr("On") : tr("Off")));

    m_vibraEn = m_pButtonVibraEn->isChecked();
}

void WidgetSettings::backlightOnOff()
{
    m_pButtonBacklight->setText(tr("Backlight") + ": " +
                                (m_pButtonBacklight->isChecked() ?
                                     tr("Keep") : tr("Don't Keep")));

    m_backlightEn = m_pButtonBacklight->isChecked();
}

void WidgetSettings::volumeKeysOnOff()
{
    m_pButtonVolumeKeys->setText(tr("Volume Keys") + ": " +
                                 (m_pButtonVolumeKeys->isChecked() ?
                                      tr("Enabled") : tr("Disabled")));
    m_volumeKeysEn = m_pButtonVolumeKeys->isChecked();

}

void WidgetSettings::incDecMode()
{
    m_reversed = !m_reversed;
    m_pButtonMode->setText(tr("Mode") + ": " +
                           (m_reversed ? tr("Decrement") : tr("Increment")));
}

void WidgetSettings::orientationToggled()
{
    if(m_orientation == Qt::WA_AutoOrientation)
    {
        m_orientation = Qt::WA_LockPortraitOrientation;
        m_pButtonOrientation->setText(tr("Orientation: ") + tr("Portrait"));
    }
    else if(m_orientation == Qt::WA_LockPortraitOrientation)
    {
        m_orientation = Qt::WA_LockLandscapeOrientation;
        m_pButtonOrientation->setText(tr("Orientation: ") + tr("Landscape"));
    }
    else
    {
        m_orientation = Qt::WA_AutoOrientation;
        m_pButtonOrientation->setText(tr("Orientation: ") + tr("Auto"));
    }
}

void WidgetSettings::init()
{
    m_vibraEn      = m_pSettings->vibraEnabled();
    m_backlightEn  = m_pSettings->backlightAlwaysOn();
    m_volumeKeysEn = m_pSettings->volumeKeysEnabled();
    m_reversed     = m_pSettings->reversed();
    m_orientation  = m_pSettings->orientation();

    // Vibra button
    m_pButtonVibraEn = new QPushButton(tr("Vibra") + ": " +
                                       (m_vibraEn ? tr("On") : tr("Off")), this);
    m_pButtonVibraEn->setCheckable(true);
    m_pButtonVibraEn->setChecked(m_vibraEn);

    // Backlight button
    m_pButtonBacklight = new QPushButton(tr("Backlight") + ": " +
                                         (m_backlightEn ? tr("Keep") :
                                                          tr("Don't Keep")), this);
    m_pButtonBacklight->setCheckable(true);
    m_pButtonBacklight->setChecked(m_backlightEn);

    // Volume keys button
    m_pButtonVolumeKeys = new QPushButton(tr("Volume Keys") + ": " +
                                          (m_volumeKeysEn ? tr("Enabled") :
                                                            tr("Disabled")), this);
    m_pButtonVolumeKeys->setCheckable(true);
    m_pButtonVolumeKeys->setChecked(m_volumeKeysEn);

    // Mode button
    m_pButtonMode = new QPushButton(tr("Mode") + ": " +
                                    (m_reversed ? tr("Decrement") :
                                                  tr("Increment")), this);

    // Orientation button
    m_pButtonOrientation = new QPushButton(tr("Orientation: ") +
                                           getOrientationString(m_orientation));

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

QString WidgetSettings::getOrientationString(int orientation)
{
    QString result = "";

    switch(orientation)
    {
    case Qt::WA_AutoOrientation:
        result = tr("Auto");
        break;
    case Qt::WA_LockPortraitOrientation:
        result = tr("Portrait");
        break;
    case Qt::WA_LockLandscapeOrientation:
        result = tr("Landscape");
        break;
    default:
        result = tr("Auto");
        break;
    }

    return result;
}

void WidgetSettings::resizeEvent(QResizeEvent *event)
{
    updateButtonsWidth(event->size().width() / 3 * 2);
    event->accept();
}

