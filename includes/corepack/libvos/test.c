#include <stdio.h>
#include "vos.h"

int main() {
    request_stdout(false);
    printf("Hello from libvos!\n");
    release_stdout();
    return 0;
}