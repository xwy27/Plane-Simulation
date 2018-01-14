#include <iostream>
#include <cstdio>
#include <sstream>
#include "Runway.h"
#include "Random.h"
#include "Plane.h"
#include "Solution.h"
using namespace std;
extern bool manual;
stringstream ss;
double getNum(double l, double r)//to get [l, r) integer
{
    for (;;)
    {
        string inp;
        inp.clear();
        while (inp.empty()) getline(cin, inp);
        ss.clear();
        ss << inp;
        double res = 0;
        if(ss >> res)
        {
            if (res >= 0 && res < r) return res;
            cout << "input number exceed interval " << endl;
        }
        else {
            cout << "invalid input!" << endl;
        }
    }

}
//output in the time the x runway is idle
void run_idle(int time, int x) {
    /*Post: The specified time is printed with a message that the runway is idle.*/
    cout << time << ": Runway "<< x <<" is idle." << endl;
}
//solve the problem1
void problem1(int end_time, int queue_limit, double arrival_rate, double departure_rate) {
    
    int flight_number = 0;
    Runway::reset();
    Random variable;
    Runway small_airport(queue_limit);
    for (int current_time = 0; current_time < end_time; ++current_time) {
                        //  loop over time intervals
        int number_arrivals;
        if (manual) 
        {
            cout << "Please enter the number of planes which arrive the airport at this moment (time " << current_time << ")" << endl;
            number_arrivals =getNum();
        }
        else number_arrivals = variable.poisson(arrival_rate);
                        //  current arrival requests
        for (int i = 0; i < number_arrivals; ++i) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success) {
                current_plane.refuse();
            }
        }
        int number_departures;
        if (manual) 
        {
            cout << "Please enter the number of planes which leave the airport at this moment (time " << current_time << ")" << endl;
            number_departures =getNum();
        }
        else number_departures = variable.poisson(departure_rate);
                        //  current departure requests
        for (int j = 0; j < number_departures; ++j) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success) {
                current_plane.refuse();
            }
        }
        
        Plane moving_plane;
        switch (small_airport.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case takeOff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time, 1);
        }
    }
    small_airport.shut_down(end_time);
    
}
//solve the problem2
void problem2(int end_time, int queue_limit, double arrival_rate, double departure_rate) {
    
    int flight_number = 0;
    Runway::reset();
    Random variable;
    Runway arrival_runway(queue_limit);
    Runway departure_runway(queue_limit);
    for (int current_time = 0; current_time < end_time; ++current_time) {
                        //  loop over time intervals
        int number_arrivals;
        if (manual) 
        {
            cout << "Please enter the number of planes which arrive the airport at this moment (time " << current_time << ")" << endl;
            number_arrivals =getNum();
        }
        else number_arrivals = variable.poisson(arrival_rate);
                        //  current arrival requests
        for (int i = 0; i < number_arrivals; ++i) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrival_runway.can_land(current_plane) != success) {
                current_plane.refuse();
            }
        }
        int number_departures;
        if (manual) 
        {
            cout << "Please enter the number of planes which leave the airport at this moment (time " << current_time << ")" << endl;
            number_departures =getNum();
        }
        else number_departures = variable.poisson(departure_rate);
                        //  current departure requests
        for (int j = 0; j < number_departures; ++j) {
            Plane current_plane(flight_number++, current_time, departing);
            if (departure_runway.can_depart(current_plane) != success) {
                current_plane.refuse();
            }
        }
        
        Plane moving_plane;
        if (arrival_runway.activity(current_time, moving_plane) == land) {
            moving_plane.land(current_time);
        } else {
            run_idle(current_time, 1);
        }
        if (departure_runway.activity(current_time, moving_plane) == takeOff) {
            moving_plane.fly(current_time);
        } else {
            run_idle(current_time, 2);
        }
    }
    arrival_runway.shut_down(end_time);

}
//solve the problem3
void problem3(int end_time, int queue_limit, double arrival_rate, double departure_rate){
    
    int flight_number = 0;
    Runway::reset();
    Random variable;
    Runway arrival_runway(queue_limit);
    Runway departure_runway(queue_limit);
    for (int current_time = 0; current_time < end_time; ++current_time) {
                        //  loop over time intervals
        int number_arrivals;
        if (manual) 
        {
            cout << "Please enter the number of planes which arrive the airport at this moment (time " << current_time << ")" << endl;
            number_arrivals =getNum();
        }
        else number_arrivals = variable.poisson(arrival_rate);
                        //  current arrival requests
        bool solveBacklog = 0;
        for (int i = 0; i < number_arrivals; ++i) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrival_runway.can_land(current_plane) != success) {
                //use departure_runway to land 
                if (!solveBacklog) {
                    Plane moving_plane;
                    if (arrival_runway.activity(current_time, moving_plane) == land) {
                        moving_plane.land(current_time);
                    }
                } else {
                    current_plane.refuse();
                }
            }
        }
        int number_departures;
        if (manual) 
        {
            cout << "Please enter the number of planes which leave the airport at this moment (time " << current_time << ")" << endl;
            number_departures =getNum();
        }
        else number_departures = variable.poisson(departure_rate);
                        //  current departure requests
        for (int j = 0; j < number_departures; ++j) {
            Plane current_plane(flight_number++, current_time, departing);
            if (departure_runway.can_depart(current_plane) != success) {
                current_plane.refuse();
            }
        }
        
        Plane moving_plane;
        if (arrival_runway.activity(current_time, moving_plane) == land) {
            moving_plane.land(current_time);
        } else {
            run_idle(current_time, 1);
        }
        if (!solveBacklog){
            if (departure_runway.activity(current_time, moving_plane) == takeOff) {
                moving_plane.fly(current_time);
            } else {
                run_idle(current_time, 2);
            }
        } 
    }
    arrival_runway.shut_down(end_time);
    
}
//solve the problem4
void problem4(int end_time, int queue_limit, double arrival_rate, double departure_rate){
    
    int flight_number = 0;
    Runway::reset();
    Random variable;
    Runway arrival_runway(queue_limit);
    Runway departure_runway(queue_limit);
    Runway flexible_runway(queue_limit);
    for (int current_time = 0; current_time < end_time; ++current_time) {
                        //  loop over time intervals
        int number_arrivals;
        if (manual) 
        {
            cout << "Please enter the number of planes which arrive the airport at this moment (time " << current_time << ")" << endl;
            number_arrivals =getNum();
        }
        else number_arrivals = variable.poisson(arrival_rate);
                        //  current arrival requests
        for (int i = 0; i < number_arrivals; ++i) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrival_runway.can_land(current_plane) != success) {
                if (flexible_runway.can_land(current_plane) != success) {
                    current_plane.refuse();
                }
            }
        }
        int number_departures;
        if (manual) 
        {
            cout << "Please enter the number of planes which leave the airport at this moment (time " << current_time << ")" << endl;
            number_departures =getNum();
        }
        else number_departures = variable.poisson(departure_rate);
                        //  current departure requests
        for (int j = 0; j < number_departures; ++j) {
            Plane current_plane(flight_number++, current_time, departing);
            if (departure_runway.can_depart(current_plane) != success) {
                if (!flexible_runway.isLandingEmpty()){
                    flexible_runway.can_depart(current_plane);
                } else {
                    current_plane.refuse();
                }
            }
        }
        
        Plane moving_plane;
        if (arrival_runway.activity(current_time, moving_plane) == land) {
            moving_plane.land(current_time);
        } else {
            run_idle(current_time, 1);
        }
        if (departure_runway.activity(current_time, moving_plane) == takeOff) {
            moving_plane.fly(current_time);
        } else {
            run_idle(current_time, 2);
        }
        switch (flexible_runway.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case takeOff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time, 3);
        }
    }
    arrival_runway.shut_down(end_time);
    
}

