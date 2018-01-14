#include <iostream>
#include "Solution.h"
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;


bool manual = false;

void initialize(int &end_time, int &queue_limit,
                double &arrival_rate, double &departure_rate) {
    /*Pre:  The user specifies the number of time units in the simulation, the maximal
            queue sizes premitted, and the expected arrival and departure rates for
            the airport.
      Post: The program prints instructions and initializes the parameters end_time,
            queue_limit, arrival_rate, and departure_rate to the specified values.
      Uses: utility function user_says_yes*/
    cout << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land " 
         << "or take off at any time?" << flush;
    queue_limit = getNum();
    cout << "How many units of time will the simulation run?" << flush;
    end_time = getNum();
    bool acceptable;
    if (!manual)
    {
        do {
            cout << "Expected number of arrivals per unit time?" << flush;
            arrival_rate = getNum();
            cout << "Expected number of departures per unit time?" << flush;
            departure_rate = getNum();
            if (arrival_rate < 0.0 || departure_rate < 0.0) {
                cout << "These rates must be nonnegative." << endl;
            } else {
                acceptable = true;
            }
            if (acceptable && arrival_rate + departure_rate > 1.0) {
                cerr << "Safety Warning: This airport will become saturated." << endl;
            }
        } while (!acceptable);
    }

}

int main() {    //Airport simulation program
    /*Pre:  The user must supply the number of time intervals the simulation is to run,
            the expected number of planes arriving, the expected number of planes 
            departing per time interval, and the maximum allowed size for runway queues.
      Post: The progrram performs a random simulation of the ariport, showing the status 
            of the runway at each time interval, and prints out a summary of airport 
            operation at the conclusion.
      Uses: Classes Runway, Plane, Random and functions run_idle, initialize.*/
    int end_time;       //  time to run simulation
    int queue_limit;    //  size of Runway queues
    double arrival_rate, departure_rate;

    for(;;) {
        //choose problem to solve
        cout<< "Enter the serial number of operation you want to do: "<<endl;
        cout<< "[0] change input mode(manual/auto). Current mode is " << (manual?"manual":"auto") <<endl;
        cout<< "[1] an airport with only one runway." <<endl;
        cout<< "[2] an airport with two runways, one always used for landingsand onealwaysused for takeoffs." <<endl;
        cout<< "[3] an airport with two runways, one usually used for landings and one usually used for takeoffs."
               "If one of the queues is empty, then both runways can be used for the other queue. Also, "
               "if the landing queue is full and another plane arrives to land, "
               "then takeoffs will be stopped and both runways used to clear the backlog of landing planes. " << endl;
        cout<< "[4] an airport with three runways, one always reserved for each of landing and takeoff and "
               "the third used for landings unless the landing queue is empty, in which case it can be used for takeoffs."<<endl;
        cout<< "[5] an airport with only one runway, but the plane may run out of fuel and then crash" <<endl;
        cout<< "Or Enter [Q] or [q] to exit the program" << endl;
        string opt;
        opt.clear();
        while (opt.empty()) getline(cin, opt);   
        if (opt[0] == 'Q' || opt[0] == 'q') break;     
        if (opt.size() > 1 || opt[0] < '0' || opt[0] > '6') {
            cout<<"please enter valid operation" <<endl;
            cin >> opt;
            continue;
        }
        switch (opt[0]){
        case '0':
            manual = !manual;
            break;
        case '1':
            initialize(end_time, queue_limit, arrival_rate, departure_rate);
            problem1(end_time, queue_limit, arrival_rate, departure_rate);
            break;
        case '2':
            initialize(end_time, queue_limit, arrival_rate, departure_rate);
            problem2(end_time, queue_limit, arrival_rate, departure_rate);
            break;
        case '3':
            initialize(end_time, queue_limit, arrival_rate, departure_rate);
            problem3(end_time, queue_limit, arrival_rate, departure_rate);
            break;
        case '4':
            initialize(end_time, queue_limit, arrival_rate, departure_rate);
            problem4(end_time, queue_limit, arrival_rate, departure_rate);
            break;
        case '5':
            initialize(end_time, queue_limit, arrival_rate, departure_rate);
            problem5(end_time, queue_limit, arrival_rate, departure_rate);
            break;
          
            
        }        
    }
    
    return 0;
}
