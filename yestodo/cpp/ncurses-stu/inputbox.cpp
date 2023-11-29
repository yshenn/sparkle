#include <curses.h>
#include <ncurses.h>
#include <string>

int main() {
  initscr();
  std::string mesg = "Enter a string: ";
  // std::string str;
  char str[80];
  int row, col;

  initscr();
  getmaxyx(stdscr, row, col);
  mvprintw(row / 2, (col - mesg.size()) / 2, "%s", mesg.c_str());

  getstr(str);
  mvprintw(LINES - 2, 0, "You Entered: %s", str);

  int ch = getch();
  mvprintw(LINES - 1, 0, "You Entered: %d", ch);
  getch();
  endwin();

  return 0;
}
