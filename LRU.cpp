#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

class LinkedNode {
public:
    LinkedNode* prev;
    LinkedNode* next;
    int key;
    int value;
    LinkedNode(int key_, int value_) : key(key_), value(value_), next(nullptr), prev(nullptr) {}
};

class LRUCache {
public:
    int capacity;
    int size;
    LinkedNode* head;
    LinkedNode* tail;
    unordered_map<int, LinkedNode*> hash;

    LRUCache(int capacity_) {
        capacity = capacity_;
        size = 0;
        head = new LinkedNode(0, 0);
        tail = new LinkedNode(0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (!hash.count(key)) {
            return -1;
        } else {
            LinkedNode* node = hash[key];
            moveToHead(node);
            return node->value;
        }
    }
    
    void put(int key, int value) {
        if (!hash.count(key)) {
            LinkedNode* node = new LinkedNode(key, value);
            addToHead(node);
            hash[key] = node;
            size++;
            if (size > capacity) {
                LinkedNode* remove = removeTail();
                hash.erase(remove->key);
                delete remove;
                size--;
            }
        } else {
            LinkedNode* node = hash[key];
            node->value = value;
            moveToHead(node);
        }
    }

private:
    void removeNode(LinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addToHead(LinkedNode* node) {
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        node->prev = head;
    }

    void moveToHead(LinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    LinkedNode* removeTail() {
        LinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};

// 测试函数
void testLRUCache() {
    LRUCache cache(2);  // 缓存容量为2

    // 插入数据
    cache.put(1, 1);
    cache.put(2, 2);

    // 检查数据是否能正确获取
    assert(cache.get(1) == 1);  // 返回 1
    assert(cache.get(2) == 2);  // 返回 2

    // 插入新数据，导致最久未使用的键被移除
    cache.put(3, 3);
    assert(cache.get(1) == -1);  // 返回 -1，因为键 1 已经被移除
    assert(cache.get(3) == 3);   // 返回 3
    assert(cache.get(2) == 2);   // 返回 2，键 2 还在缓存中

    // 插入新数据，导致键 2 被移除
    cache.put(4, 4);
    assert(cache.get(2) == -1);  // 返回 -1，因为键 2 已经被移除
    assert(cache.get(3) == 3);   // 返回 3
    assert(cache.get(4) == 4);   // 返回 4
}

int main() {
    testLRUCache();  // 运行测试
    std::cout << "All test cases passed!" << std::endl;
    return 0;
}

