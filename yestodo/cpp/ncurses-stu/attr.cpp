#include <curses.h>
#include <ncurses.h>

int main(int argc, char *argv[]) {
  initscr();
  start_color();

  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  printw("A Big string which i didn't care to type fully ");
  mvchgat(0, 0, -1, A_BLINK, 1, nullptr);

  refresh();
  getch();
  endwin();

  return 0;
}
