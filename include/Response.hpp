#ifndef KASOUZA_SIMPLE_HTTP_RESPONSE_HPP
#define KASOUZA_SIMPLE_HTTP_RESPONSE_HPP

#include "Server.hpp"

#include <map>
#include <string>

namespace kshttp {
class Response {
  private:
    std::string _http_version;
    socket_t _client;
    unsigned short _status_code{ 200 };
    std::map<std::string, std::string> _headers;
    std::string _body;

  public:
    /**
     * @brief Construct a new Response:: Response object
     *
     * @param client Socket file descriptor used to send the response
     * @param http_version String identifying the http protocol version
     */
    Response(socket_t client, std::string http_version);

    /**
     * @brief Set the status code of the response
     * 
     * @param code HTTP status code
     * @return Response& A reference to this response
     */
    Response &status(unsigned short status);
    /**
     * @brief Set a header to be sent to the client
     *
     * @param header Header key
     * @param value Header content
     * @return Response& A reference to this response
     */
    Response &header(std::string header, std::string value);

    /**
     * @brief Use the given string as the reponse body
     *
     * @param body The body to be used
     * @return Response& A reference to this response
     */
    Response &text(std::string body);

    /**
     * @brief Send the response to the client, using the data you've setted up
     * using the other methods
     *
     */
    void send();
};
} // namespace simple_http

#endif