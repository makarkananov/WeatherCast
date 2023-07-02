#include "config.h"

ConfigParameters::ConfigParameters(const std::string& config_file_path) {
  std::ifstream f(config_file_path);
  if (!f.is_open()) {
    throw std::invalid_argument("no json config file found");
  }
  auto config_parsed = nlohmann::json::parse(f);
  number_of_days = config_parsed["days"];
  cities = config_parsed["cities"];
  update_frequency = config_parsed["update-frequency"];
  if (cities.empty()) throw std::logic_error("no cities were provided");
  if (update_frequency == 0) throw std::logic_error("update frequency cannot be equal to 0");
  if (number_of_days <= 0 || number_of_days > 7)  throw std::logic_error("number of days for forecast must be between 1 and 7");
}