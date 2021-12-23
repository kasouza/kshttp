#ifndef KASOUZA_SIMPLE_HTTP_RESPONSE_HPP
#define KASOUZA_SIMPLE_HTTP_RESPONSE_HPP

#include "Server.hpp"

#include <map>
#include <string>

namespace simple_http {
class Response {
  private:
    std::string _http_version;
    socket_t _client;
    std::string _status_code{"200"};
    std::map<std::string, std::string> _headers;
    std::string _content;

  public:
    Response(socket_t client, std::string http_version);

    Response &status_code(std::string code);
    Response &header(std::string header, std::string value);
    Response &text(std::string content);
    void send();
};
} // namespace simple_http

#endif