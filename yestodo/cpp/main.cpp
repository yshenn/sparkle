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
void init_todo(std::vector<Todos *> &wig_todo) {
  for (int i = 0; i < 4; ++i) {
    Todos *tmp = new Todos(i);
    tmp->load_todos();
    wig_todo.push_back(tmp);
  }
}

int main(int argc, char *argv[]) {
  std::string username = "yshenn";

  int scope = DAY;
  std::vector<Todos *> wig_todo;
  init_todo(wig_todo);

  initUI();
  draw_username(username);
  draw_clock();
  draw_todolist(wig_todo[DAY]->get_todolists());

  refresh();
  getch();
  endwin();

  return 0;
}
