#include <bits/stdc++.h>
using namespace std;

class OpenAddressHashMap {
    vector<pair<int, int>> hashTable;
    vector<bool> isOccupied;
    int tableSize;
    
    int hashFunction(int key) {
        return key % tableSize;
    }

public:
    OpenAddressHashMap(int size = 100) : tableSize(size) {
        hashTable.resize(tableSize, {0, 0});
        isOccupied.resize(tableSize, false);
    }

    bool contains(int key) {
        int index = hashFunction(key);
        for (int i = 0; i < tableSize; ++i) {
            int currentIndex = (index + i) % tableSize;
            if (!isOccupied[currentIndex]) return false;
            if (hashTable[currentIndex].first == key) return true;
        }
        return false;
    }

    void add(int key, int value) {
        int index = hashFunction(key);
        for (int i = 0; i < tableSize; ++i) {
            int currentIndex = (index + i) % tableSize;
            if (!isOccupied[currentIndex] || hashTable[currentIndex].first == key) {
                hashTable[currentIndex] = {key, value};
                isOccupied[currentIndex] = true;
                return;
            }
        }
    }

    void erase(int key) {
        int index = hashFunction(key);
        for (int i = 0; i < tableSize; ++i) {
            int currentIndex = (index + i) % tableSize;
            if (!isOccupied[currentIndex]) return;
            if (hashTable[currentIndex].first == key) {
                isOccupied[currentIndex] = false;
                return;
            }
        }
    }
};

int main() {
    OpenAddressHashMap hashMap;
    hashMap.add(1, 10);
    hashMap.add(2, 20);
    cout << hashMap.contains(1) << endl;  // 1
    cout << hashMap.contains(3) << endl;  // 0
    hashMap.erase(1);
    cout << hashMap.contains(1) << endl;  // 0
    return 0;
}