void problem5(int end_time, int queue_limit, double arrival_rate, double departure_rate) {
    
    int left_limit, right_limit;
    if (!manual)
    {
        cout << "Please enter the lowest number of fuels" << endl;
        left_limit = getNum();
        cout << "Please enter the highest number of fuels" << endl;
        right_limit = getNum();
    }
    
    int flight_number = 0;
    int crash_number = 0;
    Runway::reset();
    Random variable;
    Runway small_airport(queue_limit);
    for (int current_time = 0; current_time < end_time; ++current_time) {
                        //  loop over time intervals
        int number_arrivals;
        if (manual) 
        {
            cout << "Please enter the number of planes which arrive the airport at this moment (time " << current_time << ")" << endl;
            number_arrivals =getNum();
        }
        else number_arrivals = variable.poisson(arrival_rate);
                        //  current arrival requests
        for (int i = 0; i < number_arrivals; ++i) {
            int fuel;
            if (manual)
            {
                cout << "Please enter the number of fuel of " << i << "th plane" << endl;
                fuel = getNum();
            }else fuel = variable.random_integer(left_limit, right_limit);
            Plane current_plane(flight_number++, current_time, arriving, fuel);
            if (small_airport.can_land(current_plane) != success) {
                current_plane.refuse();
            }
        }
        
        int number_departures;
        if (manual) 
        {
            cout << "Please enter the number of planes which leave the airport at this moment (time " << current_time << ")" << endl;
            number_departures =getNum();
        }
        else number_departures = variable.poisson(departure_rate);
                        //  current departure requests
        for (int j = 0; j < number_departures; ++j) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success) {
                current_plane.refuse();
            }
        }
        
        Plane moving_plane;
        switch (small_airport.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case takeOff:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time, 1);
        }
       // cout << "HaHa" << endl;
        crash_number += small_airport.check_crash(current_time);
    }
    small_airport.shut_down(end_time);
    cout << crash_number << " planes crash!" << endl;
    
}



