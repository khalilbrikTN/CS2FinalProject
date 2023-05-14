//
// Created by Adam on 5/13/2023.
//

#ifndef DEQSIMULATION_AirplaneQueue_H
#define DEQSIMULATION_AirplaneQueue_H

#include "Airplane.h"
#include "Deque.h"

class AirplaneQueue {
private:
    Deque<Airplane> airplaneQueue;
    int landingTime;

public:
    AirplaneQueue(int t);
    void addAirplane(Airplane a);
    Airplane removeAirplane();
    bool isEmpty();
    int queueLength();
    Airplane* getfront();
    Airplane *getNext();
};

AirplaneQueue::AirplaneQueue(int t) {
    landingTime = t;
}

bool AirplaneQueue::isEmpty() {
    return airplaneQueue.isEmpty();
}

void AirplaneQueue::addAirplane(Airplane a) {
    airplaneQueue.pushBack(a);
}

Airplane AirplaneQueue::removeAirplane() {
    Airplane a = airplaneQueue.front();
    airplaneQueue.popFront();
    return a;
}

int AirplaneQueue::queueLength() {
    return airplaneQueue.size();
}

Airplane* AirplaneQueue::getfront() {
    Airplane* p = new Airplane(0);
    *p = airplaneQueue.front();
    return p;
}



#endif //DEQSIMULATION_AirplaneQueue_H
