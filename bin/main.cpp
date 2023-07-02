#include "libs/weather.h"
#include "libs/UI.h"

#include <iostream>

int main(int argc, char** argv) {
  try {
    ConfigParameters Parameters(argv[1]);
    display(Parameters);
  } catch (const std::exception& e){
    std::cerr << e.what() << std::endl;
    exit(1);
  }
  return 0;
}