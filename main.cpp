#include <iostream>
#include "deque.h"
#include "AirplaneQueue.h"
#include "Airplane.h"
#include <ctime>
#include <cstdlib>
using namespace std;

float Generate_Random(int Dt) {
    float r = (rand() % 7);
    return (Dt-3) + r;
}

// void planeDeparture(int, int, int&);

int main() {
    srand(time(NULL));
    int Tservice = 10;
    int Tmax = 360; // 6 hours in minute unit
    int Dt = 6; // avg inter arrival time
    int delay = 30; // avg time for a plane to wait before departure

    AirplaneQueue AirplaneQ(Tservice);
    float nextPlaneIn;

    // Initialize simulation time and counters
    int time = 0;
    int counter = 1;
    int totalPlanesArrived = 0;
    int totalPlanesLeft = 0;
    int totalPlanesDelayed = 0;
    int totalWaitTime = 0;

    while (time < Tmax) { // as long as the simulation is working
        nextPlaneIn = Generate_Random(Dt);
        cout << "Next Plane comes in: "<< nextPlaneIn << " minutes" << endl << endl;
        time += nextPlaneIn;
        int h = time / 60;
        int m = time % 60;


        cout << "Time now is: " << h << ":" << m << endl;

        // Check for new arrivals
        Airplane plane(time);
        AirplaneQ.addAirplane(plane); // Add the plane to the AirplaneQ queue

        int hours = plane.getTarrival() / 60;
        int minutes = plane.getTarrival() % 60;

        cout << "Plane " << counter << " has arrived at " << hours << ":" << minutes << endl;
        counter++;
        totalPlanesArrived++;

        if (AirplaneQ.queueLength() <= 1) {
            if (plane.getTarrival() > AirplaneQ.getfront()->getTdeparture()) { // arrival time of new plane smaller than departure of old one


                hours = AirplaneQ.getfront()->getTdeparture() / 60;
                minutes = AirplaneQ.getfront()->getTdeparture() % 60;

                cout << "Runway is free at " << hours << ":" << minutes << endl;

                Airplane served = AirplaneQ.removeAirplane(); // The first plane in the queue lands and is served
                served.hasLanded();

                cout << hours << ":" << minutes << " --> Runway is now free" << endl << endl;

                totalPlanesLeft++;

            } else {
                // Calculate wait time

                int waitTime = AirplaneQ.getfront()->getTdeparture() - plane.getTarrival();
                if (AirplaneQ.queueLength() == 1)
                    waitTime = 0;
                else
                    cout << "Please remain airborne for: " << waitTime << " minutes" << endl;

                //cout << "New plane arrives: " << plane.getTarrival() << endl;
                //cout << "Front plane departs: " << AirplaneQ.getfront()->getTdeparture() << endl;

                plane.setTwait(waitTime);
                totalWaitTime += waitTime;
                time += waitTime;

                totalPlanesDelayed++;

            }
        } else {
            if (plane.getTarrival() > AirplaneQ.getfront()->getTdeparture()) { // arrival time of new plane smaller than departure of old one


                hours = AirplaneQ.getfront()->getTdeparture() / 60;
                minutes = AirplaneQ.getfront()->getTdeparture() % 60;

                cout << "Runway is free at " << hours << ":" << minutes << endl;

                Airplane served = AirplaneQ.removeAirplane(); // The first plane in the queue lands and is served
                served.hasLanded();

                cout << hours << ":" << minutes << " --> Runway is now free" << endl;

                totalPlanesLeft++;

            } else {
                int waitTime = AirplaneQ.getfront()->getTdeparture() - plane.getTarrival();
                if (AirplaneQ.queueLength() == 1)
                    waitTime = 0;
                else
                    cout << "Please remain airborne for: " << waitTime << " minutes" << endl;

                plane.setTwait(waitTime);
                totalWaitTime += waitTime;
                time += waitTime;

                totalPlanesDelayed++;

                Airplane served = AirplaneQ.removeAirplane(); // The first plane in the queue lands and is served
                served.hasLanded();

            }
        }

    }

    // Print simulation statistics
    cout << "Simulation Statistics:" << endl;
    cout << "Total planes arrived: " << totalPlanesArrived << endl;
    cout << "Total planes delayed: " << totalPlanesDelayed << endl;
    cout << "Total planes left on time: " << totalPlanesLeft << endl;
    cout << "Total wait time: " << totalWaitTime << " minutes" << endl;
    cout << "Average wait time: " << ((float)totalWaitTime / totalPlanesArrived) << " minutes" << endl;

    return 0;
}
