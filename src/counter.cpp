#include "counter.h"

Counter::Counter(QObject *parent) :
    QObject(parent)
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
    emit valueChanged(m_counter);
}

void Counter::decrement()
{
    m_counter = m_counter - 1;
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

int Counter::value() const
{
    return m_counter;
}
