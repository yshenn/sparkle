#include "widgets.h"
#include <vector>

void initUI() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
}

void draw_username(std::string username) { mvprintw(0, 0, username.c_str()); }

void draw_clock() {
  std::string timestr = get_time();
  int lenoftmstr = (int)timestr.size();
  mvprintw(0, COLS - lenoftmstr, timestr.c_str());
}

void draw_todolist(Todolist &list) {
  int y, x;
  getyx(stdscr, y, x);
  y += 1;
  x = COLS / 2;
  mvprintw(y, x, list.getdate().c_str());
  std::vector<Entry *> &entryIng = list.getEntryIng();
  std::vector<Entry *> &entryDone = list.getEntryDone();
  for (std::vector<Entry *>::iterator head = entryIng.begin();
       head != entryIng.end(); head++) {
    mvprintw(++y, 0, (*head)->get_content().c_str());
    mvprintw(++y, 0, "\n");
  }
  for (std::vector<Entry *>::iterator head = entryDone.begin();
       head != entryDone.end(); head++) {
    mvprintw(++y, 0, (*head)->get_content().c_str());
    mvprintw(++y, 0, "\n");
  }
}
