#ifndef CPPEVENTS_IEVENTCALLBACK_H
#define CPPEVENTS_IEVENTCALLBACK_H

#include "EventType.h"
#include "IEventBase.h"

class IEventCallback {

public:
    virtual EventType getEventType() const = 0;
    virtual void operator()(IEventBase const &event) const = 0;
    virtual bool operator==(IEventCallback *other) = 0;
    virtual ~IEventCallback() = default;
};

template<class T>
class EventCallback : public IEventCallback {

    T const *instance;
    EventType eventType;
    void (T::*callback)(IEventBase const &) const;

public:
    EventCallback(T const *instance, EventType eventType, void (T::*function)(IEventBase const &event) const)
            : instance(instance), eventType(eventType), callback(function) {}

    EventType getEventType() const override {
        return eventType;
    }

    void operator()(IEventBase const &event) const override {
        (instance->*callback)(event);
    }

    bool operator==(IEventCallback *other) override {
        auto *otherEventCallback = dynamic_cast<EventCallback *>(other);

        if (otherEventCallback == nullptr) return false;

        return (this->callback == otherEventCallback->callback) &&
               (this->instance == otherEventCallback->instance);
    }
};

#endif //CPPEVENTS_IEVENTCALLBACK_H
