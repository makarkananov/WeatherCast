include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 32fd1453194c37d5136577ee55629b863a42333f)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG 4.0.0)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(json)

add_library(config config.cpp config.h)
add_library(weather weather.cpp weather.h)
add_library(UI UI.cpp UI.h weather)
target_link_libraries(config
        PUBLIC cpr::cpr
        PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(weather
        PUBLIC cpr::cpr
        PUBLIC nlohmann_json::nlohmann_json
        PUBLIC config)
target_link_libraries(UI
        PUBLIC cpr::cpr
        PUBLIC nlohmann_json::nlohmann_json
        PUBLIC ftxui::screen
        PUBLIC ftxui::dom
        PUBLIC ftxui::component)