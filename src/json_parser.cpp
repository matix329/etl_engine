#include "json_parser.h"
#include <nlohmann/json.hpp>
#include <iostream>

std::vector<std::map<std::string, std::string>> JsonParser::parseJson(const std::string& jsonData) {
    std::vector<std::map<std::string, std::string>> parsedData;

    try {
        nlohmann::json json_response = nlohmann::json::parse(jsonData);

        for (const auto& item : json_response) {
            std::string exchange = item.value("exchange", "");

            if (exchange == "London Stock Exchange" || exchange == "NASDAQ") {
                std::map<std::string, std::string> stock_data;

                stock_data["symbol"] = item.value("symbol", "N/A");
                stock_data["name"] = item.value("name", "N/A");
                stock_data["price"] = std::to_string(item.value("price", 0.0));
                stock_data["exchange"] = exchange;
                stock_data["exchangeShortName"] = item.value("exchangeShortName", "N/A");
                stock_data["type"] = item.value("type", "N/A");

                parsedData.push_back(stock_data);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    return parsedData;
}