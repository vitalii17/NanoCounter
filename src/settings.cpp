#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent), m_pSettings(new QSettings)
{
    m_counterValue = m_pSettings->value("CounterValue", 0   ).toInt();
    m_vibraEnabled = m_pSettings->value("VibraEnabled", true).toBool();
}

Settings::~Settings()
{
    if(m_counterValue != m_pSettings->value("CounterValue", 0).toInt())
    {
        m_pSettings->setValue("CounterValue", m_counterValue);
    }
    if(m_vibraEnabled != m_pSettings->value("VibraEnabled", true).toBool())
    {
        m_pSettings->setValue("VibraEnabled", m_vibraEnabled);
    }

    delete m_pSettings;
}

void Settings::setCounterValue(int arg)
{
    if(m_counterValue != arg)
    {
        m_counterValue = arg;
        emit counterValueChanged(m_counterValue);
    }
}

void Settings::setVibraEnabled(bool arg)
{
    if(m_vibraEnabled != arg)
    {
        m_vibraEnabled = arg;
        emit vibraEnabledChanged(m_vibraEnabled);
    }
}

int Settings::counterValue() const
{
    return m_counterValue;
}

bool Settings::vibraEnabled() const
{
    return m_vibraEnabled;
}
