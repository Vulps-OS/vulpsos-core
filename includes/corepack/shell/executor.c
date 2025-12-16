#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

int execute_command(char *input) {
    // Remove trailing newline
    input[strcspn(input, "\n")] = 0;
    
    // Try to match registered commands (longest first)
    for (int i = 0; i < command_count; i++) {
        int len = strlen(commands[i].phrase);
        if (strncmp(input, commands[i].phrase, len) == 0) {
            // Found a match, execute it
            pid_t pid = fork();
            if (pid == 0) {
                // Child process - execute the binary
                execl(commands[i].binary, commands[i].binary, input, NULL);
                printf("Failed to execute: %s\n", commands[i].binary);
                return 1;
            } else {
                // Parent process - wait for child
                wait(NULL);
                return 0;
            }
        }
    }
    
    // No match found
    printf("Command not found: %s\n", input);
    return 1;
}