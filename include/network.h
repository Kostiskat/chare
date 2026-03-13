#ifndef CHARE_NETWORK_H
#define CHARE_NETWORK_H

#include <stdint.h>

/**
 * Initializes a TCP socket, binds it to the specified port,
 * and starts listening for incoming connections.
 * @param port The port number to listen on (e.g. 8080)
 * @return The file descriptor (integer) of the listening server socket.
 */
int init_server(uint16_t port);

#endif //CHARE_NETWORK_H