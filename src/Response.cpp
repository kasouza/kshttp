#include "Response.hpp"
#include "Status.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <sys/socket.h>

namespace kshttp {
Response::Response(socket_t client, std::string http_version)
    : _client{client}, _http_version{http_version} {}

Response &Response::status(unsigned short status) {
    assert(is_status_valid(status));

    _status_code = status;
    // Look up for the status text or something
    return *this;
}


Response &Response::header(std::string header, std::string value) {
    _headers[header] = value;
    return *this;
}


Response &Response::text(std::string body) {
    _body = body;
    return *this;
}


void Response::send() {
    if (!is_status_valid(_status_code)) {
        // TODO: Get response from a file or something instead of hardcode it
        std::cerr << "Invalid status code: " << _status_code << '\n';
        _status_code = 500;
        _body = get_error_page(500);
    }

    std::stringstream s;
    s << _http_version << " " << _status_code << " " << get_status_text(_status_code) << "\r\n";
    s << "\r\n";
    s << _body;

    std::string content = s.str();
    int sent = ::send(_client, content.c_str(), content.length(), 0);
    if (sent < 0) {
        perror("Error sending response");
        exit(EXIT_FAILURE);
    }
}

} // namespace simple_http