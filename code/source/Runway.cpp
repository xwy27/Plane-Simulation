#include "Runway.h"

int Runway::num_land_requests = 0;      //  number of planes asking to land
int Runway::num_takeoff_requests = 0;   //  number of planes asking to take off
int Runway::num_landings = 0;           //  number of planestahthave landed
int Runway::num_takeoffs = 0;           //  number of planes that have taken off
int Runway::num_land_accepted = 0;      //  number of planes queued to land
int Runway::num_takeoff_accepted = 0;   //  number of planes queued to take off
int Runway::num_land_refused = 0;       //  number of landing planes refused
int Runway::num_takeoff_refused = 0;    //  number of departing planes refused
int Runway::land_wait = 0;              //  total time of planes waiting to land
int Runway::takeoff_wait = 0;           //  total time of planes waiting to take off
int Runway::idle_time = 0;              //  total time runway is idle
int Runway::num_runway = 0;



Runway::Runway(int limit) {
    /*Post: The Runway data members are initialized to record no prior Runway use
            and to record the limit on queue sizes.*/
    queue_limit = limit;
    ++num_runway;
}

Error_code Runway::can_land(const Plane &current) {
    /*Pre:  If possible, the Plane current is added to the landing Queue; otherwise,
            an Error_code of overflow is returned. The Runway statistics are updated.
      Uses: class Extended_queue.*/
    Error_code result;
    if (landing.size() < queue_limit) {
        result = landing.append(current);
    } else {
        result = fail;
    }
    num_land_requests++;
    if (result != success) {
        num_land_refused++;
    } else {
        num_land_accepted++;
    }
    return result;
}

Error_code Runway::can_depart(const Plane &current) {
    /*Pre:  If possible, the Plane current is added to the takeoff Queue; otherwise,
            an Error_code of overflow is returned. The Runway statistics are updated.
      Uses: class Extended_queue.*/
      Error_code result;
      if (takeoff.size() < queue_limit) {
          result = takeoff.append(current);
      } else {
          result = fail;
      }
      num_takeoff_requests++;
      if (result != success) {
          num_takeoff_refused++;
      } else {
          num_takeoff_accepted++;
      }
      return result;
}

Runway_activity Runway::activity(int time, Plane &moving) {
    /*Post: If the landing Queue has entries, its front Plane is copied to the parameter
            moving and a result land is returned. Otherwise, if the takeoff Queue has
            entries, its front Plane is copied to the parameter moving and a result
            take off is returned. Otherwise, idle is returned. Runway statistics are 
            updated.
    Uses: class Extended_queue.*/
    Runway_activity in_progress;
    if (!landing.empty()) {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land;
        landing.serve();
    } else if (!takeoff.empty()) {
        takeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = takeOff;
        takeoff.serve();
    } else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}

void Runway::shut_down(int time) const {
    cout << "Simulation has conluded after " << time << " time units." << endl
         << "Total number of planes processed "
         << (num_land_requests + num_takeoff_requests) << endl
         << "Total number of planes asking to land "
         << num_land_requests << endl
         << "Total number of planes asking to takeoff "
         << num_takeoff_requests << endl
         << "Total number of planes accepted for landing "
         << num_land_accepted << endl
         << "Total number of planes accepted for takeoff "
         << num_takeoff_accepted << endl
         << "Total number of planes refused for landing "
         << num_land_refused << endl
         << "Total number of planes refused for takeoff "
         << num_takeoff_refused << endl
         << "Total number of planes that landed "
         << num_landings << endl
         << "Total number of planes that take off "
         << num_takeoffs << endl
         << "Total number of planes left in landing queue "
         << landing.size() << endl
         << "Total number of planes left in takeoff queue "
         << takeoff.size() << endl;
    cout << "Percentage of time runway idle "
         << 100.0 * ((float)idle_time)/((float)time)/num_runway << "%" << endl;
    cout << "Average wait in landing queue "
         << ((float)land_wait)/((float)num_landings) << " time units" << endl;
    cout << "Average wait in takeoff queue "
         << ((float)takeoff_wait)/((float)num_takeoffs) << " time units" << endl;
    cout << "Average observed rate of planes waiting to land  "
         << ((float)num_land_requests)/((float)time) << " per time unit" << endl;
    cout << "Average observed rate of planes waiting to take off  "
         << ((float)num_takeoff_requests)/((float)time) << " per time unit" << endl;
    

}

void Runway::reset() {
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
    num_runway = 0;
}
bool Runway::isLandingEmpty(){
    return landing.empty();
}
bool Runway::isTakeoffEmpty(){
    return takeoff.empty();
}

int Runway::check_crash(int current_time){
    int res = 0;
    while (!landing.empty())
    {
        Plane plane = landing.top();
        if (plane.get_deadline() <= current_time)
        {
            landing.pop();
            cout << current_time << ": Plane number " << plane.get_flt_num() << " crash!! (cry...) " << endl;
            res++;
        }
        else break;
    }
    return res;
}