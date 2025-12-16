#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Init starting...\n");
    execve("/corepack/shell", NULL, NULL);
    printf("Init: Failed to start shell!\n");
    while(1) sleep(1);
    return 0;
}