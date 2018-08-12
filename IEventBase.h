#ifndef CPPEVENTS_IEVENTBASE_H
#define CPPEVENTS_IEVENTBASE_H

#include "EventType.h"

class IEventBase {

public:
    virtual EventType getEventType() const = 0;
    virtual ~IEventBase() = default;
};

#endif //CPPEVENTS_IEVENTBASE_H
