#include <stdio.h>
#include <string.h>
#include "shell.h"

struct Command commands[MAX_COMMANDS];
int command_count = 0;

int load_registry(const char *registry_path) {
    FILE *file = fopen(registry_path, "r");
    if (!file) {
        return -1;  // File doesn't exist or can't open
    }
    
    char line[512];
    command_count = 0;
    
    while (fgets(line, sizeof(line), file) && command_count < MAX_COMMANDS) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Parse "phrase:binary"
        char *phrase = strtok(line, ":");
        char *binary = strtok(NULL, ":");
        
        if (phrase && binary) {
            strcpy(commands[command_count].phrase, phrase);
            strcpy(commands[command_count].binary, binary);
            command_count++;
        }
    }
    
    fclose(file);
    return command_count;
}