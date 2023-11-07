#ifndef _TODOLIST_H_
#define _TODOLIST_H_

#include "jsons.h"
#include <ctime>
#include <string>
#include <vector>

// or use enum ??
// #define YEAR 0
// #define MON 1
// #define WEEK 2
// #define DAY 3

#define DEFBUF 7

enum Scope {
  DAY,
  WEEK,
  MON,
  YEAR,
};

const std::string jsonfiles[] = {"day.json", "week.json", "mon.json",
                                 "year.json"};

class Entry {
private:
  std::string content;
  bool isdone;
  time_t addtime;
  time_t donetime;

public:
  Entry();
  ~Entry() {}

  void set_isdone(bool isdone);
  void set_addtime(int addtime);
  void set_donetime(int donetime);
  void set_content(std::string content);
  bool is_done();
  int get_addtime();
  int get_donetime();
  std::string get_content();
};

class Todolist {
private:
  const int scope;
  std::string dateofscope;
  int numOfEntrys;
  std::vector<Entry *> entryIng;
  std::vector<Entry *> entryDone;

public:
  Todolist();
  Todolist(int scope);
  ~Todolist() {}

  void load_list(json::iterator it);
  std::string getdate();
  std::vector<Entry *> &getEntryIng();
  std::vector<Entry *> &getEntryDone();
};

class Todos {
private:
  const int scope;
  const int bufsize;
  int pos;
  std::vector<Todolist *> todolists;

public:
  Todos();
  Todos(int scope);
  Todos(int scope, int buf);
  ~Todos() {}

  void load_todos();
  Todolist &get_todolists();
  void set_pos(int dpos);
};

#endif
