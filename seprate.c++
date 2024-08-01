#include <bits/stdc++.h>
using namespace std;

class SeparateChainingHashMap {
    vector<list<pair<int, int>>> hashTable;
    int tableSize;

    int hashFunction(int key) {
        return key % tableSize;
    }

public:
    SeparateChainingHashMap(int size = 100) : tableSize(size) {
        hashTable.resize(tableSize);
    }

    bool contains(int key) {
        int index = hashFunction(key);
        for (const auto &entry : hashTable[index]) {
            if (entry.first == key) return true;
        }
        return false;
    }

    void add(int key, int value) {
        int index = hashFunction(key);
        for (auto &entry : hashTable[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        hashTable[index].emplace_back(key, value);
    }

    void erase(int key) {
        int index = hashFunction(key);
        hashTable[index].remove_if([key](const pair<int, int> &entry) {
            return entry.first == key;
        });
    }
};

int main() {
    SeparateChainingHashMap hashMap;
    hashMap.add(1, 10);
    hashMap.add(2, 20);
    cout << hashMap.contains(1) << endl;  // 1
    cout << hashMap.contains(3) << endl;  // 0
    hashMap.erase(1);
    cout << hashMap.contains(1) << endl;  // 0
    return 0;
}
