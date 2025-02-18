#include "api_client.h"
#include <iostream>

int main() {
    api_client api("https://financialmodelingprep.com/api/v3/");
    std::string data=  api.fetchData("symbol/NASDAQ");

    std::cout << "Received data: " << data << std::endl;
    return 0;
}