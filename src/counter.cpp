#include "counter.h"

Counter::Counter(QObject *parent) :
    QObject(parent), m_triggerMode(Normal)
{
    reset();
}

void Counter::reset()
{
    if(m_counter != 0)
    {
        m_counter = 0;
        emit valueChanged(m_counter);
    }
}

void Counter::increment()
{
    m_counter = m_counter + 1;

    if(m_counter < 0)
    {
        m_counter = 0;
    }

    emit valueChanged(m_counter);
}

void Counter::decrement()
{
    int previousCounter = m_counter;

    m_counter = m_counter - 1;

    if(m_counter < 0)
    {
        m_counter = 0;
        emit errorDecrementLimit();
    }

    if((m_counter == 0) && (previousCounter == 1))
    {
        emit reachedZero();
    }

    emit valueChanged(m_counter);
}

void Counter::setValue(int arg)
{
    if(m_counter != arg)
    {
        m_counter = arg;
        emit valueChanged(m_counter);
    }
}

void Counter::setTriggerMode(Counter::TriggerMode mode)
{
    if(m_triggerMode != mode)
    {
        m_triggerMode = mode;
        emit triggerModeChanged(m_triggerMode);
    }
}

void Counter::setReversed(bool reversed)
{
    if(reversed)
    {
        setTriggerMode(Reverse);
    }
    else
    {
        setTriggerMode(Normal);
    }
}

void Counter::trigger()
{
    switch(m_triggerMode)
    {
    case Normal:
        increment();
        break;
    case Reverse:
        decrement();
        break;
    default:
        increment();
        break;
    }
}

int Counter::value() const
{
    return m_counter;
}
