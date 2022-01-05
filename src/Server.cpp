#include "Server.hpp"
#include "Request.hpp"
#include "Response.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <netdb.h>

#include <sys/socket.h>
#include <unistd.h>

namespace simple_http {
Server::Server(const std::string &port, router_t router)
    : _router{router}, _port{port} {
    addrinfo *results;
    addrinfo hints;
    std::memset(&hints, 0, sizeof(hints));

    // Get the necessary info about the server
    int err = getaddrinfo(NULL, port.c_str(), &hints, &results);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(err));
        exit(EXIT_FAILURE);
    }

    addrinfo *result;
    sockaddr peer_addr;
    size_t peer_addr_len;

    // Create and bind socket
    for (result = results; result != NULL; result = result->ai_next) {
        _server =
            socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        int i = 1;
        setsockopt(_server, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));

        if (_server == -1) {
            continue;
        }

        if (bind(_server, result->ai_addr, result->ai_addrlen) == 0) {
            break;
        }

        close(_server);
    }

    freeaddrinfo(results);

    if (result == NULL) {
        std::string error = "Could not create and/or bind socket";
        std::perror(error.c_str());
        exit(EXIT_FAILURE);
    }

    if (listen(_server, MAX_CONNECTIONS) == -1) {
        std::string error = "Could not listen at port " + port;
        std::perror(error.c_str());
        exit(EXIT_FAILURE);
    }

    _is_running = true;
}

Server::~Server() { close(_server); }

void Server::serve() {
    std::cout << "Currently listening at \033[3;1;4mhttps://localhost:" << _port
              << "\033[0m\n";
    while (_is_running) {
        sockaddr peer_addr;
        socklen_t peer_addr_len = sizeof(peer_addr);

        socket_t client = accept(_server, &peer_addr, &peer_addr_len);
        if (client == -1) {
            perror("Invalid client");
            exit(EXIT_FAILURE);
        }

        char raw_req[65536];
        memset(raw_req, 0, sizeof(raw_req));

        size_t rd = read(client, raw_req, sizeof(raw_req));
        raw_req[rd] = '\0';

        auto optional{Request::parse(raw_req)};
        if (!optional.has_value()) {
            // This should not exit the program, instead send a 500 status page
            std::cerr << "Error trying to parse request.\n";
            exit(EXIT_FAILURE);
        }

        Request req = optional.value();
        Response res{client, req.get_http_version()};

        _router(req, res);

        close(client);
    }
}

} // namespace simple_http