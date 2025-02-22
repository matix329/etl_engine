#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <string>
#include <vector>
#include <map>

class JsonParser {

public:
    static std::vector<std::map<std::string, std::string>> parseJson(const std::string& jsonData);
};

#endif