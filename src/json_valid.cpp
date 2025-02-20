#include "json_valid.h"
#include <valijson/utils/file_utils.hpp>
#include <stdexcept>
#include <fstream>

JsonValidator::JsonValidator(const std::string& schemaFilePath) {
    nlohmann::json jsonSchema;
    std::ifstream schemaFile(schemaFilePath);
    if (!schemaFile.is_open()) {
        throw std::runtime_error("Failed to open schema file: " + schemaFilePath);
    }

    schemaFile >> jsonSchema;
    schemaFile.close();

    valijson::SchemaParser schemaParser;
    valijson::adapters::NlohmannJsonAdapter schemaAdapter(jsonSchema);
    schemaParser.populateSchema(schemaAdapter, schema);
}

void JsonValidator::validate(const nlohmann::json& data) const {
    valijson::Validator validator;
    valijson::adapters::NlohmannJsonAdapter dataAdapter(data);

    if (!validator.validate(schema, dataAdapter)) {
        throw std::runtime_error("JSON validation failed: Data does not conform to schema");
    }
}