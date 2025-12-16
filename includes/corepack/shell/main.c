#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/reboot.h>
#include "shell.h"

int main() {
    char input[MAX_INPUT];
    
    printf("VulposOS Shell V-0.002-Command-Registry\n");
    
    // Load command registry
    if (load_registry("/etc/vulpos/commands.registry") < 0) {
        printf("Warning: Could not load command registry\n");
    }
    
    // Main loop
    while(1) {
        printf("vulpos> ");
        fflush(stdout);
        
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            break;
        }
        
        // Check for built-in commands
        if (strncmp(input, "now stop", 8) == 0) {
            printf("Shutting down...\n");
            sync();
            reboot(0x4321fedc);
        }
        
        // Execute command
        execute_command(input);
    }
    
    return 0;
}