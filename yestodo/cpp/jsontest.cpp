#include "jsons.h"
#include <iostream>

int main(int argc, char *argv[]) {

  json data = parseFile(argv[1]);

  std::cout << data << std::endl;
  return 0;
}
