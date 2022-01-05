#include "Request.hpp"
#include <iostream>
#include <vector>

// Spit a string into tokens
static std::vector<std::string>
tokenize(const std::string &s, const std::string &del = " ", int limit = -1) {
    std::vector<std::string> tokens;

    int start = 0;
    int end = s.find(del);

    do {
        tokens.push_back(s.substr(start, end - start));

        start = end + del.length();
        end = s.find(del, start);
        --limit;
    } while (end != -1 && limit != 1);

    tokens.push_back(s.substr(start, end - start));

    return tokens;
}

namespace simple_http {
std::optional<Request> Request::parse(const std::string &raw_req) {
    Request req;

    if (raw_req.empty()) {
        std::cerr << "Empty request.\n";
        return {};
    }

    // Split headers from body
    int empty_line = raw_req.find("\r\n\r\n");
    std::string headers_str = raw_req.substr(0, empty_line);
    std::string body = raw_req.substr(empty_line + 4); // After the empty line

    if (headers_str.empty()) {
        std::cerr << "Empty headers.\n";
        return {};
    }

    // Split string into individual headers
    auto header_tokens{tokenize(headers_str, "\r\n")};
    if (header_tokens.empty()) {
        std::cerr << "Invalid headers: " << headers_str << '\n';
        return {};
    }

    // Get the request line and remove it from
    // the headers vector
    std::string request_line{header_tokens[0]};
    header_tokens.erase(header_tokens.begin());

    if (request_line.empty()) {
        std::cerr << "Empty request line.\n";
        return {};
    }

    for (auto &h : header_tokens) {
        auto tokens{tokenize(h, ": ", 2)};
        if (tokens.size() != 2) {
            std::cerr << "Error while parsing header: " << h << '\n';
            return {};
        }

        req._headers.emplace(tokens[0], tokens[1]);
    }

    // Parse the request line
    auto req_line_tokens{tokenize(request_line, " ", 3)};
    if (req_line_tokens.size() != 3) {
        std::cerr << "Invalid request line: " << request_line << '\n';
        return {};
    }

    req._method = req_line_tokens[0];
    req._path = req_line_tokens[1];
    req._http_version = req_line_tokens[2];

    return {req};
}
} // namespace simple_http