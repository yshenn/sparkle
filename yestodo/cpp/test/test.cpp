#include <ctime>
#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <string>

using namespace std;

string get_time();
void init();
void draw_username(string username);
void draw_clock();

int main(int argc, char *argv[]) {
  string username = "yshenn";

  init();
  draw_clock();
  draw_username(username);

  refresh();
  getch();

  return 0;
}

void init() {
  initscr();
  cbreak();
  keypad(stdscr, true);
}

string get_time() {
  time_t now = time(0);
  tm *tmofnow = localtime(&now);
  int year = tmofnow->tm_year + 1900;
  int month = tmofnow->tm_mon + 1;
  int day = tmofnow->tm_mday;
  int hour = tmofnow->tm_hour;
  int min = tmofnow->tm_min;

  auto timestr = to_string(hour);
  timestr += ":";
  if (min < 10) {
    timestr += "0";
  }
  timestr += to_string(min);
  // string datestr = "";
  return timestr;
}

void draw_username(string username) { mvprintw(0, 0, username.c_str()); }

void draw_clock() {
  string timestr = get_time();
  int lenoftmstr = (int)timestr.size();
  mvprintw(0, COLS - lenoftmstr, timestr.c_str());
}
