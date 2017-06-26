#include "hevent.h"

HEvent::HEvent()
{

}

HEvent::HEvent(QEvent *event,QVariant data)
    :event(event),data(data)
{

}

HEvent::~HEvent()
{

}
