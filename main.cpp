#include <iostream>
#include "deque.h"
#include "AirplaneQueue.h"
#include "Airplane.h"
#include <ctime>
#include <cstdlib>
using namespace std;

float Generate_Random(int Dt); // Generates a random inter arrival time with an average of 6

void landingInstructions(int, int); // Displays the wait time and decides whether or not the plane can land

void freeRunway(int a, int &h, int &m); // Decides the time at which the runway is open for a plane


int main() {

    srand(time(NULL)); // Seed the time

    int Tservice = 10; // constant service time of 10 minutes
    int Tmax = 6 * 60; // 6 hours in minute unit
    int Dt = 6; // avg inter arrival time
    int delay = 5; // wait time at which the plane becomes late

    AirplaneQueue AirplaneQ(Tservice); // Create a queue

    float nextPlaneIn; // random inter arrival time

    // Initialize simulation time and counters
    int time = 0;

    int counter = 1; // Order of planes

    int totalPlanesArrived = 0; // Key metrics
    int totalPlanesLeft = 0;
    int totalPlanesDelayed = 0;
    int totalWaitTime = 0;

    while (time < Tmax) { // as long as the simulation is working
        nextPlaneIn = Generate_Random(Dt);
        cout << "Next Plane comes in: "<< nextPlaneIn << " minutes" << endl << endl;

        time += nextPlaneIn; // Time is updated to plane arrival time

        int h = time / 60;
        int m = time % 60;

        cout << "Time now is: " << h << ":" << m << endl;

        Airplane plane(time);
        AirplaneQ.addAirplane(plane); // Add the plane to the AirplaneQ queue

        int hours = plane.getTarrival() / 60;
        int minutes = plane.getTarrival() % 60;

        cout << "Plane " << counter << " has arrived at " << hours << ":" << minutes << endl;

        counter++; // order of plane is incremented

        totalPlanesArrived++; // Total number of arrivals is incremented

        if (AirplaneQ.queueLength() == 1) { // Queue has a single plane
            if (plane.getTarrival() > AirplaneQ.getfront()->getTdeparture()) { // arrival time of new plane smaller than departure of old one

                freeRunway(AirplaneQ.getfront()->getTdeparture(), hours, minutes);

                Airplane served = AirplaneQ.removeAirplane(); // The first plane in the queue lands and is served
                served.hasLanded();

                totalPlanesLeft++;

            } else {
                // Calculate wait time

                int waitTime = AirplaneQ.getfront()->getTdeparture() - plane.getTarrival();

                landingInstructions(waitTime, delay);

                plane.setTwait(waitTime);
                totalWaitTime += waitTime;
                time += waitTime;

                totalPlanesDelayed++;

            }
        } else {
            if (plane.getTarrival() > AirplaneQ.getfront()->getTdeparture()) { // arrival time of new plane smaller than departure of old one

                freeRunway(AirplaneQ.getfront()->getTdeparture(), hours, minutes);

                Airplane served = AirplaneQ.removeAirplane(); // The first plane in the queue lands and is served
                served.hasLanded();

                totalPlanesLeft++;

            } else {
                // Calculate wait time

                int waitTime = AirplaneQ.getfront()->getTdeparture() - plane.getTarrival();

                landingInstructions(waitTime, delay);

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

float Generate_Random(int Dt) {
    float r = (rand() % 7);
    return (Dt-3) + r;
}


void landingInstructions(int waitTime, int d) {
    cout << "Please remain airborne for: " << waitTime << " minutes" << endl;
    if (waitTime >= d)
        cout << "We apologize for the delay" << endl;
    else cout << "You will land shortly" << endl << endl;
}

void freeRunway(int a, int &h, int &m) {
    h = a / 60;
    m = a % 60;
    cout << "Runway is free at " << h << ":" << m << endl;
    cout << h << ":" << m << " --> Runway is now free" << endl;
}

