#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "config.h"

#include <fstream>
#include <string>
#include <utility>
#include <vector>

class Weather {
 public:
  Weather() = default;
  explicit Weather(const ConfigParameters& Parameters);
  struct DayWeather {
    double max_wind_speed;
    int8_t max_temperature;
    int8_t min_temperature;
    std::string weather_description;
    double precipitation_sum;
    uint8_t WMO_code;
    std::string date;
  };
  struct CityWeather{
    std::string name;
    std::vector<DayWeather> weather_on_days;
  };
  std::vector<CityWeather> weather_in_cities;
 private:
  struct Coordinates {
    Coordinates() = default;
    Coordinates(double longitude, double latitude) : longitude(longitude), latitude(latitude) {}
    double longitude;
    double latitude;
  };
  [[nodiscard]] static Coordinates getCityCoordinates(const std::string& city_name);
  [[nodiscard]] static std::string getWeatherDescription(uint8_t WMO_code);
};