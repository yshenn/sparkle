# lib: `ctime` 
The cpp standard library does not have something about date, so cpp inherit them from c : `<ctime>`   
There are four types about time: `clock_t` `time_t` `size_t` `tm`  
`clock_t size_t time_t` represent time or date as integer  
`tm` is a struct:
```cpp
struct tm {
  int tm_sec; // 0 - 59
  int tm_min; // 0 - 59
  int tm_hour; // 0 - 23
  int tm_mday; // 1 - 31
  int tm_mon; // 0 - 11
  int tm_year; // number of years from 1900
  int tm_wday; // which day of week, 0 - 6 , start from Sunday
  int tm_yday; // which day of year, 0 - 365, start from 1.1
  int tm_isdst; //夏令时
}
```

Some func to get time and date
```cpp
time_t now = time(0);  //get the date and time of now
chat *dt = ctime(&now); // transform into a string of localtime
tm *ltm = localtime(&now); // get the tm of localtime

``` 

# How to convert int to string in C++

```cpp
// 1
int a = 10;
char *intstr = itoa(a);
string str = string(intStr);

// 2
int a = 10;
stringstream ss;
ss << a;
string str = ss.str();

``` 
Any other way to conquer this problem, [here](https://stackoverflow.com/questions/5590381/how-to-convert-int-to-string-in-c)  
C++11 introduces `std::stoi` (and variants for each numeric type) and `std::to_string`, the counterparts of the C `atoi` and `itoa` but expressed in term of std::string
```cpp
#include <string>
std::string s = std::to_string(10);

//or shorter
auto s = std::to_string(10);

``` 

# how to convert `string` to `const char *` or `char *` in C++
[here](https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char)   
If you just want to pass a `string` a function that needs const char *), you can use `.c_str()`
```cpp
string str;
const char *c = str.c_str();
```
**Note that** the pointer in only valid as long as the string object is in scope and not modified, as the internal memory may be deallocated or reallocated when the string is modified

If you need a non-const `char *` , call `strdup`
```cpp
string str = "Hello world";

char *mutableCStr = strdup(str.c_str()); // a new C-string

free(mutableCStr); // do not forget to free the memory
```
`strdup` is used to create a copy of the C-string, which you can modified without affecting the original string object


# how to initialize const member in class

In initializer
```cpp
class MyClass {
public:
  const int myConstMember
  
  Myclass() : myConstMember(value){}
  Myclass(int value) : myConstMember(value) {} 
}
``` 

Why cannot I use default assignment operator in constructors to initialize const member?
```cpp
class MyClass {
public:
  const int my ConstMember
  
  Myclass()  //为什么这样不可以
  {
    myConstMember = 1;
  }
  Myclass(int value) : myConstMember(value) {} 
}
``` 
Chatgpt:  
The myConstMember is properly initialized in the constructors using the member initializer list, which is the only place where you can set the value of a const member.



