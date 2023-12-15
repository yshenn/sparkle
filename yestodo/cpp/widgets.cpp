#include "widgets.h"
#include "todolist.h"
#include "utils.h"
#include <curses.h>
#include <ios>
#include <ncurses.h>
#include <vector>

void initUI() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
}

void draw_username(std::string username) { mvprintw(0, 0, username.c_str()); }

void draw_clock() {
  std::string timestr = get_time();
  int lenoftmstr = (int)timestr.size();
  mvprintw(0, COLS - lenoftmstr, timestr.c_str());
}

void draw_todolist(Todolist &list) {
  if (todolistwin)
    delwin(todolistwin);
  int height = LINES - 3; // leave one line to inputbox
  int width = COLS;
  int starty = 2;
  int startx = 0;
  todolistwin = create_newwin(height, width, starty, startx);
  int y, x;
  // getyx(stdscr, y, x);
  y = 2;
  std::string datastr = datetostr(list.getdate(), scope);
  x = (COLS - datastr.size()) / 2;

  // erase(); // clear the whole window (scr)
  mvwprintw(todolistwin, y++, x,
            datastr.c_str()); // draw the data string

  // date todolist entries which have not done
  std::string entrystr;
  std::vector<Entry *> &entryIng = list.getEntryIng();
  int numofentrying = entryIng.size();
  int counter = 0;
  for (std::vector<Entry *>::iterator head = entryIng.begin();
       head != entryIng.end(); head++) {
    entrystr = (*head)->get_content();
    x = (COLS - entrystr.size()) / 2;
    // Attention: -1 % 1 = 0
    if (entrySelected != -1 && counter++ == entrySelected % numofentrying) {
      wattron(todolistwin, COLOR_PAIR(1));
      mvwprintw(todolistwin, ++y, x, entrystr.c_str());
      mvwprintw(todolistwin, ++y, x, "\n");
      wattroff(todolistwin, COLOR_PAIR(1));
    } else {
      mvwprintw(todolistwin, ++y, x, entrystr.c_str());
      mvwprintw(todolistwin, ++y, x, "\n");
    }
  }

  // date todolist entries which have done
  std::vector<Entry *> &entryDone = list.getEntryDone();
  wattron(todolistwin, COLOR_PAIR(2));
  for (std::vector<Entry *>::iterator head = entryDone.begin();
       head != entryDone.end(); head++) {
    entrystr = (*head)->get_content();
    x = (COLS - entrystr.size()) / 2;
    mvwprintw(todolistwin, ++y, x, entrystr.c_str());
    mvwprintw(todolistwin, ++y, x, "\n");
  }
  wattroff(todolistwin, COLOR_PAIR(2));
}

void draw_inputbox(std::string entryStr) {
  // inputbox in the last line of screen
  int height = 1;
  int width = COLS;
  int starty = LINES - 1;
  int startx = 0;
  inputwin = create_newwin(height, width, starty, startx);

  wattron(inputwin, COLOR_PAIR(3));
  mvwprintw(inputwin, 0, 0, entryStr.c_str());
  wattroff(inputwin, COLOR_PAIR(3));
}

