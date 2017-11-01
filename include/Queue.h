#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <queue>
#include "Plane.h"
#include "Random.h"
typedef Plane Queue_entry;



class Extended_queue : public std::priority_queue<Queue_entry> {
public:
    Error_code append(const Queue_entry &x);
    Error_code serve();
    Error_code retrieve(Queue_entry &item) const;
    void clear();
 
};

#endif