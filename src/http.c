#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "platform_io.h"
#include "http.h"

void handle_client(const int client_socket, const char *filepath) {
    printf("new client connected. processing request...\n");

    char buffer[4096];
    const ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
    }

    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("error: file not found\n");
        const char *err = "HTTP/1.1 404 Not Found\r\n\r\nFile not found.";
        send(client_socket, err, strlen(err), 0);
        close(client_socket);
        return;
    }

    fseek(file, 0, SEEK_END);
    const long fsize = ftell(file);
    fclose(file);

    char response_header[512];
    snprintf(response_header, sizeof(response_header),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: application/octet-stream\r\n"
                 "Content-Disposition: attachment; filename=\"%s\"\r\n" // Tells browser to download it
                 "Content-Length: %ld\r\n"
                 "\r\n",
                 filepath, fsize);

    send(client_socket, response_header, strlen(response_header), 0);

    if (stream_file_to_socket(client_socket, filepath) == 0) {
        printf("file sent successfully.\n");
    } else {
        printf("error sending file.\n");
    }

    close(client_socket);
    printf("client disconnected\n");
}
