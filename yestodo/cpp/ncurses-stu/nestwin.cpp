#include <curses.h>
#include <ncurses.h>

int main(int argc, char *argv[]) {
  initscr();
  noecho();
  cbreak();
  mvwprintw(stdscr, 0, 0, "Hello World!");

  WINDOW *nest = newwin(LINES / 2, COLS / 2, LINES / 4, COLS / 4);
  mvwprintw(nest, 0, 0, "Hello World!");

  mvwprintw(stdscr, LINES, 0, "Hello World!");
  refresh();
  wrefresh(nest);
  getch();

  endwin();
  return 0;
}
