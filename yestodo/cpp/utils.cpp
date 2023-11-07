#include "utils.h"

std::string get_time() {
  time_t now = time(0);
  tm *tmofnow = localtime(&now);
  int year = tmofnow->tm_year + 1900;
  int month = tmofnow->tm_mon + 1;
  int day = tmofnow->tm_mday;
  int hour = tmofnow->tm_hour;
  int min = tmofnow->tm_min;

  auto timestr = std::to_string(hour);
  timestr += ":";
  if (min < 10) {
    timestr += "0";
  }
  timestr += std::to_string(min);
  // string datestr = "";
  return timestr;
}
