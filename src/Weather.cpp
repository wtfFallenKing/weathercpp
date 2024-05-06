#include <iostream>
#include "Weather.h"
#include "cpr/cpr.h"

cpr::Response Weather::Get(const std::string& city, const cpr::Url& url) {
    return cpr::Get(
        url
        , cpr::Parameters{
              {"q", city}
            , {"apikey", api_key_}
            , {"metric", "true"}
            , {"language", "en-us"}
        }
    );
}

json Weather::GetResponseForCity(const std::string& city, const cpr::Url& url) {
    auto response = Get(city, url);
    if (response.status_code == 503) {
        throw std::invalid_argument("Too many requests today...");
    } else if (response.status_code != 200 && response.status_code != 503) {
        throw std::invalid_argument("City is bad");
    }
    json result = json::parse(response.text);
    return result;
}

float Weather::GetTemperature(const std::string& city) {
    std::string locationKey = GetLocationKey(city);
    json response = GetResponseForCity(city, baseUrl + locationKey);
    return response[0]["Temperature"]["Metric"]["Value"];
}

float Weather::GetTomorrowTemperature(const std::string& city) {
    std::string locationKey = GetLocationKey(city);
    json response = GetResponseForCity(city, forecastUrl + locationKey);
  return response["DailyForecasts"][1]["Temperature"]["Maximum"]["Value"];
}

std::string Weather::GetLocationKey(const std::string& city) {
    auto cache_iterator = locations_cache_.find(city);
    if (cache_iterator != locations_cache_.end()) {
        return cache_iterator->second;
    }
    json response = GetResponseForCity(city, locationUrl);
    if (response.size() < 1) {
        throw std::runtime_error("City " + city + " not found!");
    }
    return response[0]["Key"];
}

float Weather::GetDifference(const std::string& city1, const std::string& city2) {
    return GetTemperature(city1) - GetTemperature(city2);
}

void Weather::SetApiKey(const std::string& api_key) {
    api_key_ = api_key;
}

std::string Weather::GetDifferenceString(const std::string& city1, const std::string& city2) {
    float diff = GetDifference(city1, city2);
    std::stringstream output;
    output << "Weather in " << city1 << " ";
    if (diff < 0) {
        output << "is colder than in " << city2 << " by " << int(-diff) << " degrees";
    } else {
        output << "is warmer than in " << city2 << " by " << int(diff) << " degrees";
    }
    return output.str();
}

std::string Weather::GetTomorrowDiff(const std::string& city) {
    float diff = GetTomorrowTemperature(city) - GetTemperature(city);
    std::stringstream output;
    output << "The weather in " << city << " tomorrow will be ";
    std::string response;
    if (diff > 3) {
        response = "much warmer";
    } else if (diff > 0.5) {
        response = "warmer";
    } else if (diff < -3) {
        response = "much colder";
    } else if (diff < -0.5) {
        response = "colder";
    } else {
        response = "the same";
    }
    output << response << " than today";
    return output.str();
}

std::string Weather::GetWeather(const std::string& city) {
    std::string location_key = GetLocationKey(city);
    json response = GetResponseForCity(city, baseUrl + location_key);
    return response[0]["WeatherText"];
}