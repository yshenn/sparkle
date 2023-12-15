#include "jsons.h"
#include <fstream>
#include <nlohmann/json.hpp>

/*************************/
// Ret: json
// Args: std::string
// Description: 读取json文件，将其转化为json对象，并返回
/*************************/
json parseFile(std::string filename) {
  std::ifstream jsonfile(filename); // 创建json文件流对象,并打开相应的文件
  json data;                        // 创建json对象
  if (jsonfile) { // 通过流对象状态，判断文件是否打开成功
    data = json::parse(jsonfile);
    jsonfile.close();     // 关闭与流对象绑定的文件
  } else {                // 错误处理
    data = json::array(); // 创建一个空数组存入空文件中
    std::ofstream newfile(
        filename, std::ofstream::out); // 如果文件不存在，则创建一个空的文件
    newfile << data << std::endl;
    newfile.close();
    // std::cerr << filename << "open failed" << std::endl;
    // exit(1);
  }
  return data;
}

void writeFile(std::string filename, json data) {
  std::ofstream jsonfile(filename, std::ofstream::out);
  jsonfile << to_string(data);
}
