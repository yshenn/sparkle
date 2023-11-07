#ifndef _WIDGETS_H_
#define _WIDGETS_H_

#include "todolist.h"
#include "utils.h"
#include <ncurses.h>
#include <string>

extern std::vector<Todos *> wig_todo;
extern int scope;

void initUI();
void draw_username(std::string username);
void draw_clock();
void draw_todolist(Todolist &list);
bool key_event();
void clearArea(int y, int x);

#endif
