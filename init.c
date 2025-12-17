#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void launch_services() {
    FILE *f = fopen("/conf/launchables", "r");
    if (!f) {
        printf("Init: No launchables file found, skipping services\n");
        return;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Skip empty lines or comments
        if (line[0] == '\0' || line[0] == '#') continue;
        
        printf("Init: Launching %s\n", line);
        
        pid_t pid = fork();
        if (pid == 0) {
            // Child - exec the service
            execl(line, line, NULL);
            printf("Init: Failed to launch %s\n", line);
            _exit(1);
        }
        // Parent continues to next service
    }
    
    fclose(f);
}

int main() {
    printf("Init starting...\n");
    
    launch_services();
    
    printf("Init: Launching shell\n");
    char *argv[] = {"/corepack/shell/shell", NULL};
    char *envp[] = {NULL};
    execve("/corepack/shell/shell", argv, envp);
    printf("Init: Failed to start shell!\n");
    while(1) sleep(1);
    return 0;
}