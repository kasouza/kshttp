#include "main.hpp"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <netdb.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

#include <cstring>

#include <errno.h>
#include <utility>

#define PORT "8080"
#define MAX_CONNECTIONS 1000000
#define MAX_CLIENTS 1000

socket_t start_server(const char *port) {
  // fd == File descriptor
  socket_t server;
  struct addrinfo hints;
  struct addrinfo *results;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  int err = getaddrinfo(NULL, port, &hints, &results);
  if (err != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(err));
    exit(EXIT_FAILURE);
  }

  struct addrinfo *result = NULL;
  for (result = results; result != NULL; result = result->ai_next) {
    int option = 1;

    server = socket(result->ai_family, result->ai_socktype, 0);
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (server == -1)
      continue;

    if (bind(server, result->ai_addr, result->ai_addrlen) == 0)
      break;

    close(server);
  }

  freeaddrinfo(results);

  if (result == NULL) {
    fprintf(stderr, "Could not listen: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  if (listen(server, MAX_CONNECTIONS) != 0) {
    fprintf(stderr, "Error listening: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  return server;
}

std::vector<std::string> tokenize(const std::string &s,
                                  std::string delimiter = " ") {
  std::vector<std::string> tokens;

  int start = 0;
  int end = s.find(delimiter);

  while (end != -1) {
    tokens.push_back(s.substr(start, end - start));
    start = end + delimiter.size();
    end = s.find(delimiter, start);
  }

  tokens.push_back(s.substr(start));

  return tokens;
}

void respond(char const *req, size_t req_len, socket_t client) {
  auto headers = tokenize(req, "\n");
  std::map<std::string, std::string> headers_map;

  std::string first_line{headers[0]};
  headers.erase(headers.begin());

  auto first_line_tokens = tokenize(first_line);

  std::for_each(headers.begin(), headers.end(), [&headers_map](std::string s) {
    s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());

    if (!s.empty()) {
      auto tokens = tokenize(s);
      std::cerr << "sas: " << tokens[0] << '\n';
      headers_map.emplace(tokens[0], tokens[1]);
      std::cerr << "ke\n";
    }
  });

  char res[] = "HTTP/1.1 200 OK\n"
               "\n"
               "<h1>SASKE</h1>";

  int sent = send(client, res, strlen(res) + 1, 0);

  if (sent < 0) {
    fprintf(stderr, "Error sending response: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  close(client);
}

void serve(socket_t server) {
  socket_t clients[MAX_CLIENTS];
  std::fill_n(clients, sizeof(clients), -1);

  std::thread *threads[MAX_CLIENTS];
  std::fill_n(threads, sizeof(threads), nullptr);

  socket_t client = -1;

  printf("Currently listening at \033[3;1;4mhttps://localhost:8080\033[0m\n");

  size_t current_client = 0;

  while (1) {
    if (clients[current_client] == -1) {
      struct sockaddr peer_addr;
      socklen_t peer_addr_len;

      clients[current_client] = accept(server, &peer_addr, &peer_addr_len);

      if (clients[current_client] < 0) {
        fprintf(stderr, "Error\n");
      } else {
        char buf[65536];
        memset(buf, 0, sizeof(char) * 256);

        ssize_t rd = read(clients[current_client], buf, sizeof(buf));
        buf[rd] = '\0';

        threads[current_client] =
            new std::thread([buf, &clients, current_client]() {
              respond(buf, strlen(buf) + 1, clients[current_client]);
            });
      }
    } else {
      if (threads[current_client] && threads[current_client]->joinable()) {
        threads[current_client]->join();
        delete threads[current_client];

        threads[current_client] = nullptr;
        clients[current_client] = -1;
      }
    }

    current_client = (current_client + 1) % MAX_CLIENTS;
  }
}

int main() {
  socket_t server = start_server(PORT);

  serve(server);

  close(server);

  return 0;
}