#include "widgets.h"
#include <curses.h>
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
  // getyx(stdscr, y, x);
  y = 2;
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

void clearArea(int y, int x) {
  move(y, x);
  clrtoeol();
}

bool key_event() {
  char key = wgetch(stdscr);
  switch (key) {
  case 'h':
    wig_todo[scope]->set_pos(1);
    draw_todolist(wig_todo[scope]->get_todolists());
    clearArea(5, 0);
    return false;
  case 'l':
    wig_todo[scope]->set_pos(-1);
    draw_todolist(wig_todo[scope]->get_todolists());
    clearArea(5, 0);
    return false;

  //  break;
  // case 'j':

  //  break;
  // case 'k':

  //  break;
  case 'q':
    // some work about closing and cleaning
    return true;
  }
}
