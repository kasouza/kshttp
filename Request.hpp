#ifndef KASOUZA_SIMPLE_HTTP_REQUEST_HPP
#define KASOUZA_SIMPLE_HTTP_REQUEST_HPP

#include <map>
#include <optional>
#include <string>

namespace simple_http {

class Request {
  private:
    std::string _method;
    std::string _path;
    std::string _http_version;

    std::map<std::string, std::string> _headers;
    std::string _content{""};

    Request(){};

  public:
    static std::optional<Request> parse(const std::string &raw_req);

    inline bool has_header(const std::string &header) const {
        return _headers.find(header) != _headers.end();
    }

    inline std::optional<std::string>
    get_header(const std::string &header) const {
        if (!has_header(header))
            return "";

        return _headers.at(header);
    }

    inline const std::string get_method() const { return _method; };
    inline const std::string get_path() const { return _path; };
    inline const std::string get_http_version() const { return _http_version; };
    
    inline const std::map<std::string, std::string> &get_headers() const {
        return _headers;
    };
    inline const std::string &get_content() const { return _content; }
};

} // namespace simple_http

#endif