#include <iostream>
#include "EventManager.h"
#include "GetUserEvent.h"
#include "GetUserSettingsEvent.h"

EventManager *eventManager;

struct Publisher {
    std::string userName;
    std::string userType;

    Publisher(std::string userName, std::string userType) : userName(std::move(userName)),
                                                            userType(std::move(userType)) {}

    void publishGetUser() {
        auto eventType = EventType::GET_USER;
        std::cout << "Event: " << EventTypes[eventType] << " fired: " << userName << std::endl;

        eventManager->fire(eventType, GetUserEvent(userName));
    }

    void publishGetUserSettings() {
        auto eventType = EventType::GET_USER_SETTINGS;
        std::cout << "Event: " << EventTypes[eventType] << " fired: " << userType << std::endl;

        eventManager->fire(eventType, GetUserSettingsEvent(userType));
    }
};

struct Subscriber {

    std::string name;

    explicit Subscriber(std::string name) : name(std::move(name)) {}

    void gotUser(IEventBase const &event) const {
        auto &ev = dynamic_cast<GetUserEvent const &>(event);

        std::cout << name << " handled: " << EventTypes[ev.getEventType()] << ": " << ev.userName << std::endl;
    }

    void gotUserSettings(IEventBase const &event) const {
        auto &ev = dynamic_cast<GetUserSettingsEvent const &>(event);

        std::cout << name << " handled: " << EventTypes[ev.getEventType()] << ": " << ev.userType << std::endl;
    }

    EventCallback<Subscriber> *subscribeGetUser() {
        return eventManager->subscribe(this, EventType::GET_USER, &Subscriber::gotUser);
    }

    EventCallback<Subscriber> *subscribeGetUserSettings() {
        return eventManager->subscribe(this, EventType::GET_USER_SETTINGS, &Subscriber::gotUserSettings);
    }
};

int main() {
    eventManager = new EventManager();

    auto subscriber = Subscriber("subscriber");
    auto subscriberOther = Subscriber("subscriberOther");
    auto publisher = Publisher("QQ", "Q_TYPE");
    auto event = subscriber.subscribeGetUser();
    auto eventOther = subscriberOther.subscribeGetUser();
    subscriber.subscribeGetUserSettings();
    publisher.publishGetUser();

    eventManager->unSubscribe(event);
    eventManager->unSubscribe(eventOther);
    publisher.publishGetUser();
    publisher.publishGetUserSettings();

    std::cin.ignore();

    delete eventManager;

    return 0;
}