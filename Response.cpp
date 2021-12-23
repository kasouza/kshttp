#include "Response.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <sys/socket.h>

namespace simple_http {
Response::Response(socket_t client, std::string http_version)
    : _client{client}, _http_version{http_version} {}
Response &Response::status_code(std::string code) {
    _status_code = code;
    // Look up for the status text or something
    return *this;
}

Response &Response::header(std::string header, std::string value) {
    _headers[header] = value;
    return *this;
}

Response &Response::text(std::string content) {
    _content = content;
    return *this;
}

void Response::send() {
    std::stringstream s;
    s << _http_version << " " << _status_code << " OK\r\n";
    s << "\r\n";
    s << _content;

    std::string content = s.str();
    int sent = ::send(_client, content.c_str(), content.length(), 0);
    if (sent < 0) {
        perror("Error sending response");
        exit(EXIT_FAILURE);
    }
}

} // namespace simple_http