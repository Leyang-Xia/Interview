#include <iostream>
#include <vector>
#include <optional>
#include <functional>

template<typename K, typename V>
class HashTable {
private:
    struct Entry {
        K key;
        V value;
        bool is_occupied;
        bool is_deleted;

        Entry() : is_occupied(false), is_deleted(false) {}
    };

    std::vector<Entry> table;
    size_t size;
    size_t capacity;
    static constexpr float LOAD_FACTOR = 0.7f;

    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % capacity;
    }

    void resize() {
        size_t old_capacity = capacity;
        capacity *= 2;
        std::vector<Entry> new_table(capacity);
        for (const auto& entry : table) {
            if (entry.is_occupied && !entry.is_deleted) {
                size_t index = hash(entry.key);
                while (new_table[index].is_occupied) {
                    index = (index + 1) % capacity;
                }
                new_table[index] = entry;
            }
        }
        table = std::move(new_table);
    }

public:
    HashTable(size_t initial_capacity = 16) 
        : table(initial_capacity), size(0), capacity(initial_capacity) {}

    void insert(const K& key, const V& value) {
        if (static_cast<float>(size) / capacity >= LOAD_FACTOR) {
            resize();
        }

        size_t index = hash(key);
        while (table[index].is_occupied) {
            if (table[index].key == key && !table[index].is_deleted) {
                table[index].value = value;
                return;
            }
            index = (index + 1) % capacity;
        }

        table[index].key = key;
        table[index].value = value;
        table[index].is_occupied = true;
        table[index].is_deleted = false;
        size++;
    }

    std::optional<V> find(const K& key) const {
        size_t index = hash(key);
        while (table[index].is_occupied) {
            if (table[index].key == key && !table[index].is_deleted) {
                return table[index].value;
            }
            index = (index + 1) % capacity;
        }
        return std::nullopt;
    }

    bool remove(const K& key) {
        size_t index = hash(key);
        while (table[index].is_occupied) {
            if (table[index].key == key && !table[index].is_deleted) {
                table[index].is_deleted = true;
                size--;
                return true;
            }
            index = (index + 1) % capacity;
        }
        return false;
    }

    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }
};

int main() {
    HashTable<std::string, int> ht;

    ht.insert("apple", 5);
    ht.insert("banana", 7);
    ht.insert("cherry", 11);

    std::cout << "Size: " << ht.get_size() << std::endl;
    std::cout << "Capacity: " << ht.get_capacity() << std::endl;

    if (auto value = ht.find("banana")) {
        std::cout << "Value of 'banana': " << *value << std::endl;
    } else {
        std::cout << "'banana' not found" << std::endl;
    }

    ht.remove("banana");

    if (auto value = ht.find("banana")) {
        std::cout << "Value of 'banana': " << *value << std::endl;
    } else {
        std::cout << "'banana' not found" << std::endl;
    }

    return 0;
}
