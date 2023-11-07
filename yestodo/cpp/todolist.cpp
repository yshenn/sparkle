#include "todolist.h"
// #include "jsons.h"

/********************/
/****** Entry *******/
/********************/
Entry::Entry() : isdone(false), addtime(0), donetime(0) {}

bool Entry::is_done() { return isdone; }
void Entry::set_isdone(bool isdone) { this->isdone = isdone; }
void Entry::set_addtime(int addtime) { this->addtime = addtime; }
void Entry::set_donetime(int donetime) { this->donetime = donetime; }
void Entry::set_content(std::string content) { this->content = content; }
int Entry::get_addtime() { return addtime; }
int Entry::get_donetime() { return donetime; }
std::string Entry::get_content() { return content; }

/********************/
/***** Todolist *****/
/********************/
Todolist::Todolist() : scope(DAY) {}
Todolist::Todolist(int scope) : scope(scope) {}

/*************************/
// Ret: void
// Args: json::iterator
// Description: 通过json的arr迭代器，将json对象中数据读入Todolist对象
/*************************/
void Todolist::load_list(json::iterator it) {
  this->dateofscope = it->value("dateofscope", "not found"); // 设置dateofscope
  json entrys = (*it)["entrys"]; // 获取entrys数组
  json::iterator it_entrys = entrys.begin();
  while (it_entrys != entrys.end()) { // 设置每一条Entry
    Entry *tmp_entry = new Entry;
    tmp_entry->set_addtime((*it_entrys)["addtime"]);   // 设置addtime
    tmp_entry->set_donetime((*it_entrys)["donetime"]); // 设置donetime
    tmp_entry->set_isdone((*it_entrys)["isdone"]);     // 设置isdone
    tmp_entry->set_content((*it_entrys)["content"]);   // 设置content
    if (tmp_entry->is_done()) {
      entryIng.push_back(tmp_entry);
    } else {
      entryDone.push_back(tmp_entry);
    }
    it_entrys++;
  }
}

std::string Todolist::getdate() { return dateofscope; }

std::vector<Entry *> &Todolist::getEntryIng() { return entryIng; }
std::vector<Entry *> &Todolist::getEntryDone() { return entryDone; }

/********************/
/****** Todos *******/
/********************/
Todos::Todos() : scope(DAY), bufsize(DEFBUF), pos(0) {}
Todos::Todos(int scope) : scope(scope), bufsize(DEFBUF), pos(0) {}
Todos::Todos(int scope, int buf) : scope(scope), bufsize(buf), pos(0) {}

/*************************/
// Ret: void
// Args: void
// Description: 加载所需scope（day,week...）的todos
/*************************/
void Todos::load_todos() {
  json data = parseFile(jsonfiles[scope]); // 通过parseFile获取json对象
  json::iterator it = data.begin();        // 利用json中关于arr的迭代器

  // 在arr的大小以及bufsize范围内，将json对象中的数据存入todolists对象数组中
  while (it != data.end() && it < data.begin() + bufsize) {
    Todolist *tmp_list = new Todolist(scope);
    tmp_list->load_list(it);
    todolists.push_back(tmp_list);
    it++;
  }
}

Todolist &Todos::get_todolists() { return *todolists[pos]; }
void Todos::set_pos(int pos) { this->pos = pos; }
