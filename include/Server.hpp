#ifndef KASOUZA_SIMPLE_HTTP_SERVER_HPP
#define KASOUZA_SIMPLE_HTTP_SERVER_HPP

#include <functional>
#include <string>

namespace kshttp {

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
  /**
   * @brief Construct a new Server object.
   * 
   * @param port A port to listen to
   * @param router A user defined function that will handle the routing
   */
    Server(const std::string &port, router_t router);
    ~Server();

    /**
     * @brief Start the server.
     * 
     */
    void serve();

    /**
     * @brief Stops the server.
     * 
     */
    inline void stop() { _is_running = false; }
};

} // namespace simple_http

#endif