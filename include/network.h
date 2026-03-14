#ifndef CHARE_NETWORK_H
#define CHARE_NETWORK_H

#include <stdint.h>

/**
 * Returns of the local IP of the machine running chare. Used for convenience when sharing.
 * @param buffer Where the local IP is written
 */
void get_local_ip(char *buffer);

/**
 * Initializes a TCP socket, binds it to the specified port,
 * and starts listening for incoming connections.
 * @param port The port number to listen on (e.g. 8080)
 * @return The file descriptor (integer) of the listening server socket.
 */
int init_server(uint16_t port);

#endif //CHARE_NETWORK_H