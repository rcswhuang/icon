#ifndef HEVENT_H
#define HEVENT_H
#include <QEvent>
#include <QVariant>

class HEvent
{
public:
    HEvent();
    HEvent(QEvent *event,QVariant data);
    ~HEvent();

    QEvent* Event(){return event;}
    QVariant Data() {return data;}
public:
    QEvent *event;
    QVariant data;
};

#endif // HEVENT_H
