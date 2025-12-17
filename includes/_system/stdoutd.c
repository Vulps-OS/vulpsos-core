#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/_system/stdout"

int main() {
    printf("[stdoutd] Service starting...\n");
    
    // Create socket
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        printf("[stdoutd] Failed to create socket\n");
        return 1;
    }
    
    // Bind to path
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);
    unlink(SOCKET_PATH);  // Remove if exists
    
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("[stdoutd] Failed to bind socket\n");
        return 1;
    }
    
    // Listen for connections
    listen(sock, 5);
    printf("[stdoutd] Listening on %s\n", SOCKET_PATH);
    
    // TODO: Accept connections and handle messages
    while(1) {
        sleep(1);
    }
    
    return 0;
}