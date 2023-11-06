#include "jsons.h"

json parseFile(std::ifstream file) {
  json data = json::parse(file);
  return data;
}
