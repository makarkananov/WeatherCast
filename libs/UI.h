#include <ftxui/component/component.hpp>
#include <ftxui/dom/flexbox_config.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/loop.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "weather.h"

#include <sstream>
#include <utility>

using namespace ftxui;

// Edited scroll implementation by FTXUI creator https://github.com/ArthurSonzogni/git-tui/blob/master/src/scroller.cpp
class ScrollerBase : public ComponentBase {
 public:
  explicit ScrollerBase(Component child) { Add(std::move(child)); }

 private:
  Element Render() final {
    auto focused = Focused() ? focus : ftxui::select;

    Element background = ComponentBase::Render();
    background->ComputeRequirement();
    size_ = background->requirement().min_y;
    return dbox({
                    std::move(background),
                    vbox({
                             text(L"") | size(HEIGHT, EQUAL, selected_),
                             text(L"") | focused,
                         }),
                }) |
        vscroll_indicator | yframe | yflex | reflect(box_);
  }

  bool OnEvent(Event event) final {
    if (event.is_mouse() && box_.Contain(event.mouse().x, event.mouse().y))
      TakeFocus();

    int selected_old = selected_;
    if (event == Event::ArrowUp || event == Event::Character('k') ||
        (event.is_mouse() && event.mouse().button == Mouse::WheelUp)) {
      selected_ -= 3;
    }
    if ((event == Event::ArrowDown || event == Event::Character('j') ||
        (event.is_mouse() && event.mouse().button == Mouse::WheelDown))) {
      selected_ += 3;
    }
    if (event == Event::PageDown)
      selected_ += box_.y_max - box_.y_min;
    if (event == Event::PageUp)
      selected_ -= box_.y_max - box_.y_min;
    if (event == Event::Home)
      selected_ = 0;
    if (event == Event::End)
      selected_ = size_;

    selected_ = std::max(0, selected_);
    return selected_old != selected_;
  }

  [[nodiscard]] bool Focusable() const final { return true; }

  int selected_ = 0;
  int size_ = 0;
  Box box_;
};
Component Scroller(Component child) {
  return Make<ScrollerBase>(std::move(child));
}

std::string dtos(const double& t);

Decorator getWeatherColor(uint8_t WMO_code);
Element getWeatherPicture(uint8_t WMO_code);
Decorator getTempColor(int32_t temp);
Decorator getWindColor(double wind_speed);

void display(ConfigParameters& Parameters);