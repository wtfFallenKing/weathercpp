#include "json.hpp"
#include "cpr/cpr.h"

using json = nlohmann::json;

class Weather {
 private:
   const cpr::Url baseUrl = cpr::Url{"http://dataservice.accuweather.com/currentconditions/v1/"};
   const cpr::Url forecastUrl = cpr::Url{"http://dataservice.accuweather.com/forecasts/v1/daily/5day/"};
   const cpr::Url locationUrl = cpr::Url{"http://dataservice.accuweather.com/locations/v1/cities/search"};
   std::string api_key_;
   std::unordered_map<std::string, std::string> locations_cache_;

 protected:
   virtual cpr::Response Get(const std::string& key, const cpr::Url& url);

 public:
   json GetResponseForCity(const std::string& city, const cpr::Url& url);
   
   virtual float GetTemperature(const std::string& city);
   virtual float GetTomorrowTemperature(const std::string& city);

   virtual std::string GetLocationKey(const std::string& city);

   float GetDifference(const std::string& city1, const std::string& city2);

   void SetApiKey(const std::string& api_key);

   std::string GetDifferenceString(const std::string& city1, const std::string& city2);
   std::string GetTomorrowDiff(const std::string& city);

   virtual std::string GetWeather(const std::string& city);

};