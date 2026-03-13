#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include "http.h"
#include "network.h"

#define PORT 8080

volatile int keep_running = 1;

void handle_sigint(int sig) {
    printf("shutting down chare server...");
    keep_running = 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: %s <file_to_send>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];

    signal(SIGINT, handle_sigint);

    const int server_fd = init_server(PORT);
    printf("chare server live on port %d.\n", PORT);

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    while (keep_running) {
        const int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

        if (client_socket < 0) {
            if (!keep_running) break;

            perror("failed to accept connection.");
        }

        handle_client(client_socket, filepath);
    }

    printf("closing network sockets...");
    close(server_fd);
    printf("goodbye!");

    return 0;
}