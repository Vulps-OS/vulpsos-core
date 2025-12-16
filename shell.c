#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/reboot.h>

int main(){
    char input[256];

    printf("VulpsOS Shell V-0.001-Proof-Of-Concept \n");
    while(1) {
        printf("vulpsos>");
        fflush(stdout);

        fgets(input, 256, stdin);

        if(strncmp(input, "now stop", 8) == 0){
            printf("Shutting down... \n");
            sync();
            reboot(RB_POWER_OFF);
        }

        printf("%s", input);
    }

    return 0;
}