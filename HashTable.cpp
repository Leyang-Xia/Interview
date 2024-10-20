#include <iostream>
#include <vector>
#include <list>
#include <string>

class SimpleHashTable {
private:
    static const int TABLE_SIZE = 10;
    std::vector<std::list<std::pair<std::string, int>>> table;

    int hash(const std::string& key) {
        int sum = 0;
        for (char c : key) {
            sum += c;
        }
        return sum % TABLE_SIZE;
    }

public:
    SimpleHashTable() : table(TABLE_SIZE) {}

    void insert(const std::string& key, int value) {
        int index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[index].push_back({key, value});
    }

    bool get(const std::string& key, int& value) {
        int index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }

    void remove(const std::string& key) {
        int index = hash(key);
        table[index].remove_if([&key](const auto& pair) {
            return pair.first == key;
        });
    }
};

int main() {
    SimpleHashTable ht;

    ht.insert("apple", 5);
    ht.insert("banana", 7);
    ht.insert("cherry", 11);

    int value;
    if (ht.get("banana", value)) {
        std::cout << "Value of 'banana': " << value << std::endl;
    } else {
        std::cout << "'banana' not found" << std::endl;
    }

    ht.remove("banana");

    if (ht.get("banana", value)) {
        std::cout << "Value of 'banana': " << value << std::endl;
    } else {
        std::cout << "'banana' not found" << std::endl;
    }

    return 0;
}
