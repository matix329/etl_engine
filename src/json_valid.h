#ifndef JSON_VALID_H
#define JSON_VALID_H

#include <nlohmann/json.hpp>
#include <valijson/schema.hpp>

class JsonValidator {
public:
    JsonValidator(const std::string& schemaFilePath);
    void validate(const nlohmann::json& data) const;
    void saveValidatedData(const nlohmann::json& data) const;
    void validateSchema(const nlohmann::json& data) const;
    void ensureRequiredFields(const nlohmann::json& data) const;

private:
    valijson::Schema schema;
    void createDirectoryIfNotExists(const std::string& path) const;
    std::string sanitizeName(const std::string& name) const;
};

#endif