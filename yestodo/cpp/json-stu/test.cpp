#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

int main() {
  int addtime = 123;
  int donetime = 321;
  int isdone = true;
  std::string content = "hello world";
  json entry = json::object();
  entry.push_back(json::object_t::value_type("addtime", addtime));
  entry.push_back(json::object_t::value_type("donetime", donetime));
  entry.push_back(json::object_t::value_type("isdone", isdone));
  entry.push_back(json::object_t::value_type("content", content));
  std::cout << entry << std::endl;
  std::cout << std::endl;
  std::cout << entry["addtime"] << std::endl;
  std::cout << entry["donetime"] << std::endl;
  std::cout << entry["isdone"] << std::endl;
  std::cout << entry["content"] << std::endl;

  return 0;
}
