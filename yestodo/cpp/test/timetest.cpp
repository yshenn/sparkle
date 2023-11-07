#include <ctime>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  time_t now = time(0);
  cout << now << endl;

  time_t next = time(0);
  cout << next << endl;

  return 0;
}
