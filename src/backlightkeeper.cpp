#include "backlightkeeper.h"
#include <e32std.h>

BacklightKeeper::BacklightKeeper(QObject *parent) :
    QObject(parent), m_pTimer(new QTimer(this))
{
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(resetInactivityTime()));
}

void BacklightKeeper::setActive(bool on)
{
    if(on)
    {
        m_pTimer->start(8000);
    }
    else
    {
        m_pTimer->stop();
    }
}

void BacklightKeeper::resetInactivityTime()
{
    User::ResetInactivityTime();
}
