#ifndef PLANE_H
#define PLANE_H

#include <iostream>
using namespace std;

enum Plane_status {null, arriving, departing};
class Plane {
private:
    int flt_num;
    int clock_start;
    int clock_deadline;
    Plane_status state;

public:
    Plane();
    Plane(int flt, int time, Plane_status status, int fuel = 0);
    void refuse() const;
    void land(int time) const;
    void fly(int time) const;
    int started() const;

    bool operator<(const Plane &b)const{
        if (clock_deadline != b.clock_deadline) return clock_deadline > b.clock_deadline;
        return flt_num > b.flt_num;
    }
    int get_deadline(){
        return clock_deadline;
    }
    int get_flt_num(){
        return flt_num;
    }
};



#endif
