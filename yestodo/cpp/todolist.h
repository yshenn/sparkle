#ifndef TODOLIST_H_
#define TODOLIST_H_

#include "jsons.h"
#include <ctime>
#include <string>
#include <vector>

// or use enum ??
// #define YEAR 0
// #define MON 1
// #define WEEK 2
// #define DAY 3

// 默认的todolist buffer 为7, 即每个scope开始加载的todolist数为7
#define DEFBUF 7

enum Scope {
  DAY,
  WEEK,
  MON,
  YEAR,
};

extern int entrySelected;
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
  json savetojson();
};

class Todolist {
private:
  const int scope;                // 当前todolist的scope
  int dateofscope;                // 当前todolist表示的日期
  int numOfEntrys;                // Entry的数目
  std::vector<Entry *> entryIng;  // 未完成的entry
  std::vector<Entry *> entryDone; // 完成的entry

public:
  Todolist();
  Todolist(int scope);
  Todolist(int scope, int num, int date);
  ~Todolist() {}

  void load_list(json::iterator it);
  int getdate();
  std::vector<Entry *> &getEntryIng();
  std::vector<Entry *> &getEntryDone();
  void addEntry(std::string);
  void changeEntry(std::string);
  void doneEntry();
  void deleteEntry();
  json savetojson();
};

// todos类，表示某个scope的todolists
class Todos {
private:
  const int scope;                   // 范围
  const int bufsize;                 // 默认加载的todolist数
  int pos;                           // 当前显示的todolist的位置
  int numoftodolist;                 // 加载的todolist数目
  bool changed;                      // todos 是否发生改变
  std::vector<Todolist *> todolists; // todolist指针数组

public:
  Todos();
  Todos(int scope);
  Todos(int scope, int buf);
  ~Todos() {}

  void load_todos();
  bool get_todolists(Todolist **todolistOfPos);
  bool set_pos(int dpos);
  bool is_now_pos();
  void set_changed(bool ischanged);
  bool get_changed();
  void save();
};

#endif
