#ifndef C_SERVE_MAIN_HPP
#define C_SERVE_MAIN_HPP

#include <stddef.h>

typedef int socket_t;

socket_t start_server(const char *port);
void serve(socket_t server);

void respond(char *req, size_t req_len, socket_t client);

#endif