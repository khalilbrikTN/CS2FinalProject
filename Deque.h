#ifndef DEQUE_H
#define DEQUE_H

template<class T>
class Deque {
private:
    // Node struct to hold data and pointers to next and previous nodes
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d) : data(d), next(nullptr), prev(nullptr) {}
    };

    // Pointers to the front and back nodes of the deque
    Node* frontNode;
    Node* backNode;
    // The current size of the deque
    int dequeSize;

public:
    // Constructor to initialize the deque
    Deque() : frontNode(nullptr), backNode(nullptr), dequeSize(0) {}

    // Destructor to delete all nodes in the deque
    ~Deque() {
        while (!isEmpty()) {
            popFront();
        }
    }

    // Method to check if the deque is empty
    bool isEmpty() const {
        return dequeSize == 0;
    }

    // Method to get the current size of the deque
    int size() const {
        return dequeSize;
    }

    // Method to add a new node to the front of the deque
    void pushFront(const T& data) {
        // Create a new node with the given data
        Node* newNode = new Node(data);
        // If the deque is empty, set both front and back pointers to the new node
        if (isEmpty()) {
            frontNode = backNode = newNode;
        }
            // If the deque is not empty, insert the new node before the current front node
        else {
            newNode->next = frontNode;
            frontNode->prev = newNode;
            frontNode = newNode;
        }
        // Increase the size of the deque
        dequeSize++;
    }

    // Method to add a new node to the back of the deque
    void pushBack(const T& data) {
        // Create a new node with the given data
        Node* newNode = new Node(data);
        // If the deque is empty, set both front and back pointers to the new node
        if (isEmpty()) {
            frontNode = backNode = newNode;
        }
            // If the deque is not empty, insert the new node after the current back node
        else {
            backNode->next = newNode;
            newNode->prev = backNode;
            backNode = newNode;
        }
        // Increase the size of the deque
        dequeSize++;
    }

    // Method to remove the front node from the deque
    void popFront() {
        // If the deque is empty, do nothing
        if (isEmpty()) {
            return;
        }
        // Otherwise, remove the front node and update the front pointer
        Node* temp = frontNode;
        frontNode = frontNode->next;
        // If the deque is now empty, update the back pointer to null as well
        if (frontNode == nullptr) {
            backNode = nullptr;
        }
            // Otherwise, update the previous pointer of the new front node to null
        else {
            frontNode->prev = nullptr;
        }
        // Delete the old front node and decrease the size of the deque
        delete temp;
        dequeSize--;
    }

    // Method to remove the back node from the deque
    void popBack() {
        // check if the deque is empty
        if (isEmpty()) {
            return;
        }
        // get the node at the back of the deque
        Node* temp = backNode;
        // update backNode to point to the previous node
        backNode = backNode->prev;
        // if the deque is now empty, update frontNode to nullptr
        if (backNode == nullptr) {
            frontNode = nullptr;
        }
            // otherwise, update the next pointer of the new backNode to nullptr
        else {
            backNode->next = nullptr;
        }
        // delete the node and decrement dequeSize
        delete temp;
        dequeSize--;
    }

    T& front() const {
        // return a reference to the data in the front node
        return frontNode->data;
    }

    T& back() const {
        // return a reference to the data in the back node
        return backNode->data;
    }

    T& getnext() const {
        // return a reference to the data in the next node after the front node
        return frontNode->next->data;
    }
};

#endif // DEQUE_H
