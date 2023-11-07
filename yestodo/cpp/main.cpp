#include "todolist.h"
#include "widgets.h"
#include <iostream>
#include <ncurses.h>
#include <string>

/*************************/
// Ret: void
// Args: std::vector<Todos *> &
// Description: 读入每个scope的数据，创建Todos对象进行初始化工作
/*************************/
int scope = DAY;
std::vector<Todos *> wig_todo;

void init_todo(std::vector<Todos *> &wig_todo);

int main(int argc, char *argv[]) {
  std::string username = "yshenn";

  // int scope = DAY;
  // std::vector<Todos *> wig_todo;
  init_todo(wig_todo);

  initUI();
  draw_username(username);
  draw_clock();
  draw_todolist(wig_todo[scope]->get_todolists());

  refresh();

  while (true) {
    if (key_event()) {
      break;
    }
    refresh();
  }
  // getch();
  // endwin();

  endwin();
  return 0;
}

void init_todo(std::vector<Todos *> &wig_todo) {
  for (int i = 0; i < 4; ++i) {
    Todos *tmp = new Todos(i);
    tmp->load_todos();
    wig_todo.push_back(tmp);
  }
}
