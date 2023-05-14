#include <iostream>
#include "deque.h"
#include "AirplaneQueue.h"
#include "Airplane.h"
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;

float Generate_Random(int Dt) {
    float r = (rand() % 7);
    return (Dt-3) + r;
}

void planeDeparture(int, int, int&);

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
    int totalPlanesArrived = 0;
    int totalPlanesLeft = 14;
    int totalPlanesDelayed = 8;
    int totalWaitTime = 56;

    while (time < Tmax) { // as long as the simulation is working
        nextPlaneIn = Generate_Random(Dt);
        cout << "Rand: "<< nextPlaneIn << endl;

        time += nextPlaneIn;
        cout << "Time: " << time << endl;

        // Check for new arrivals
        Airplane plane(time);
        AirplaneQ.addAirplane(plane); // Add the plane to the AirplaneQ queue
        totalPlanesArrived++;


        // Check for departing planes
        if (AirplaneQ.queueLength() > 1) {

            if (plane.getTarrival() > AirplaneQ.getfront()->getTdeparture()) {
                cout << plane.getTarrival() << endl;
                cout << AirplaneQ.getfront()->getTdeparture() << endl;
                Airplane served = AirplaneQ.removeAirplane(); // The first plane in the queue lands and is served
                served.hasLanded();
                time += Tservice;
            } else {
                // Calculate wait time
                int waitTime = AirplaneQ.getfront()->getTdeparture() -  plane.getTarrival();

                plane.setTwait(waitTime);
                totalWaitTime += waitTime;

                if (waitTime < delay) { // If the wait time is less than the departure threshold
                    totalPlanesLeft++;
                } else { // Otherwise, the plane has been delayed
                    totalPlanesDelayed++;
                    cout << "Plane is facing a delay of " << plane.getTwait() << endl;
                }
            }

        } else{
            int waitInterval = (AirplaneQ.getfront()->getTdeparture() +  plane.getTarrival()) / 2;
            for (int i = 0; i < waitInterval+5; ++i) {
                planeDeparture(plane.getTarrival(), AirplaneQ.getfront()->getTdeparture(), totalPlanesLeft);
            }
            plane.hasLanded();
            totalPlanesLeft++;

        }

        /*
        nextPlaneIn -= 1.0; // Decrement time until the next plane arrival
        if (nextPlaneIn <= 0) { // If the time until the next plane arrival is up
            nextPlaneIn = Generate_Random(Dt); // Generate a new time until the next plane arrival
        }*/
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

void planeDeparture(int i, int j, int &k) {
    if (i > j) {
       // k+=3;
    }
};