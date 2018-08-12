#ifndef CPPEVENTS_GETUSEREVENT_H
#define CPPEVENTS_GETUSEREVENT_H

#include "IEventBase.h"

struct GetUserEvent : public IEventBase {

    std::string userName;

    explicit GetUserEvent(std::string userName) : userName(std::move(userName)) {}

    EventType getEventType() const override {
        return GET_USER;
    }
};

#endif //CPPEVENTS_GETUSEREVENT_H
