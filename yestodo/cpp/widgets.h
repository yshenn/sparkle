#ifndef WIDGETS_H_
#define WIDGETS_H_

#include "todolist.h"
#include "utils.h"
#include <curses.h>
#include <ncurses.h>
#include <string>

extern std::vector<Todos *> wig_todo;
extern int scope;
extern WINDOW *todolistwin;
extern WINDOW *inputwin;
extern int mode;
extern int entrySelected;

enum MODE {
  SHOW_MODE,
  SELECT_MODE,
  EDIT_MODE,
};

void initUI();
void draw_username(std::string);
void draw_clock();
void draw_todolist(Todolist &);
bool key_event();
void clearArea(int, int);
WINDOW *create_newwin(int, int, int, int);

void draw_inputbox(std::string);
void get_entry();
void edit_entry();

#endif
