#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>

#include "http.h"
#include "network.h"

#define PORT 8080

volatile int keep_running = 1;

char local_ip[100];



void handle_sigint(int sig) {
    printf("aborting...\n");
    exit(0);
}

int main(const int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: %s <file_to_send>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];

    signal(SIGINT, handle_sigint);

    get_local_ip(local_ip);

    const int server_fd = init_server(PORT);
    printf("chare server live on %s:%d.\n", local_ip, PORT);
    printf("you may scan the qr code with a mobile device to instantly download the file!\n\n");

    char qr_command[256];
    snprintf(qr_command, sizeof(qr_command), "qrencode -t UTF8 \"http://%s:%d\"\n", local_ip, PORT); // HTTP links are fine since this is running locally

    system(qr_command);


    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    while (keep_running) {
        const int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

        if (client_socket < 0) {
            if (!keep_running) break;

            perror("failed to accept connection.");
        }

        handle_client(client_socket, filepath);

        printf("file sent! shutting down...\n");
        break;
    }

    printf("closing network sockets...\n");
    close(server_fd);
    printf("goodbye!\n");

    return 0;
}