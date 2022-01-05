#ifndef KASOUZA_SIMPLE_HTTP_REQUEST_HPP
#define KASOUZA_SIMPLE_HTTP_REQUEST_HPP

#include <map>
#include <optional>
#include <string>

namespace kshttp {

class Request {
  private:
    std::string _method;
    std::string _path;
    std::string _http_version;

    std::map<std::string, std::string> _headers;
    std::string _body{""};

    Request(){};

  public:
  /**
   * @brief Try to parse a raw text into a Request object
   * 
   * @param raw_req String containing a HTTP request
   * @return std::optional<Request> 
   */
    static std::optional<Request> parse(const std::string &raw_req);

    /**
     * @brief Return wether a certaing header was sent by the client
     * 
     * @param header
     * @return true 
     * @return false 
     */
    inline bool has_header(const std::string &header) const {
        return _headers.find(header) != _headers.end();
    }

    /**
     * @brief Try to get a header and return it's value
     * 
     * @param header 
     * @return std::optional<std::string> 
     */
    inline std::optional<std::string>
    get_header(const std::string &header) const {
        if (!has_header(header))
            return "";

        return _headers.at(header);
    }

    /**
     * @brief Get the method (POST, GET, etc)
     * 
     * @return const std::string 
     */
    inline const std::string get_method() const { return _method; };

    /**
     * @brief Get the path
     * 
     * @return const std::string 
     */
    inline const std::string get_path() const { return _path; };

    /**
     * @brief Get the http version used
     * 
     * @return const std::string 
     */
    inline const std::string get_http_version() const { return _http_version; };
    
    inline const std::map<std::string, std::string> &get_headers() const {
        return _headers;
    };

    /**
     * @brief Get the body of the request
     * 
     * @return const std::string& 
     */
    inline const std::string &get_body() const { return _body; }
};

} // namespace simple_http

#endif