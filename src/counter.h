#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QObject *parent = 0);

    enum TriggerMode
    {
        Normal, Reverse
    };
    
signals:
    void valueChanged(int arg);
    void triggerModeChanged(TriggerMode mode);
    
public slots:
    void reset();
    void increment();
    void decrement();
    void setValue(int arg);

    void setTriggerMode(TriggerMode mode);
    void setReversed(bool reversed);
    void trigger();

public:
    int  value() const;

private:
    int         m_counter;
    TriggerMode m_triggerMode;
};

#endif // COUNTER_H
