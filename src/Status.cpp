#include "Status.hpp"

#include <map>
#include <iostream>
#include <sstream>

namespace kshttp {

/**
 * @brief Status code and their respective text. I've got then from
 * https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
 *
 */
std::map<unsigned short, std::string> status_codes{
    // Information responses
    {100, "Continue"},
    {101, "Switching Protocols"},
    {102, "Processing"},
    {103, "Early Hints"},

    // Sucessfull responses
    {200, "OK"},
    {201, "Created"},
    {202, "Accepted"},
    {203, "Non-Authoritative Information"},
    {204, "No Content"},
    {205, "Reset Content"},
    {206, "Partial Content"},
    {207, "Multi-Status"},
    {208, "Already Reported"},
    {226, "IM used"},

    // Redirection messages
    {300, "Multiple Choice"},
    {301, "Moved permanently"},
    {302, "Found"},
    {303, "See other"},
    {304, "Not modified"},
    {307, "Temporary Redirect"},
    {308, "Permanent Redirect"},
    {400, "Bad Request"},
    {401, "Unauthorized"},
    {402, "Payment Required"},
    {403, "Forbidden"},
    {404, "Not Found"},
    {405, "Method Not Allowed"},
    {406, "Not Acceptable"},
    {407, "Proxy Authentication Required"},
    {408, "Request Timeout"},
    {409, "Conflict"},
    {410, "Gone"},
    {411, "Length Required"},
    {412, "Precondition Failed"},
    {413, "Payload Too Large"},
    {414, "URI Too Long"},
    {415, "Unsupported Media Type"},
    {416, "Range Not Satisfiable"},
    {417, "Expectation Failed"},
    {418, "I'm a teapot"},
    {421, "Misdirected Request"},
    {422, "Unprocessable Entity"},
    {423, "Locked"},
    {424, "Failed Dependency"},
    {425, "Too Early"},
    {426, "Upgrade Required"},
    {428, "Precondition Required"},
    {429, "Too Many Requests"},
    {431, "Request Header Fields Too Large"},
    {451, "Unavailable For Legal Reasons"},

    // Server errors
    {500, "Internal Server Error"},
    {501, "Not Implemented"},
    {502, "Bad Gateway"},
    {503, "Service Unavailable"},
    {504, "Gateway Timeout"},
    {505, "HTTP Version Not Supported"},
    {506, "Variant Also Negotiates"},
    {507, "Insufficient Storage"},
    {508, "Loop Detected"},
    {510, "Not Extended"},
    {511, "Network Authentication Required"},
};

bool is_status_valid(unsigned short status) {
    return status_codes.find(status) != status_codes.end();
}

// Using the subscript operator will return a empty string if the status is
// invalid, which is the desired output
std::string get_status_text(unsigned short status) {
    return status_codes[status];
}

std::string get_error_page(unsigned short status) {
    std::stringstream s;
    s << "<h1>" << status << " " << get_status_text(status) << "</h1>";
    return s.str();
}

} // namespace kshttp