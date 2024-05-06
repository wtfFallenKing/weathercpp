#include <iostream>
#include "Weather.h"

int main() {
    Weather weather;
    weather.SetApiKey("YOUR API");
    std::string city;
    std::cout << "Введите город: ";
    std::cin >> city;
    std::cout << "Температура в " << city << ": " << weather.GetTemperature(city) << " °C." << '\n';
    std::cout << "Погода в " << city << ": " << weather.GetWeather(city) << " °C." << '\n';
    return 0;
}