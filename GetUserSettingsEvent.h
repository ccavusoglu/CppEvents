#ifndef CPPEVENTS_GETUSERSETTINGSEVENT_H
#define CPPEVENTS_GETUSERSETTINGSEVENT_H

#include <utility>
#include "IEventBase.h"

struct GetUserSettingsEvent : public IEventBase {

    std::string userType;

    explicit GetUserSettingsEvent(std::string userType) : userType(std::move(userType)) {}

    EventType getEventType() const override {
        return GET_USER_SETTINGS;
    }
};

#endif //CPPEVENTS_GETUSERSETTINGSEVENT_H