WINDOW *create_newwin(int height, int width, int starty, int startx) {
  WINDOW *tmp_win;
  tmp_win = newwin(height, width, starty, startx);
  return tmp_win;
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
    if (mode == SHOW_MODE) {
      if (wig_todo[scope]->set_pos(1)) {
        if (wig_todo[scope]->get_todolists(&to_draw))
          draw_todolist(*to_draw);
        // clearArea(5, 0);
      }
    }
    return false;

  case 'l':
    if (mode == SHOW_MODE) {
      if (wig_todo[scope]->set_pos(-1)) {
        if (wig_todo[scope]->get_todolists(&to_draw))
          draw_todolist(*to_draw);
        // clearArea(5, 0);
      }
    }
    return false;

  case 'j':
    if (mode == SHOW_MODE) {
      tmp_scope = scope + 1;
      if (tmp_scope < 4) {
        scope = tmp_scope;
        if (wig_todo[scope]->get_todolists(&to_draw))
          draw_todolist(*to_draw);
      }
    }
    return false;
  //  break;
  case 'k':
    if (mode == SHOW_MODE) {
      tmp_scope = scope - 1;
      if (tmp_scope > -1) {
        scope = tmp_scope;
        if (wig_todo[scope]->get_todolists(&to_draw))
          draw_todolist(*to_draw);
      }
    }
    return false;
  case 9:
    // 在SHOW_MODE下，并且是最新的todolist中，才可以进入SELECT_MODE进行选中和编辑
    if (mode == (SHOW_MODE && wig_todo[scope]->is_now_pos()) ||
        mode == SELECT_MODE) {
      entrySelected++;
      if (wig_todo[scope]->get_todolists(&to_draw))
        draw_todolist(*to_draw);
      mode = SELECT_MODE;
    } else {
    }
    return false;

    // key <ESC> : 27
#if 0
  case 27:
    if (mode == SELECT_MODE) {
      entrySelected = -1;
      if (wig_todo[scope]->get_todolists(&to_draw))
        draw_todolist(*to_draw);
      mode = SHOW_MODE;
    } else {
    }
    return false;
#endif

  case 'o': // 新建要一个entry
    if (mode == SELECT_MODE || mode == SHOW_MODE) {
      char newentry[80];
      std::string entryStr = "New Entry: ";
      draw_inputbox(entryStr);
      wrefresh(inputwin);
      wmove(inputwin, 0, entryStr.size());
      echo();
      wgetstr(inputwin, newentry);
      noecho();
      if (wig_todo[scope]->get_todolists(&to_draw)) {
        to_draw->addEntry(newentry);
        wig_todo[scope]->set_changed(true);
      }
      draw_todolist(*to_draw);

      delwin(inputwin);

      return false;
    }

  case 'd': // done a task
    if (mode == SELECT_MODE) {
      if (wig_todo[scope]->get_todolists(&to_draw)) {
        to_draw->doneEntry();
        wig_todo[scope]->set_changed(true);
        // back to show mode , reset 'mode' and 'entrySelected'
        mode = SHOW_MODE;
        entrySelected = -1;
        draw_todolist(*to_draw);
      }
      return false;
    }

  // 模仿h-m-m
  // 编辑条目的方式，将所有的编辑工作放在todolistwin/stdscr的最下方，专门有一个编辑行
  case 'C': // 覆盖当前entry，并重新编辑
    if (mode == SELECT_MODE) {
      char changedEntry[80];
      std::string entryStr = "Change Entry: ";
      draw_inputbox(entryStr);
      wrefresh(inputwin);
      wmove(inputwin, 0, entryStr.size());
      echo();
      wgetstr(inputwin, changedEntry);
      noecho();
      if (wig_todo[scope]->get_todolists(&to_draw)) {
        to_draw->changeEntry(changedEntry);
        wig_todo[scope]->set_changed(true);
      }
      draw_todolist(*to_draw);

      delwin(inputwin);
    }
    return false;
  // case 'A': // 在当前entry后面添加内容
  // case 'I': // 在当前entry后面添加内容
  case 'D': // delete the entry
    if (mode == SELECT_MODE) {
      if (wig_todo[scope]->get_todolists(&to_draw)) {
        to_draw->deleteEntry();
        wig_todo[scope]->set_changed(true);
      }
      draw_todolist(*to_draw);
    }
    return false;

  case 's':
    if (mode == SHOW_MODE) {
      for (auto it = wig_todo.begin(); it != wig_todo.end(); it++) {
        if ((*it)->get_changed()) {
          (*it)->save();
        }
      }
    }
    return false;

  //  break;
  case 'q':
    if (mode == SELECT_MODE) {
      entrySelected = -1;
      if (wig_todo[scope]->get_todolists(&to_draw))
        draw_todolist(*to_draw);
      mode = SHOW_MODE;
      return false;
    } else {
      // some work about closing and cleaning
      return true;
    }
  default:
    return false;
  }
}
