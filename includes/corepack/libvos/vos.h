#ifndef VOS_H
#define VOS_H

#include <stdbool.h>

// Output management
void demand_stdout(bool await_ack);
void request_stdout(bool await_ack);
void release_stdout(void);

#endif