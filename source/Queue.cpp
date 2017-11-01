#include "Queue.h"




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
        item = top();
    }
    return success;
}
void Extended_queue::clear(){
    while (empty()) {
        pop();
    }
}