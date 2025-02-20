#ifndef JSON_VALID_H
#define JSON_VALID_H

#include <string>
#include <json.hpp>
#include <valijson/schema.hpp>
#include <valijson/validator.hpp>
#include <valijson/schema_parser.hpp>

class JsonValidator {
public:
    JsonValidator(const std::string& schemaFilePath);
    void validate(const nlohmann::json& data) const;

private:
    valijson::Schema schema;
};

#endif