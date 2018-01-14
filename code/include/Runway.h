#ifndef RUNWAY_H
#define RUNWAY_H

#include "Plane.h"
#include "Queue.h"
#include <iostream>
using namespace std;

enum Runway_activity {idle, land, takeOff};
class Runway {
private:
    Extended_queue landing;
    Extended_queue takeoff;
    int queue_limit;
    static int num_land_requests;      //  number of planes asking to land
    static int num_takeoff_requests;   //  number of planes asking to take off
    static int num_landings;           //  number of planestahthave landed
    static int num_takeoffs;           //  number of planes that have taken off
    static int num_land_accepted;      //  number of planes queued to land
    static int num_takeoff_accepted;   //  number of planes queued to take off
    static int num_land_refused;       //  number of landing planes refused
    static int num_takeoff_refused;    //  number of departing planes refused
    static int land_wait;              //  total time of planes waiting to land
    static int takeoff_wait;           //  total time of planes waiting to take off
    static int idle_time;              //  total time runway is idle
    static int num_runway;             //  number of runways

public:
    Runway(int limit);
    Error_code can_land(const Plane &current);
    Error_code can_depart(const Plane &current);
    Runway_activity activity(int time, Plane &moving);
    void shut_down(int time) const;
    static void reset();
    int check_crash(int);
    bool isLandingEmpty();
    bool isTakeoffEmpty();
};


#endif