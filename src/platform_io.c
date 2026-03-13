#include "platform_io.h"
#include <stdio.h>
#include <sys/socket.h>

// --- LINUX ---
#ifdef __linux__
#include <sys/sendfile.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int stream_file_to_socket(int client_socket, const char *filepath) {
    int file_fd = open(filepath, O_RDONLY);
    if (file_fd < 0) return -1;

    struct stat stat_buf;
    fstat(file_fd, &stat_buf);

    off_t offset = 0;
    sendfile(client_socket, file_fd, &offset, stat_buf.st_size);

    close(file_fd);
    return 0;
}

// --- FALLBACK METHOD ---
#else
#include <stdlib.h>

int stream_file_to_socket(int client_socket, const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (!file) return -1;

    char buffer[8192];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(client_socket, buffer, bytes_read, 0);
    }

    fclose(file);
    return 0;
}

#endif