#include "Request.hpp"
#include "Response.hpp"
#include "Router.hpp"
#include "Server.hpp"

#include <iostream>

int main() {
    kshttp::Router router;

    router.get("/", [](const kshttp::Request &req, kshttp::Response &res) {
        res.text("<h1>AMOGUS</h1>").send();
    });

    router.post("/saske", [](const kshttp::Request &req, kshttp::Response &res) {
        res.text("<h1>Amogus</h1>").send();
    });

    kshttp::Server server{"8080", router};
    server.serve();

    return 0;
}