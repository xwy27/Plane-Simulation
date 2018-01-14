#ifndef SOLUTION_H
#define SOLUTION_H
//get a double number from input
double getNum(double l = 0, double r = 100000000);//to get [l, r) integer
//output in the time the x runway is idle
void run_idle(int time,int number);
//solve the problem1
void problem1(int end_time, int queue_limit, double arrival_rate, double departure_rate);
//solve the problem2
void problem2(int end_time, int queue_limit, double arrival_rate, double departure_rate);
//solve the problem3
void problem3(int end_time, int queue_limit, double arrival_rate, double departure_rate);
//solve the problem4
void problem4(int end_time, int queue_limit, double arrival_rate, double departure_rate);
//solve the problem5
void problem5(int end_time, int queue_limit, double arrival_rate, double departure_rate);

#endif