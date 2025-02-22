#include "api_client.h"
#include "json_parser.h"
#include <nlohmann/json.hpp>
#include <iostream>

int main() {
    api_client client("https://financialmodelingprep.com/api/v3/");

    try {
        std::string endpoint = "etf/list";
        std::string api_key = "?apikey=" + client.getApiKey();
        std::string fullEndpoint = client.getBaseUrl() + endpoint + api_key;

        std::cout << "Fetching data for endpoint: " << fullEndpoint << std::endl;
        std::string response = client.fetchData(endpoint);

        if (!response.empty()) {
            std::cout << "Processing data..." << std::endl;

            std::vector<std::map<std::string, std::string>> filteredData = JsonParser::parseJson(response);

            if (!filteredData.empty()) {
                std::cout << "Filtered Data:" << std::endl;
                for (const auto& stock : filteredData) {
                    for (const auto& [key, value] : stock) {
                        std::cout << key << ": " << value << std::endl;
                    }
                    std::cout << "---------------------------------" << std::endl;
                }
            } else {
                std::cerr << "No valid data found for the specified exchanges!" << std::endl;
            }

        } else {
            std::cerr << "No response or empty response from API!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}