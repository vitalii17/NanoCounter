#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QObject *parent = 0);
    
signals:
    void valueChanged(int arg);
    
public slots:
    void reset();
    void increment();
    void decrement();
    void setValue(int arg);

public:
    int  value() const;

private:
    int m_counter;
};

#endif // COUNTER_H
