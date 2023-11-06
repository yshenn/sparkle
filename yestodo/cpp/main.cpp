#include "todolist.h"
#include "utils.h"
#include <iostream>
#include <ncurses.h>
#include <string>

void init();

int main(int argc, char *argv[]) {
  std::string username = "yshenn";
  init();
  draw_clock();
  draw_username(username);

  refresh();
  getch();
  endwin();

  return 0;
}

void init() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
}
