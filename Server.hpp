#ifndef KASOUZA_SIMPLE_HTTP_SERVER_HPP
#define KASOUZA_SIMPLE_HTTP_SERVER_HPP

#include <functional>
#include <string>

namespace simple_http {

class Request;
class Response;

using router_t = std::function<void(const Request &req, Response &res)>;

using socket_t = int;

constexpr std::size_t MAX_CONNECTIONS = 1000000;

class Server {
  private:
    socket_t _server;
    router_t _router;
    bool _is_running{false};
    std::string _port;

  public:
    Server(const std::string &port, router_t router);
    ~Server();

    void serve();

    inline void stop() { _is_running = false; }
};

} // namespace simple_http

#endif