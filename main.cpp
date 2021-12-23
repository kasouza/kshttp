#include "Request.hpp"
#include "Response.hpp"
#include "Server.hpp"
#include <iostream>

int main() {
    simple_http::Server server{"8080", [](const auto &req, auto &res) {
                                   res.text("<h1>sASKE</h1>").send();
                               }};
    server.serve();

    // simple_http::Request::parse("GET / HTTP/1.1\r\n"
    //                             "Host: localhost:8080\r\n"
    //                             "User-Agent: curl/7.80.0\r\n"
    //                             "Accept: */*\r\n\r\n<h1>sasake</h1>");

    return 0;
}