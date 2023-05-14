//
// Created by Adam on 5/13/2023.
//

#ifndef DEQSIMULATION_AIRPLANE_H
#define DEQSIMULATION_AIRPLANE_H

class Airplane {
private:
    int Twait;
    int Tarrival;
    int Tdeparture;
    bool landed;
public:
    explicit Airplane(int t) {
        Tarrival = t;
        Twait = 0;
        Tdeparture = Tarrival + 10;
        landed = false;
    }

    int getTarrival() const {
        return Tarrival;
    }

    int getTwait() const {
        return Twait;
    }

    int getTdeparture() const {
        return Tdeparture;
    }

    void hasLanded() {
        landed = true;
    }

    void setTwait(int t) {
         Twait = t;
    }

    void incrementTwait() {
        Twait++;
    }

};

#endif //DEQSIMULATION_AIRPLANE_H
