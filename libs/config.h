#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <fstream>
#include <string>
#include <vector>

class ConfigParameters {
 public:
  explicit ConfigParameters(const std::string& config_file_path);
  int32_t number_of_days;
  std::vector<std::string> cities;
  uint64_t update_frequency;
};
