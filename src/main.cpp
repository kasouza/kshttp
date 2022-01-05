#include "Request.hpp"
#include "Response.hpp"
#include "Server.hpp"
#include <iostream>

void router(kshttp::Request req, kshttp::Response res) {
    res.text("<h1>Saske</h1>").send();
}

int main() {
    kshttp::Server server{"8080", router};
    server.serve();

    return 0;
}