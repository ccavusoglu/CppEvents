#include "EventManager.h"
#include "Utility.h"

// events unsubscribed will be deleted by manager itself
void EventManager::unSubscribe(IEventCallback const *action) {
    if (action == nullptr) {
        std::cout << "UnSubscribed action is null!" << std::endl;

        return;
    }

    subscribersToRemove.push(action);
}

// deletes event after handling
void EventManager::fire(EventType type, IEventBase const &event) {
    checkAddQueue();
    checkRemoveQueue();

    auto actions = subscribers[type];

    if (actions.empty()) {
        std::cout << "No subscription for event: " << EventTypes[type] << std::endl;
    }

    for (IEventCallback const *item : actions) {
        (*item)(event);
    }
}

EventManager::~EventManager() {
    for (auto &&item : subscribers) {
        for (auto &&vectorItems : item.second) {
            delete vectorItems;
        }
    }
}

void EventManager::checkAddQueue() {
    while (!subscribersToAdd.empty()) {
        auto item = subscribersToAdd.front();
        Utility::mapAddIfNotExist<int, const IEventCallback *>(subscribers, item->getEventType(), item);
        subscribersToAdd.pop();
    }
}

void EventManager::checkRemoveQueue() {
    while (!subscribersToRemove.empty()) {
        auto item = subscribersToRemove.front();
        Utility::mapRemoveIfExist<int, const IEventCallback *>(subscribers, item->getEventType(), item);
        subscribersToRemove.pop();
        delete item;
    }
}
