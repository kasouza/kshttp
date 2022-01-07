#ifndef KASOUZA_KSHTTP_INCLUDE_ROUTER_HPP
#define KASOUZA_KSHTTP_INCLUDE_ROUTER_HPP

#include <functional>
#include <map>
#include <optional>
#include <string>

namespace kshttp {

class Request;
class Response;

// Callback to be called when a route is reached
using route_cb_t = std::function<void(const Request &req, Response &res)>;

enum class HTTPMethod {
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE,
    PATCH,
};

class Route {
  private:
    std::map<HTTPMethod, route_cb_t> _methods;

  public:
    Route() {}

    static std::optional<HTTPMethod> parse_method(std::string method);

    inline void add_method(HTTPMethod method, route_cb_t callback) {
        _methods[method] = callback;
    }

    inline bool has_method(HTTPMethod method) {
        return _methods.find(method) != _methods.end();
    }

    std::optional<route_cb_t> get_callback(HTTPMethod method);
};

class Router {
  private:
    std::map<std::string, Route> _routes;

  public:
    Router(){};

    /**
     * @brief Add a route.
     *
     * @param method HTTP method to be used by the route
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void route(HTTPMethod method, const std::string &path,
                      route_cb_t callback) {
        _routes[path].add_method(method, callback);
    }

    /**
     * @brief Add a GET route.
     *
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void get(const std::string &path, route_cb_t callback) {
        route(HTTPMethod::GET, path, callback);
    }

    /**
     * @brief Add a HEAD route.
     *
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void head(const std::string &path, route_cb_t callback) {
        route(HTTPMethod::HEAD, path, callback);
    }

    /**
     * @brief Add a POST route.
     *
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void post(const std::string &path, route_cb_t callback) {
        route(HTTPMethod::POST, path, callback);
    }

    /**
     * @brief Add a PUT route.
     *
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void put(const std::string &path, route_cb_t callback) {
        route(HTTPMethod::PUT, path, callback);
    }

    /**
     * @brief Add a DELETE route.
     *
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void _delete(const std::string &path, route_cb_t callback) {
        route(HTTPMethod::DELETE, path, callback);
    }

    /**
     * @brief Add a CONNECT route.
     *
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void connect(const std::string &path, route_cb_t callback) {
        route(HTTPMethod::CONNECT, path, callback);
    }

    /**
     * @brief Add a OPTIONS route.
     *
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void options(const std::string &path, route_cb_t callback) {
        route(HTTPMethod::OPTIONS, path, callback);
    }

    /**
     * @brief Add a TRACE route.
     *
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void trace(const std::string &path, route_cb_t callback) {
        route(HTTPMethod::TRACE, path, callback);
    }

    /**
     * @brief Add a PATCH route.
     *
     * @param path When this path is acessed by the client, `callback` will be
     * called
     * @param callback A callback to be called when `path` is acessed
     */
    inline void patch(const std::string &path, route_cb_t callback) {
        route(HTTPMethod::PATCH, path, callback);
    }

    /**
     * @brief Execute a route based on the request. This method is used
     * internally by the server and don't need to be called by the user.
     *
     * @param req
     * @param res
     */
    void resolve(const Request &req, Response &res);
};
} // namespace kshttp

#endif