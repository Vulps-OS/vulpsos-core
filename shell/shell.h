// shell.h
#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMANDS 100
#define MAX_INPUT 256

// Command structure
struct Command {
    char phrase[256];
    char binary[256];
};

// Global command registry
extern struct Command commands[MAX_COMMANDS];
extern int command_count;

// registry.c functions
int load_registry(const char *registry_path);

// executor.c functions
int execute_command(char *input);

#endif