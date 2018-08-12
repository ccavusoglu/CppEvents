#ifndef CPPEVENTS_EVENTTYPE_H
#define CPPEVENTS_EVENTTYPE_H

#include <string>

enum EventType {
    GET_USER = 0,
    GET_USER_SETTINGS
};

static const std::string EventTypes[] = {
        "GET_USER",
        "GET_USER_SETTINGS"
};

#endif //CPPEVENTS_EVENTTYPE_H
