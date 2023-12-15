#include "utils.h"
#include <ctime>
#include <string>

std::string get_time() {
  time_t now = time(0);
  tm *tmofnow = localtime(&now);
  // int year = tmofnow->tm_year + 1900;
  int month = tmofnow->tm_mon + 1;
  int day = tmofnow->tm_mday;
  int hour = tmofnow->tm_hour;
  int min = tmofnow->tm_min;

  std::string timestr = "";
  if (month < 10) {
    timestr += "0";
  }
  timestr += std::to_string(month);
  timestr += ".";
  if (day < 10) {
    timestr += "0";
  }
  timestr += std::to_string(day);
  timestr += " (";
  timestr += std::to_string(hour);
  timestr += ":";
  if (min < 10) {
    timestr += "0";
  }
  timestr += std::to_string(min);
  timestr += ")";
  // string datestr = "";
  return timestr;
}

int get_dateofscope(int scope) {
  int dateofscope = 0;
  time_t now = time(nullptr);
  tm *tmofnow = localtime(&now);
  int year = tmofnow->tm_year + 1900;
  int month = tmofnow->tm_mon + 1;
  int day = tmofnow->tm_mday;
  int week = ((tmofnow->tm_yday + 1 + (6 - tmofnow->tm_wday)) / 7) + 1;
  switch (scope) {
  // day: 20231201
  case 0:
    dateofscope = year * 10000 + month * 100 + day;
    break;

  // week: 202348
  case 1:
    dateofscope = year * 100 + week;
    break;

  // month: 202312
  case 2:
    dateofscope = year * 100 + month;
    break;

  // year: 2023
  case 3:
    dateofscope = year;
    break;
  }
  return dateofscope;
}

std::string datetostr(int dateofscope, int scope) {
  std::string datestr = "";
  switch (scope) {
  case 0:
    datestr += std::to_string(dateofscope / 10000);
    datestr += "-";
    dateofscope %= 10000;
    datestr += std::to_string(dateofscope / 100);
    datestr += "-";
    dateofscope %= 100;
    datestr += std::to_string(dateofscope);
    break;

  case 1:
    datestr += std::to_string(dateofscope / 100);
    datestr += "-W";
    dateofscope %= 100;
    datestr += std::to_string(dateofscope);
    break;

  case 2:
    datestr += std::to_string(dateofscope / 100);
    datestr += "-";
    dateofscope %= 100;
    datestr += std::to_string(dateofscope);
    break;

  case 3:
    datestr += std::to_string(dateofscope);
    break;
  }
  return datestr;
}
