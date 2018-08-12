#ifndef CPPEVENTS_EVENTMANAGER_H
#define CPPEVENTS_EVENTMANAGER_H

#include <unordered_map>
#include <queue>
#include "EventCallback.h"

class EventManager {

    typedef std::unordered_map<int, std::vector<IEventCallback const *>> Subscribers;
    typedef std::queue<IEventCallback const *> SubscriberQueue;

    Subscribers subscribers;
    SubscriberQueue subscribersToAdd;
    SubscriberQueue subscribersToRemove;

private:
    void checkAddQueue();
    void checkRemoveQueue();

public:
    ~EventManager();

    template<class T>
    EventCallback<T> *subscribe(T const *instance, EventType eventType,
                                void (T::*function)(IEventBase const &event) const) {
        auto action = new EventCallback<T>(instance, eventType, function);

        subscribersToAdd.push(action);

        return action;
    }

    void unSubscribe(IEventCallback const *action);
    void fire(EventType type, IEventBase const &event);
};

#endif //CPPEVENTS_EVENTMANAGER_H
