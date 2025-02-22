#include "json_valid.h"
#include <nlohmann/json.hpp>
#include <valijson/schema_parser.hpp>
#include <valijson/validator.hpp>
#include <valijson/adapters/nlohmann_json_adapter.hpp>
#include <stdexcept>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

JsonValidator::JsonValidator(const std::string& schemaFilePath) : schema() {
    nlohmann::json jsonSchema;
    std::ifstream schemaFile(schemaFilePath);
    if (!schemaFile.is_open()) {
        throw std::runtime_error("Failed to open schema file: " + schemaFilePath);
    }

    schemaFile >> jsonSchema;
    schemaFile.close();

    valijson::SchemaParser schemaParser;
    valijson::adapters::NlohmannJsonAdapter schemaAdapter(jsonSchema);
    schemaParser.populateSchema(schemaAdapter, this->schema);
}

void JsonValidator::validateSchema(const nlohmann::json& data) const {
    if (!data.is_array()) {
        throw std::runtime_error("Validation error: Expected JSON data to be an array.");
    }
    for (const auto& item : data) {
        if (!item.is_object()) {
            throw std::runtime_error("Validation error: JSON array contains non-object item.");
        }
    }
}

void JsonValidator::validate(const nlohmann::json& data) const {
    valijson::Validator validator;
    valijson::adapters::NlohmannJsonAdapter dataAdapter(data);

    if (!validator.validate(this->schema, dataAdapter, nullptr)) {
throw std::runtime_error("JSON validation failed: Data does not conform to schema");
    }
}

void JsonValidator::ensureRequiredFields(const nlohmann::json& data) const {
    std::vector<std::string> requiredFields = {"symbol", "price", "name", "exchange"};
    for (const auto& requiredField : requiredFields) {
        if (!data.contains(requiredField) || data.at(requiredField).is_null()) {
            throw std::runtime_error("Validation error: Missing or null required field \"" + requiredField + "\"");
        }
    }
}

void JsonValidator::saveValidatedData(const nlohmann::json& data) const {
    validateSchema(data);
    createDirectoryIfNotExists("data");
createDirectoryIfNotExists("data/London Stock Exchange");

createDirectoryIfNotExists("data/NASDAQ");

for (const auto& item : data) {
    try {
        ensureRequiredFields(item);
        validate(item);

std::string exchange = item.at("exchange");
std::string exchangeShortName = item.value("exchangeShortName", "Unknown");
std::string type = item.value("type", "Unknown");
            std::string outputPath;
if (exchange == "London Stock Exchange") {
    outputPath = "data/London Stock Exchange";
} else if (exchange == "NASDAQ") {
    outputPath = "data/NASDAQ";
} else {
    std::cerr << "Warning: Unknown exchange \"" << exchange << "\". Creating dynamic directory." << std::endl;
    outputPath = "data/" + sanitizeName(exchange);
}

            std::string stockSymbol = item.at("symbol");
double stockPrice = item.at("price").get<double>();
std::string stockName = item.at("name");

            std::ofstream outFile(outputPath + "/" + stockSymbol + ".json");
            if (!outFile.is_open()) {
                std::cerr << "Failed to write file: " << outputPath + "/" + stockSymbol + ".json" << std::endl;
                continue;
            }
            outFile << item.dump(4);
            outFile.close();
            std::cout << "Saved: " << outputPath + "/" + stockSymbol + ".json" << std::endl;


        } catch (const std::exception& e) {
std::cerr << "Error validating item: " << e.what() << std::endl;
        }
    }
}


std::string JsonValidator::sanitizeName(const std::string& name) const {
    std::string sanitized = name;
    std::replace_if(sanitized.begin(), sanitized.end(), [](char c) {
        return !(std::isalnum(c) || c == ' ' || c == '_');
    }, '_');
    return sanitized;
}

void JsonValidator::createDirectoryIfNotExists(const std::string& path) const {
    if (!fs::exists(path)) {
        try {
            fs::create_directories(path);
        } catch (const fs::filesystem_error& e) {
std::cerr << "Failed to create directory: " << path << ". Error: " << e.what() << std::endl;
            throw;
        }
    }
}