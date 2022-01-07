#ifndef KASOUZA_KSHTTP_INCLUDE_STATUS_HPP
#define KASOUZA_KSHTTP_INCLUDE_STATUS_HPP

#include <string>

namespace kshttp {

/**
 * @brief Check if a status code is valid, based on those present in
 * https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
 *
 * @param status Status code (i.e. 200(OK), 404(Not Found), etc)
 * @return true
 * @return false
 */
bool is_status_valid(unsigned short status);

/**
 * @brief Get the status text.
 *
 * @param status Status code (i.e. 200(OK), 404(Not Found), etc)
 * @return std::string A string containing the status text or empty if the given
 * status code is invalid.
 */
std::string get_status_text(unsigned short status);

/**
 * @brief Get a page for error (500 internal server error, 404 page not found,
 * etc)
 *
 * @param status Status code (i.e. 200(OK), 404(Not Found), etc)
 * @return std::string
 */
std::string get_error_page(unsigned short status);

} // namespace kshttp

#endif