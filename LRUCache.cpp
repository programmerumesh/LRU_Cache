#include <bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    // Doubly linked list node
    struct Node {
        int key, value;
        Node *prev, *next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    unordered_map<int, Node*> lookup;
    Node *head, *tail;

    // Insert node right after head
    void insert(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // Disconnect node from the list
    void detach(Node* node) {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // Move accessed node to the front
    void promote(Node* node) {
        detach(node);
        insert(node);
    }

    // Remove least recently used node (before tail)
    Node* evict() {
        Node* node = tail->prev;
        detach(node);
        return node;
    }

public:
    LRUCache(int cap) {
        capacity = cap;
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!lookup.count(key)) return -1;
        Node* node = lookup[key];
        promote(node);
        return node->value;
    }

    void put(int key, int value) {
        if (lookup.count(key)) {
            Node* node = lookup[key];
            node->value = value;
            promote(node);
        } else {
            Node* node = new Node(key, value);
            lookup[key] = node;
            insert(node);

            if ((int)lookup.size() > capacity) {
                Node* lru = evict();
                lookup.erase(lru->key);
                delete lru;
            }
        }
    }
};
