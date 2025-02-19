#include "json_parser.h"
#include <iostream>

std::vector<std::map<std::string, std::string>> parseJson(const std::string &json_data) {
    std::vector<std::map<std::string, std::string>> parsedData;

    try {
        nlohmann::json json_response = nlohmann::json::parse(json_data);

        for (const auto& item : json_response) {
            std::map<std::string, std::string> stock_data;

            stock_data["symbol"] = item.value("symbol", "N/A");
            stock_data["name"] = item.value("name", "N/A");
            stock_data["price"] = std::to_string(item.value("price", 0.0));
            stock_data["marketCap"] = std::to_string(item.value("marketCap", 0));
            stock_data["volume"] = std::to_string(item.value("volume", 0));
            stock_data["pe"] = std::to_string(item.value("pe", 0.0));
            stock_data["eps"] = std::to_string(item.value("eps", 0.0));

            parsedData.push_back(stock_data);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return parsedData;
}