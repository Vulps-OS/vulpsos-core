#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Init starting...");
    execve("/bin/shell", NULL, NULL);
    while(1) sleep(1);
    return 0;
}