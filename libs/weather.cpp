#include "weather.h"

 Weather::Weather(const ConfigParameters& Parameters) {
  for (const auto& city_name : Parameters.cities) {
    Coordinates City;
    City = getCityCoordinates(city_name);
    cpr::Response response = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                                      cpr::Parameters{{"latitude", std::to_string(City.latitude)},
                                                      {"longitude", std::to_string(City.longitude)},
                                                      {"timezone", "auto"},
                                                      {"forecast_days", std::to_string(Parameters.number_of_days)},
                                                      {"daily", "temperature_2m_max"},
                                                      {"daily", "temperature_2m_min"},
                                                      {"daily", "windspeed_10m_max"},
                                                      {"daily", "weathercode"},
                                                      {"daily", "precipitation_sum"}
                                      });
    if (response.status_code != 200){
      throw std::runtime_error("Error [" + std::to_string(response.status_code) + "] making request to open meteo");
    }
    auto response_parsed = nlohmann::json::parse(response.text);
    CityWeather current;
    current.name = city_name;
    for (size_t i = 0; i < Parameters.number_of_days; ++i) {
      DayWeather DW{};
      DW.max_wind_speed = response_parsed["daily"]["windspeed_10m_max"][i];
      DW.max_temperature = response_parsed["daily"]["temperature_2m_max"][i];
      DW.min_temperature = response_parsed["daily"]["temperature_2m_min"][i];
      DW.WMO_code = response_parsed["daily"]["weathercode"][i];
      DW.weather_description = getWeatherDescription(DW.WMO_code);
      DW.precipitation_sum = response_parsed["daily"]["precipitation_sum"][i];
      DW.date = response_parsed["daily"]["time"][i];
      current.weather_on_days.push_back(DW);
    }
    weather_in_cities.push_back(current);
  }
}

Weather::Coordinates Weather::getCityCoordinates(const std::string& city_name) {
  std::string token = "2FiMV3VTb+fnEpfqwqNZPQ==LhisrchbN5cKwe6k";
  cpr::Response response = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                                    cpr::Header{{"X-Api-Key", token}},
                                    cpr::Parameters{{"name", city_name}});
  if (response.status_code != 200) {
    throw std::runtime_error("Error making request to ninja");
  }
  auto response_parsed = nlohmann::json::parse(response.text);
  return {response_parsed[0]["longitude"], response_parsed[0]["latitude"]};
}
std::string Weather::getWeatherDescription(uint8_t WMO_code) {
  switch (WMO_code) {
    case 0: return "Clear sky";
    case 1: return "Mainly clear";
    case 2: return "Partly cloudy";
    case 3: return "Overcast";
    case 45: return "Fog";
    case 48: return "Depositing rime fog";
    case 51: return "Light drizzle";
    case 53: return "Moderate drizzle";
    case 55: return "Dense drizzle";
    case 56: return "Light freezing drizzle";
    case 57: return "Dense freezing drizzle";
    case 61: return "Slight rain";
    case 63: return "Moderate rain";
    case 65: return "Heavy rain";
    case 66: return "Light freezing rain";
    case 67: return "Heavy freezing rain";
    case 71: return "Light snow fall";
    case 73: return "Moderate snow fall";
    case 75: return "Heavy snow fall";
    case 77: return "Snow grains";
    case 80: return "Slight rain showers";
    case 81: return "Moderate rain showers";
    case 82: return "Violent rain showers";
    case 85: return "Slight snow showers";
    case 86: return "Heavy snow showers";
    case 95: return "Thunderstorm";
    case 96: return "Thunderstorm with slight hail";
    case 99: return "Thunderstorm with heavy hail";
    default: return "Unknown conditions";
  }
}
