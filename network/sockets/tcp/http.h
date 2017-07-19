#ifndef SIMPLE_HTTP_H
#define SIMPLE_HTTP_H

#include <vector>
#include <sys/socket.h>
#include <netdb.h>
#include <string>

namespace network {

constexpr int RECV_BUFFER_SIZE = 16;
constexpr int LF_CODE = 10;
constexpr int CR_CODE = 13;

class simple_http
{
public:
    simple_http();

    // Send request to server by m_host_address
    void request(const std::string& address);

    // Get response from server by m_host_address
    std::string response();

    // Add a new request header to m_request_headers
    void add_headers(const std::string& key, const std::string& value);

    // Get header from m_response_headers by name
    std::string get_header(const std::string& key) const;

    /* Getters / Setters */

    // Returns current request message and headers
    std::string get_request_message() const;

    void set_port(int port);
    void set_method(const std::string& method);
    void set_uri(const std::string& uri);

    virtual ~simple_http();

protected:
    /* Variables */
    int m_socket_id;
    struct addrinfo m_host;
    struct addrinfo *m_hosts; // linked list for multiply IP
    std::string m_host_address;

    /* Resquest variables */
    std::string m_request_port;
    std::string m_request_method;
    std::string m_request_uri;
    std::string m_request_http_version;
    std::string m_request_message;
    std::vector< std::pair<std::string, std::string> > m_request_headers;

    /* Response variables */
    std::string m_response_http_version;
    std::string m_response_http_status_code;
    std::string m_response_http_status;
    std::string m_response_body;
    std::vector< std::pair<std::string, std::string> > m_response_headers;

    /* Methods */

    // Create request message with headers
    void create_request_message();
    //  Split string to substring by delimeter
    std::vector<std::string> split(const std::string& value, char delim);
    // Erase leading and trailing whitespaces
    std::string trim(const std::string& value);
};

} // end of network namespace


#endif  /* SIMPLE_HTTP_H */
