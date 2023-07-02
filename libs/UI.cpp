#include "UI.h"

#include <ftxui/component/component.hpp>
#include <ftxui/dom/flexbox_config.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "weather.h"

#include <sstream>
#include <utility>

using namespace ftxui;

std::string dtos(const double& t) {
  std::ostringstream os;
  os << t;
  return os.str();
}

Decorator getWeatherColor(const uint8_t WMO_code) {
  switch (WMO_code) {
    case 0: return color(Color::Cyan1);
    case 1:
    case 2:
    case 3: return color(Color::DeepSkyBlue1);
    case 45:
    case 48: return color(Color::LightCyan1Bis);
    case 51:
    case 53:
    case 55: return color(Color::SteelBlue3);
    case 56:
    case 57: return color(Color::Aquamarine1Bis);
    case 61:
    case 63:
    case 65: return color(Color::SkyBlue1);
    case 66:
    case 67: return color(Color::SteelBlue1);
    case 71:
    case 73:
    case 75: return color(Color::Blue);
    case 77: return color(Color::Cyan2);
    case 80:
    case 81:
    case 82: return color(Color::LightSlateBlue);
    case 85:
    case 86: return color(Color::SlateBlue1);
    case 95:
    case 96: return color(Color::Magenta2);
    case 99: return color(Color::DarkMagentaBis);
    default: return color(Color::White);
  }
}
Element getWeatherPicture(const uint8_t WMO_code) {
  switch (WMO_code) {
    case 0: {
      return center(vbox({
                             text("                       "),
                             text(" _ - _   _ - _ - _   _ "),
                             text("  _   _   _  _   _  _  "),
                             text(" _- _ - _ - _- _ - _ - "),
                             text("  _   _   _  _   _  _  ")
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 1:
    case 2:
    case 3: {
      return center(vbox({
                             text("                       "),
                             text(" _ - _- _ - _- _ - _ - "),
                             text("  _ -_-- _ _ -_-- _-   "),
                             text(" _ - _- _ - _- _ - _ - "),
                             text("  _ -_-- _ _ -_-- _-   ")
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 45:
    case 48: {
      return center(vbox({
                             text("                       "),
                             text("              .-.      "),
                             text("      .-.    (   ).    "),
                             text("     (   ). (___(__)   "),
                             text("    (___(__)           ")
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 51:
    case 53:
    case 55: {
      return center(vbox({
                             text("                       ") | color(Color::DodgerBlue1),
                             text("  ‘ ‘ ‘   ‘ ‘ ‘   ‘ ‘  ") | color(Color::DodgerBlue1),
                             text("   ‘  ‘ ‘ ‘   ‘ ‘   ‘  ") | color(Color::DodgerBlue1),
                             text("  ‘   ‘   ‘ ‘   ‘ ‘    ") | color(Color::DodgerBlue1),
                             text("   ‘ ‘   ‘   ‘ ‘   ‘ ‘ ") | color(Color::DodgerBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 56:
    case 57: {
      return center(vbox({
                             text("  ‘ * ‘ ‘ * ‘ * ‘ ‘ *  ") | color(Color::LightSkyBlue1),
                             text("  ‘ ‘ * ‘ ‘ ‘ ‘ * ‘ ‘  ") | color(Color::LightSkyBlue1),
                             text("  ‘ ‘ ‘ * ‘ ‘ ‘ ‘ * ‘  ") | color(Color::LightSkyBlue1),
                             text("  ‘ * ‘ ‘ * ‘ * ‘ ‘ *  ") | color(Color::LightSkyBlue1),
                             text("   ‘ ‘ * ‘ ‘‘ ‘ * ‘ ‘  ") | color(Color::LightSkyBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 61:
    case 63:
    case 65: {
      return center(vbox({
                             text("     .-.      .-.      "),
                             text("    (   ).   (   ).    "),
                             text("   (___(__) (___(__)   "),
                             text("   ‘   ‘   ‘ ‘   ‘     ") | color(Color::DodgerBlue1),
                             text("    ‘   ‘   ‘   ‘ ‘    ") | color(Color::DodgerBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 66:
    case 67: {
      return center(vbox({
                             text("     .-.      .-.      "),
                             text("    (   ).   (   ).    "),
                             text("   (___(__) (___(__)   "),
                             text("   ‘   *   ‘ ‘   *     ") | color(Color::LightSkyBlue1),
                             text("    *   ‘   *   ‘ *    ") | color(Color::LightSkyBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 71:
    case 73:
    case 75: {
      return center(vbox({
                             text("     .-.      .-.      "),
                             text("    (   ).   (   ).    "),
                             text("   (___(__) (___(__)   "),
                             text("   *   *   * *   *     ") | color(Color::LightSkyBlue1),
                             text("    *   *   *   * *    ") | color(Color::LightSkyBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 77: {
      return center(vbox({
                             text("           .-.         "),
                             text("       .-.(  ).-.      "),
                             text("      (   )  (   ).    "),
                             text("    (___(__)(___(__)   "),
                             text("    °° °° ° °°° ° °    ") | color(Color::LightSkyBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 80:
    case 81:
    case 82: {
      return center(vbox({
                             text("           .-.         "),
                             text("       .-.(  ).-.      "),
                             text("      (   )  (   ).    "),
                             text("    (___(__)(___(__)   "),
                             text("    ‘‘ ‘ ‘‘ ‘‘‘ ‘ ‘    ") | color(Color::DodgerBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 85:
    case 86: {
      return center(vbox({
                             text("           .-.         "),
                             text("       .-.(  ).-.      "),
                             text("      (   )  (   ).    "),
                             text("    (___(__)(___(__)   "),
                             text("    * ** * *** ** *    ") | color(Color::LightSkyBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 95:
    case 96: {
      return center(vbox({
                             text("           .-.         "),
                             text("       .-.( ϟ).-.      "),
                             text("      ( ϟ )  (   ).    "),
                             text("    (___(__)(_ϟ_(__)   "),
                             text("    ‘‘ ϟ‘‘‘ ‘‘ ‘ ‘ϟ    ") | color(Color::DodgerBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    case 99: {
      return center(vbox({
                             text("           .-.         "),
                             text("       .-.( ϟ).-.      "),
                             text("      ( ϟ )  (   ).    "),
                             text("    (___(__)(_ϟ_(__)   "),
                             text("    °° ϟ°°° °°° °°ϟ    ") | color(Color::LightSkyBlue1)
                         })) | size(WIDTH, EQUAL, 30);
    }
    default: {
      return center(vbox({
                             text("               "),
                             text("  _  _   _  _  "),
                             text("   _   _   _   "),
                             text("  _  _  _  _   "),
                             text("               ")
                         })) | size(WIDTH, EQUAL, 30);
    }
  }
}
Decorator getTempColor(const int32_t temp) {
  if (temp < -30) return color(Color::DarkBlue);
  else if (temp < -20) return color(Color::Blue3Bis);
  else if (temp < -10) return color(Color::DodgerBlue2);
  else if (temp < 0) return color(Color::DeepSkyBlue1);
  else if (temp < 10) return color(Color::Wheat1);
  else if (temp < 20) return color(Color::Yellow1);
  else if (temp < 30) return color(Color::DarkOrange);
  else return color(Color::Red1);
}
Decorator getWindColor(const double wind_speed) {
  if (wind_speed < 10) return color(Color::Green1);
  else if (wind_speed < 20) return color(Color::Yellow1);
  else if (wind_speed < 30) return color(Color::DarkOrange);
  else return color(Color::Red1);
}

void display(ConfigParameters& Parameters) {
  auto screen = ScreenInteractive::Fullscreen();
  Weather weather;
  size_t current_city = 0;
  Component component;
  bool weather_status;
  try{
    weather = Weather(Parameters);
    weather_status = true;
  } catch(const std::exception& e){
    weather = Weather();
    weather_status = false;
  }
  component = Renderer([&] {
    try {
      if (!weather_status) {
        throw std::runtime_error("No weather data");
      }
      FlexboxConfig config;
      config.wrap = FlexboxConfig::Wrap::Wrap;
      config.justify_content = FlexboxConfig::JustifyContent::SpaceAround;
      config.align_content = FlexboxConfig::AlignContent::Center;
      const auto& city_weather = weather.weather_in_cities[current_city];
      Elements days;
      Element days_container;
      for (const auto& day_weather : city_weather.weather_on_days) {
        FlexboxConfig day_config;
        day_config.direction = FlexboxConfig::Direction::Column;
        day_config.justify_content = FlexboxConfig::JustifyContent::Center;
        auto day = window(text(day_weather.date) | center,
                          flexbox({
                                      text(day_weather.weather_description) | getWeatherColor(day_weather.WMO_code),
                                      hbox({text("Temperature: "), text(std::to_string(day_weather.min_temperature))
                                          | getTempColor(day_weather.min_temperature), text("("),
                                            text(std::to_string(day_weather.max_temperature))
                                                | getTempColor(day_weather.max_temperature), text(") °C")}),
                                      hbox({text("Wind speed: "), text(dtos(day_weather.max_wind_speed))
                                          | getWindColor(day_weather.max_wind_speed), text(" km/h")}),
                                      text("Precipitation sum: " + dtos(day_weather.precipitation_sum) + " mm"),
                                      getWeatherPicture(day_weather.WMO_code)
                                  }, day_config)) | size(WIDTH, EQUAL, 30) | size(HEIGHT, EQUAL, 11);
        days.push_back(day);
      }
      Elements cities_container;
      for (int i = 0; i < weather.weather_in_cities.size(); ++i) {
        Element city_name = text(weather.weather_in_cities[i].name) | center | size(WIDTH, GREATER_THAN, 10);
        if (i == current_city) city_name |= inverted;
        cities_container.push_back(city_name);
      }
      FlexboxConfig cities_container_config;
      cities_container_config.wrap = FlexboxConfig::Wrap::Wrap;
      cities_container_config.justify_content = FlexboxConfig::JustifyContent::Center;
      cities_container_config.align_content = FlexboxConfig::AlignContent::Center;
      days_container = vbox({text(city_weather.name) | center | inverted, separatorEmpty(),
                             flexbox(std::move(days), config), separator(),
                             flexbox(std::move(cities_container) | size(WIDTH, EQUAL, 10), cities_container_config)});
      return border(days_container);
    } catch (const std::exception& e) {
      return vbox({
                      text(e.what()),
                      text("press 'Esc' to exit or 'r' to try again"),
                  });
    }
  });

  auto scroller = Scroller(component);
  scroller |= CatchEvent([&](const Event& event) -> bool {
    if (event == Event::Escape) screen.Exit();
    else if (event == Event::Character("+")) {
      if (Parameters.number_of_days + 1 <= 7) {
        Parameters.number_of_days++;
        try{
          weather = Weather(Parameters);
          weather_status = true;
        } catch(const std::exception& e){
          weather = Weather();
          weather_status = false;
        }
      }
      return true;
    } else if (event == Event::Character("-")) {
      if (Parameters.number_of_days - 1 >= 0) {
        Parameters.number_of_days--;
        try{
          weather = Weather(Parameters);
          weather_status = true;
        } catch(const std::exception& e){
          weather = Weather();
          weather_status = false;
        }
      }
      return true;
    } else if (event == Event::Character("n")) {
      if (current_city < Parameters.cities.size() - 1) {
        current_city++;
      }
      return true;
    } else if (event == Event::Character("p")) {
      if (current_city > 0) {
        current_city--;
      }
      return true;
    }
    else if (event == Event::Character("r")) {
      try{
        weather = Weather(Parameters);
        weather_status = true;
      } catch(const std::exception& e){
        weather = Weather();
        weather_status = false;
      }
      return true;
    }
    return false;
  });
  Loop loop(&screen, scroller);
  size_t milliseconds_past = 0;
  while (!loop.HasQuitted()) {
    loop.RunOnce();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    milliseconds_past += 10;
    if (milliseconds_past / 1000 >= Parameters.update_frequency) {
      milliseconds_past = 0;
      try{
        weather = Weather(Parameters);
        weather_status = true;
      } catch(const std::exception& e){
        weather = Weather();
        weather_status = false;
      }
    }
  }
}