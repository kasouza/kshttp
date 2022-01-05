#include "Request.hpp"
#include "Response.hpp"
#include "Server.hpp"
#include <iostream>

void router(simple_http::Request req, simple_http::Response res) {
    res.text("<h1>Saske</h1>").send();
}

int main() {
    simple_http::Server server{"8080", router};
    server.serve();

    return 0;
}