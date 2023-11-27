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

  erase(); // clear the whole window (scr)
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
  Todolist *to_draw;
  int tmp_scope = 0;
  switch (key) {
  case 'h':
    if (wig_todo[scope]->set_pos(1)) {
      if (wig_todo[scope]->get_todolists(&to_draw))
        draw_todolist(*to_draw);
      // clearArea(5, 0);
    }
    return false;
  case 'l':
    if (wig_todo[scope]->set_pos(-1)) {
      if (wig_todo[scope]->get_todolists(&to_draw))
        draw_todolist(*to_draw);
      // clearArea(5, 0);
    }
    return false;

  case 'j':
    tmp_scope = scope + 1;
    if (tmp_scope < 4) {
      scope = tmp_scope;
      if (wig_todo[scope]->get_todolists(&to_draw))
        draw_todolist(*to_draw);
    }
    return false;

  //  break;
  case 'k':
    tmp_scope = scope - 1;
    if (tmp_scope > -1) {
      scope = tmp_scope;
      if (wig_todo[scope]->get_todolists(&to_draw))
        draw_todolist(*to_draw);
    }
    return false;

  //  break;
  case 'q':
    // some work about closing and cleaning
    return true;
  default:
    return false;
  }
}
