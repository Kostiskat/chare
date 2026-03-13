#ifndef CHARE_PLATFORM_IO_H
#define CHARE_PLATFORM_IO_H

#include <stddef.h>

/**
 * Reads a file from the hard drive and streams it directly to the network socket
 * using the fastest method available on the current OS.
 * @param client_socket The active network socket
 * @param filepath The path to the file on disk.
 * @return 0 on success, -1 on failure
 */
int stream_file_to_socket(int client_socket, const char *filepath);

#endif //CHARE_PLATFORM_IO_H