#include <bits/stdc++.h>
using namespace std;

class LRUCacheSystem {
    int maxCapacity;
    list<pair<int, int>> cacheList;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;

    void refreshCache(int key, int value) {
        cacheList.erase(cacheMap[key]);
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }

public:
    LRUCacheSystem(int capacity) : maxCapacity(capacity) {}

    int fetch(int key) {
        if (cacheMap.find(key) == cacheMap.end()) return -1;
        int value = cacheMap[key]->second;
        refreshCache(key, value);
        return value;
    }

    void update(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            refreshCache(key, value);
        } else {
            if (cacheList.size() == maxCapacity) {
                int oldKey = cacheList.back().first;
                cacheList.pop_back();
                cacheMap.erase(oldKey);
            }
            cacheList.push_front({key, value});
            cacheMap[key] = cacheList.begin();
        }
    }
};

int main() {
    LRUCacheSystem lru(2);
    lru.update(1, 1);
    lru.update(2, 2);
    cout << lru.fetch(1) << endl;  // 1
    lru.update(3, 3);
    cout << lru.fetch(2) << endl;  // -1
    lru.update(4, 4);
    cout << lru.fetch(1) << endl;  // -1
    cout << lru.fetch(3) << endl;  // 3
    cout << lru.fetch(4) << endl;  // 4
    return 0;
}
