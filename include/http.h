#ifndef CHARE_HTTP_H
#define CHARE_HTTP_H

/**
 * Reads an HTTP request from the given socket, parses it,
 * and sends back the appropriate HTTP response.
 * @param client_socket The file descriptor for the connected client.
 * @param filepath The path to the file.
 */
void handle_client(int client_socket, const char *filepath);

#endif //CHARE_HTTP_H