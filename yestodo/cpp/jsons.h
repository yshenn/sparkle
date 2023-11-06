#ifndef _JSONS_H_
#define _JSONS_H_

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json parseFile(std::ifstream file);

#endif
