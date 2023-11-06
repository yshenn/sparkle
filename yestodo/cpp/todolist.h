#ifndef _TODOLIST_H_
#define _TODOLIST_H_

#include <string>
#include <vector>

// or use enum ??
#define YEAR 0
#define MON 1
#define WEEK 2
#define DAY 3
#define DEFBUF 7

class Entry {
private:
  std::string content;
  bool isdone;
  int add_time;
  int done_time;

public:
  Entry();
  void changeContent();
  void getcontent();
};

class Todolist {
private:
  const int scope;
  int dateofscope;
  std::vector<Entry> entryIng;
  std::vector<Entry> entryDone;

public:
  Todolist();
  Todolist(int scope);
};

class Todos {
private:
  const int scope;
  const int bufsize;
  std::vector<Todolist> todolists;

public:
  Todos();
  Todos(int scope, int buf);
};

#endif
