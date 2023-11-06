#include "todolist.h"

Todolist::Todolist() : scope(DAY) {}
Todolist::Todolist(int scope) : scope(scope) {}

Todos::Todos() : scope(DAY), bufsize(DEFBUF) {}
Todos::Todos(int scope, int buf) : scope(scope), bufsize(buf) {}
