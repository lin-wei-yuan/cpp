#include <iostream>
#include <vector>
#include "simple_http.h"

using namespace std;

int main() {
    simple_http shttp;
    // shttp.set_port(8081);
    shttp.request("google.com");
    std::string response = shttp.response();
    cout << response << endl;
    return 0;
}