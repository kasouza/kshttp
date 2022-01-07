#include "Router.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Status.hpp"

#include <iostream>

namespace kshttp {

std::map<std::string, HTTPMethod> http_methods{
    {"GET", HTTPMethod::GET},         {"HEAD", HTTPMethod::HEAD},
    {"POST", HTTPMethod::POST},       {"PUT", HTTPMethod::PUT},
    {"DELETE", HTTPMethod::DELETE},   {"CONNECT", HTTPMethod::CONNECT},
    {"OPTIONS", HTTPMethod::OPTIONS}, {"TRACE", HTTPMethod::TRACE},
    {"PATCH", HTTPMethod::PATCH},
};

std::optional<HTTPMethod> Route::parse_method(std::string method) {
    if (http_methods.find(method) != http_methods.end()) {
        return http_methods[method];
    }

    return {};
}

std::optional<route_cb_t> Route::get_callback(HTTPMethod method) {
    if (has_method(method)) {
        return _methods[method];
    }

    return {};
}

void Router::resolve(const Request &req, Response &res) {
    const std::string &path{req.get_path()};

    if (_routes.find(path) != _routes.end()) {
        Route &route{_routes[path]};
        std::optional<HTTPMethod> method_opt{
            Route::parse_method(req.get_method())};

        if (method_opt) {
            std::optional<route_cb_t> callback_opt{
                route.get_callback(method_opt.value())};

            if (callback_opt) {
                // Everything is fine, calling the user defined callback
                callback_opt.value()(req, res);
            } else {
                // 405 Method not allowed
                std::cerr << "Method not allowed\n";
                res.status(405).text(get_error_page(405)).send();
            }
        } else {
            // Bad request method invalid
            std::cerr << "INVALID METHOD: " << req.get_method() << '\n';
            res.status(400).text(get_error_page(400)).send();
        }
    } else {
        // 404 not found
        std::cerr << "Page not found: " << path << '\n';
        res.status(404).text(get_error_page(404)).send();
    }
}
} // namespace kshttp