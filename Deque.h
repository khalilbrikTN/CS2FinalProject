#ifndef DEQUE_H
#define DEQUE_H

template<class T>
class Deque {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node* frontNode;
    Node* backNode;
    int dequeSize;

public:
    Deque() : frontNode(nullptr), backNode(nullptr), dequeSize(0) {}

    ~Deque() {
        while (!isEmpty()) {
            popFront();
        }
    }

    bool isEmpty() const {
        return dequeSize == 0;
    }

    int size() const {
        return dequeSize;
    }

    void pushFront(const T& data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            frontNode = backNode = newNode;
        }
        else {
            newNode->next = frontNode;
            frontNode->prev = newNode;
            frontNode = newNode;
        }
        dequeSize++;
    }

    void pushBack(const T& data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            frontNode = backNode = newNode;
        }
        else {
            backNode->next = newNode;
            newNode->prev = backNode;
            backNode = newNode;
        }
        dequeSize++;
    }

    void popFront() {
        if (isEmpty()) {
            return;
        }
        Node* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            backNode = nullptr;
        }
        else {
            frontNode->prev = nullptr;
        }
        delete temp;
        dequeSize--;
    }

    void popBack() {
        if (isEmpty()) {
            return;
        }
        Node* temp = backNode;
        backNode = backNode->prev;
        if (backNode == nullptr) {
            frontNode = nullptr;
        }
        else {
            backNode->next = nullptr;
        }
        delete temp;
        dequeSize--;
    }

    T& front() const {
        return frontNode->data;
    }

    T& back() const {
        return backNode->data;
    }

    T& getnext() const {
        return frontNode->next->data;
    }
};

#endif // DEQUE_H
