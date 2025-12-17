#ifndef VOS_H
#define VOS_H

#include <stdbool.h>

// Output management
void demand_stdout();
void request_stdout();
void release_stdout(bool await_ack);

#endif