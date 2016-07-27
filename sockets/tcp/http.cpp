#include "http.h"
#include <sstream>
#include <unistd.h>
#include <fcntl.h>

simple_http::simple_http() :
    m_request_port("80"),
    m_request_method("GET"),
    m_request_uri("/"),
    m_request_http_version("HTTP/1.1")
{
    memset(&m_host, 0, sizeof m_host);
    // init basic addrinfo fields before fill
    m_host.ai_family = AF_UNSPEC;
    m_host.ai_socktype = SOCK_STREAM;
}

void simple_http::create_request_message() {
    /**
        Format: "GET / HTTP/1.1\nhost: www.google.com\n\n";
        1) "GET" - method 
        2) "/" - uri
        3) "HTTP/1.1" - http version
        4) "\n" - new line
        5) "host: www.google.com" - host address
        6) ... - other headers
        7) "\n\n" - end of headers
     **/
    m_request_message.clear();
    m_request_message.append(m_request_method);
    m_request_message.append(" ").append(m_request_uri);
    m_request_message.append(" ").append(m_request_http_version).append("\n");

    m_request_headers.push_back(make_pair("host", m_host_address));

    for(auto p: m_request_headers) {
        m_request_message.append(p.first).append(": ").append(p.second);
    } 
    m_request_message.append("\n\n");
}

void simple_http::request(std::string address) {
    m_host_address = address;
    cout << "GETADDRINFO start" << endl;
    int gaddi_status = getaddrinfo(address.c_str(), m_request_port.c_str(), &m_host, &m_hosts);
    cout << "GETADDRINFO: " << gaddi_status << endl;
    
    if (gaddi_status != 0) {
        std::cout << "Status: " << gaddi_status << std::endl;
        std::cout << "Error: " << gai_strerror(gaddi_status) << std::endl;
    } else {
        // create a socket
        m_socket_id = socket(m_hosts->ai_family, m_hosts->ai_socktype, m_hosts->ai_protocol);
        if (m_socket_id == -1) {
            std::cout << "Could not create a socket" << std::endl;
        } else {
            // connect socket to host
            int connect_status = connect(m_socket_id, m_hosts->ai_addr, m_hosts->ai_addrlen);
            if (connect_status == -1) {
                std::cout << "Connection call failed" << std::cout;
            } else {
                create_request_message();
                int bytes = send(m_socket_id, m_request_message.c_str(), strlen(m_request_message.c_str()), 0);
                cout << "Bytes: " << bytes << endl;
            }
        }
    }
}

std::string simple_http::response() {
    std::string received_data;
    while(true) {
        char incoming_bytes_buffer[RECV_BUFFER_SIZE];
        // Get data from server
        ssize_t bytes_received = recv(m_socket_id, incoming_bytes_buffer, RECV_BUFFER_SIZE, 0);
        if (bytes_received == 0) {
            break;
        }
        for (ssize_t i = 0; i < bytes_received; ++i) {
            received_data += incoming_bytes_buffer[i];
        }
    }
    // Split headers and response body
    /**
        Format:
        [STATUSSTRING]\r\n
        [HEADERNAME1: HEADERVALUE1]\r\n
        [HEADERNAME2: HEADERVALUE2]\r\n
        [...]
        [LASTHEADERNAME: LASTHEADERVALUE]\r\n
        []\r\n
        [BODY]
    **/
    std::string header_buffer;
    int countOfLForCR = 0; 
    bool isHeadersParsed = false;
    std::vector<std::string> headers;

    for (size_t i = 0; i < received_data.size(); ++i) {
        char current_symbol = received_data.at(i);
        if ((int)current_symbol == LF_CODE || (int)current_symbol == CR_CODE) {
            countOfLForCR++;
            continue;
        }
        // end of header
        if (countOfLForCR == 2 && !isHeadersParsed) {
            if (!header_buffer.empty()) {
                headers.push_back(header_buffer);
                header_buffer.clear();
                countOfLForCR = 0;
            }           
        }
        // end of headers 
        if (countOfLForCR == 4 && !isHeadersParsed) {
            isHeadersParsed = true;
            countOfLForCR = 0;
            m_response_body.clear();
            m_response_body.append(received_data, i, received_data.size());
            break;
        }
        header_buffer += current_symbol;
    }
    // First item of headers array - string with response status
    // Format of response status: 
    // HTTP_VERSION + " " + HTTP_STATUS_CODE + " " + HTTP_STATUS 
    std::string status = headers.at(0);
    headers.erase(headers.begin());
    auto results = split(status, ' ');
    m_response_http_version = results.at(0);
    m_response_http_status_code = results.at(1);
    m_response_http_status = results.at(2);

    // - TODO: Parse headers
    for(auto& header : headers) {
        auto parts = split(header, ':');
        auto pair = make_pair(parts.at(0), trim(parts.at(1)));
        m_response_headers.push_back(pair);
    }

    return m_response_body;
}

std::vector<std::string> simple_http::split(std::string value, char delim) {
    std::stringstream ss(value);
    std::vector<std::string> elements;
    std::string item;
    while (std::getline(ss, item, delim)) {
        elements.push_back(item);
    }
    return elements;
}

void simple_http::add_headers(std::string key, std::string value) {
    for(auto &p : m_request_headers) {
        if (p.first == key) {
            p.second = value;
            return;
        }
    }
    m_request_headers.push_back(std::make_pair(key, value));
}

std::string simple_http::get_header(std::string key) const {
    for(auto &p : m_response_headers) {
        if (p.first == key) {
            return p.second;
        }
    }
    return "";
}

std::string simple_http::trim(std::string value) {
    const string whitespace = " \t\f\v\n\r";
    int start = value.find_first_not_of(whitespace);
    int end = value.find_last_not_of(whitespace);
    value.erase(0, start);
    value.erase((end - start) + 1);
    return value;
}

/* Getters / Setters */

std::string simple_http::get_request_message() const {
    return m_request_message;
}

void simple_http::set_port(int port) {
    m_request_port = std::to_string(port);
}

void simple_http::set_method(std::string method) {
    m_request_method = method;
}

void simple_http::set_uri(std::string uri) {
    m_request_uri = uri;
}


simple_http::~simple_http() {
    if (m_hosts != nullptr)
        freeaddrinfo(m_hosts);
    // close(m_socket_id);
}