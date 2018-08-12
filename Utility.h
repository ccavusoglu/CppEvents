#ifndef CPPEVENTS_UTILITY_H
#define CPPEVENTS_UTILITY_H

#include <unordered_map>
#include <iostream>
#include <vector>
#include <algorithm>

struct Utility {
    template<typename T, class K>
    static bool mapAddIfNotExist(std::unordered_map<T, std::vector<K>> &map, T key, K value) {
        std::vector<K> items = map[key];

        if (std::find(items.begin(), items.end(), value) != items.end()) {
            std::cout << "Already added element at: " << key << std::endl;

            return false;
        }

        map[key].emplace_back(value);

        return true;
    }

    template<typename T, class K>
    static bool mapRemoveIfExist(std::unordered_map<T, std::vector<K>> &map, T key, K value) {
        std::vector<K> *items = &map[key];

        auto found = std::find(items->begin(), items->end(), value);

        if (found != items->end()) {
            auto index = std::distance(items->begin(), found);
            items->erase(items->begin() + index);

            return true;
        }

        std::cout << "Element not found at: " << key << std::endl;

        return false;
    }
};

#endif //CPPEVENTS_UTILITY_H
