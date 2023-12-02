#include "todolist.h"
#include "widgets.h"
#include <iostream>
#include <ncurses.h>
#include <string>

int scope = DAY;
std::vector<Todos *> wig_todo;
WINDOW *todolistwin = nullptr;
WINDOW *inputwin = nullptr;
int mode = SHOW_MODE;
int premode = SHOW_MODE;

// if entrySelected == -1, in SHOW_MODE, else in SELECTED_MODE
int entrySelected = -1;

/*************************/
// Ret: void
// Args: std::vector<Todos *> &
// Description: 读入每个scope的数据，创建Todos对象进行初始化工作
/*************************/
void init_todo(std::vector<Todos *> &wig_todo);

int main(int argc, char *argv[]) {
  std::string username = "yshenn";

  // int scope = DAY;
  // std::vector<Todos *> wig_todo;
  init_todo(wig_todo);

  initUI();
  draw_username(username);
  draw_clock();
  Todolist *to_draw;
  if (wig_todo[scope]->get_todolists(&to_draw))
    draw_todolist(*to_draw);

  refresh();
  wrefresh(todolistwin);

  while (true) {
    if (key_event()) {
      break;
    }
    // if (inputwin)
    //   wrefresh(inputwin);
    wrefresh(todolistwin);
    // refresh();
  }

  // save the changes
  // for (auto todos : wig_todo) {
  //  todos->save();
  //}
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
