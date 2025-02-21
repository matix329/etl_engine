#include "api_client.h"
#include <nlohmann/json.hpp>
#include <valijson/validator.hpp>
#include <valijson/adapters/nlohmann_json_adapter.hpp>
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
            std::cout << "Response from API: " << std::endl;
            std::cout << response << std::endl;

            nlohmann::json jsonResponse = nlohmann::json::parse(response);
            valijson::Validator validator;
            valijson::adapters::NlohmannJsonAdapter jsonAdapter(jsonResponse);

        } else {
            std::cerr << "No response or empty response from API!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}