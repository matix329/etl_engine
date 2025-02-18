#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <string>

class api_client {
public:
    api_client(const std::string& base_url);
    std::string fetchData(const std::string& end_point);

private:
    std::string base_url;
};



#endif