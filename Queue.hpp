#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include "Plane.hpp"
#include "Random.hpp"

typedef Plane Queue_entry;
class Extended_queue : public std::queue<Queue_entry> {
public:
    Error_code append(const Queue_entry &x);
    Error_code serve();
    Error_code retrieve(Queue_entry &item) const;
    void clear();
};
Error_code Extended_queue::append(const Queue_entry &x) {
    push(x);
    return success;
}

Error_code Extended_queue::serve() {
    if (empty()) {
        return fail;
    } else {
        pop();
    }
    return success;
}

Error_code Extended_queue::retrieve(Queue_entry &item) const {
    if (size() <= 0) {
        return underflow;
    } else {
        item = front();
    }
    return success;
}
void Extended_queue::clear(){
    while (empty()) {
        pop();
    }
}
#endif