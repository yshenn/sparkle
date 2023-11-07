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

# pacman -Ql packagename
要查看 pacman 已将一个库安装在何处，您可以使用 pacman 自带的 -Ql 选项
```bash
pacman -Ql nlohmann-json
pacman -Ql cjson
```

# #include如何搜索头文件
当编译器遇到 #include 指令时，它会按照特定的搜索路径规则来查找和包含头文件。这些搜索路径规则通常包括以下几个方面：

1. **当前目录（当前工作目录）**：编译器首先查找当前源文件所在的目录。如果头文件位于当前目录中，编译器会成功地找到并包含它。

2. **系统标准头文件目录**：编译器会搜索标准的系统头文件目录，这些目录包含C标准库的头文件以及系统特定的头文件。这些目录通常在编译器安装时被设置好。例如，对于Linux系统，标准头文件通常位于 /usr/include 或 /usr/local/include 目录。

3. **用户自定义头文件目录**：您可以指定额外的头文件搜索路径，这些路径包括您自己编写的头文件或第三方库的头文件。这可以通过编译器的 -I 选项来实现，例如：  
```bash
gcc -I/path/to/custom_headers my_program.c
```
这将告诉编译器在 /path/to/custom_headers 目录中搜索头文件。

4. **环境变量**：有些编译器还可以使用环境变量来指定头文件搜索路径，例如，C_INCLUDE_PATH 和 CPLUS_INCLUDE_PATH。这些环境变量可以包含在makefile中

5. **编译器内置的默认路径**：编译器通常有一组内置的默认头文件搜索路径，这些路径在编译器安装时设置好。


# 如何调试ncurses程序
把要调试的程序的输出重定向到另一个终端上，这样就会把gdb的命令提示和我们的输出分开

```bash
# 查看当前tty的设备名
tty
#/dev/pts/1

# 使用sleep 告诉这个终端不要做任何事，调试结束可以使用<C-c>来唤醒该终端
sleep 100000

# 在gdb中指定对应的tty
(gdb) tty /dev/pts/1


```
