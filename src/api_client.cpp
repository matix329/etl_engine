#include "api_client.h"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <fstream>

std::string getApiKey() {
    std::ifstream envFile("src/.env");
    std::string apiKey;

    if (envFile.is_open()) {
        std::getline(envFile, apiKey);
        envFile.close();
    } else {
        std::cerr << "ERROR: Could not open .env file!" << std::endl;
        return "";
    }

    size_t pos = apiKey.find("=");
    if (pos == std::string::npos) {
        std::cerr << "ERROR: Invalid .env format!" << std::endl;
        return "";
    }

    return apiKey.substr(pos + 1);
}

size_t write_callback(void* contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

api_client::api_client(const std::string &base_url) : base_url(base_url) {}

std::string api_client::fetchData(const std::string &end_point) {
    std::string apiKey = getApiKey();
    std::string url = base_url + end_point + "?apikey=" + apiKey;
    std::string response_data;

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl" << std::endl;
        return "";
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);
    return response_data;
}

