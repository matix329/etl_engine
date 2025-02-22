#include "api_client.h"
#include "json_parser.h"
#include "json_valid.h"
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

            auto jsonData = nlohmann::json::parse(response);
            JsonValidator validator("schemas/schema.json");

            validator.saveValidatedData(jsonData);
            std::cout << "All valid data has been successfully validated and saved!" << std::endl;

        } else {
            std::cerr << "No response or empty response from API!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}