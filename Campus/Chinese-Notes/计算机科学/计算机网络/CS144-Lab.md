# C++ Crash Course
## C++ 编译过程
1. C++ 编译器在编译过程中将文本文件 (Text File) 转变为对象文件 (Object File)，随后产生的对象文件再被链接器处理
2. 在编译过程中会经过几个过程
	1. 预处理 (Pre-Process)：所有预处理语句 (P-P Statement) 被评估 (Evaluate)，包括 Include / Define / If / Ifdef / Pragma 等
	2. 标记解释 (Tokenizing)
	3. 解析 (Parsing)
3. 编译器的工作是把代码转换为常量数据 (Constant Data) 或指令，将代码转换为抽象语法树 (abstract syntax tree) 的形式
4. 当编译过程完成时，编译器为每个编译单元 (translation unit)，也就是单个 .cpp 文件 (实际上与后缀名无关，文件只是用来给编译器提供源码的方法)，生成对应的对象文件 
5. 在一个 cpp 文件中 include 另一个 cpp 文件往往只是生成了一大的 cpp 文件，所以其中一共包含 1 个编译单元同时只会编译出一个对象文件
###  include 做了什么事
1. 预处理器打开被 include 的文件，读取所有内容并粘贴替换掉写 include 的语句
2. 代码示例
```
.
├── EndBrace.h
├── Log.cpp
├── Math.cpp
├── main.cpp
└── rooster.dSYM
```

```cpp
// EndBrace.h
}
```
```cpp
// Math.cpp
int Multiply(int a, int b) {
    int result = a * b;
    return result;
#include "EndBrace.h"
```
```bash
> g++ -c Math.cpp # 成功编译
> g++ -E Math.cpp # 编译器只执行预处理过程
# 0 "Math.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "Math.cpp"
int Multiply(int a, int b) {
    int result = a * b;
    return result;
# 1 "EndBrace.h" 1
}                 # 实际上只是把 "}" 粘贴到 #include "EndBrace.h" 的位置
# 5 "Math.cpp" 2
```

```cpp
// changed Math.cpp
#define INTEGER int
 INTEGER Multiply(int a, int b) {
    INTEGER result = a * b;
    return result;
}
```
```bash
> g++ -E Math.cpp # 在经过预处理后将所有的 INTEGET 替换为了 int
# 0 "Math.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "Math.cpp"

 int Multiply(int a, int b) {
    int result = a * b;
    return result;
}
```

```cpp
// changed Math.cpp
#if 1
int Multiply(int a, int b) {
	int result = a * b;
	return result;
}
#endif
```
```bash
> g++ -E Math.cpp
# 0 "Math.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "Math.cpp"

int Multiply(int a, int b) {
 int result = a * b;
 return result;
}
```

```cpp
// changed Math.cpp
#if 0
int Multiply(int a, int b) {
	int result = a * b;
	return result;
}
#endif
```
```bash
> g++ -E Math.cpp
# 0 "Math.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "Math.cpp"
```
1. 为什么包含了 `<iostream>` 头文件编译后得到的对象文件会这么大：编译器向原文件内插入了 `iostream` 中 (包括 `iostream` 中 include) 的代码 (三万多行) ![[Pasted image 20231202214923.png]]
```cpp
// changed Math.cpp
#include <iostream>
int Multiply(int a, int b) {
	int result = a * b;
	return result;
}
```
```bash
> g++-13 -E Math.cpp >> output
```
![[Pasted image 20231202220808.png]]
### 生成的对象文件是什么
1. 在 M1 Pro Chip 上生成的 armv 8-a 指令集的代码
```cpp
int Multiply(int a, int b) {
	int result = a * b;
	return result;
}
```
```bash
> g++-13 -S Math.cpp 
```
```asm
	.arch armv8-a
	.text
	.align	2
	.globl __Z8Multiplyii
__Z8Multiplyii:
LFB0:
	sub	sp, sp, #32
LCFI0:
	str	w0, [sp, 12]
	str	w1, [sp, 8]
	ldr	w1, [sp, 12]
	ldr	w0, [sp, 8]
	mul	w0, w1, w0
	str	w0, [sp, 28]
	ldr	w0, [sp, 28]
	add	sp, sp, 32
LCFI1:
	ret
LFE0:
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x1e
	.uleb128 0x1
	.byte	0x10
	.byte	0xc
	.uleb128 0x1f
	.uleb128 0
	.align	3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB0-.
	.set L$set$2,LFE0-LFB0
	.quad L$set$2
	.uleb128 0
	.byte	0x4
	.set L$set$3,LCFI0-LFB0
	.long L$set$3
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE1:
	.ident	"GCC: (Homebrew GCC 13.2.0) 13.2.0"
	.subsections_via_symbols
```
## C++ 链接过程
1. 找到每个函数 (function) 和符号 (symbol) 的位置，并把它们链接到一起
2. 没有外部文件的函数时，应用程序仍然需要知道 entry point 在哪里，C 运行时库需要调用 main 函数 (entry point 不一定是 main 函数，例如 gcc 可以通过 `-e entry_point_function` 修改)，所以仍然需要链接过程
```cpp
// 当生成可执行文件的对象文件没有 entry point 时，会在链接阶段发生错误 
#include <iostream>

void Log(const char* message) {
    std::cout << message << std::endl;
}

int Multiply(int a, int b) {
	int result = a * b;
	return result;
}
```
```bash
> g++-13 Math.cpp
Undefined symbols for architecture arm64:
  "_main", referenced from:
     implicit entry/start for main executable
ld: symbol(s) not found for architecture arm64 # ld: GNU linker
collect2: error: ld returned 1 exit status
```
```cpp
// 当源文件具有语法错误时，会在编译阶段发生错误
#include <iostream>

void Log(const char* message) {
    std::cout << message << std::endl;
}

int Multiply(int a, int b) {
	int result = a * b;
	return result // 缺少";"
}
```
```bash
> g++-13 Math.cpp
Math.cpp: In function 'int Multiply(int, int)':
Math.cpp:9:22: error: expected ';' before '}' token
    9 |         return result
      |                      ^
      |                      ;
   10 | }
      | ~           
```
```cpp
// 修改程序添加 main 函数后，应用生成成功， 不指定 -o 则程序名称为 a.out
#include <iostream>

void Log(const char* message) {
    std::cout << message << std::endl;
}

int Multiply(int a, int b) {
	int result = a * b;
	return result;
}

int main() {

}
```
1. 知道自己的程序在编译阶段还是链接阶段发生错误很重要

## `static` 和 `inline`
```cpp
// Log.cpp
#include <iostream>

void Logrrrrrrrrrr(const char* message) {
    std::cout << message << std::endl;
}

// Math.cpp
#include <iostream>

void Log(const char* message);

static int Multiply(int a, int b) {
	Log("Multiply");
	return a * b;
}

int main() {
	//std::cout << Multiply(5, 8) << std::endl; // 程序执行流中没有用到 Multiply 和 Log 不需要去别的编译单元中寻找 Log 的定义
	std::cin.get();                             // 其他的编译单元也不会使用 Multiply 函数的定义
}
```
1. 在函数前加上 `static` 说明函数只是为当前的编译单元声明的，所以当链接器确保声明的函数不会被当前编译单元使用，也不会被其他编译单元使用时，在链接的过程中就不会报错
2. 函数的声明需要找到一模一样的函数定义，当函数定义的返回值类型和参数类型与声明不同时，链接就会报错
3. 当有两个一模一样的函数定义时，特别是个函数定义在多个 cpp 文件中时，就会发生链接错误
```cpp
// Log.h
void Log(const char* message) {
    std::cout << message << std::endl;
}

// Log.cpp
#include <iostream>
#include "Log.h"

void InitLog() {
	Log("Initialized Log")
}


// Math.cpp
#include <iostream>
#include <"Log.h">

void Log(const char* message);

static int Multiply(int a, int b) {
	Log("Multiply");
	return a * b;
}

int main() {
	std::cout << Multiply(5, 8) << std::endl;
	std::cin.get(); 
}
```

```bash
(base) ➜  3.4ErrorsWarnings clang++ Log.cpp Math.cpp
duplicate symbol 'Log(char const*)' in:
    /var/folders/fm/bbrq4pn10y39tjf0pf97xm4h0000gn/T/Log-1d2c94.o
    /var/folders/fm/bbrq4pn10y39tjf0pf97xm4h0000gn/T/Math-cd0cae.o
ld: 1 duplicate symbol for architecture arm64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```
1. 两个文件中在源文件中都包含了 Log 的定义，所以在链接时会报错

```cpp
// Log.h
inline void Log(const char* message) {
    std::cout << message << std::endl;
}

// Log.cpp
#include <iostream>
#include "Log.h"

void InitLog() {
	// Log("Initialized Log") 
	std::cout << "Initialized Log" << std::endl;
}


// Math.cpp
#include <iostream>
#include <"Log.h">

void Log(const char* message);

static int Multiply(int a, int b) {
	// Log("Multiply");
	std::cout << "Multiply" << std::endl;
	return a * b;
}

int main() {
	std::cout << Multiply(5, 8) << std::endl;
	std::cin.get(); 
}
```
1. 使用 `inline` 时将函数体直接插入到函数调用中，不需要去寻找函数的定义所以就不会产生链接错误
2. 当然，将函数的定义移动到第三个翻译翻元中也同样可以解决这个问题
## 变量
1. C++中变量主要决定了划分存储空间的大小 (用 `sizeof()` 函数来查看)
2. 如果小数后不加"f"则是一个 `double` 类型的数据
3. `bool` 类型的变量只占据一个字节，因为内存的最小寻址单元是一个字节，当要存储多个 `bool` 变量时，可以放在一个字节中
## 函数
1. 在 Debug 模式下，只有主函数不用返回一个值，如果没有指定返回值会默认返回 `0`，其他有返回类型的函数都需要有返回值
2. 将函数分为声明和定义，通常声明会写在头文件里，定义会写在编译单元里
## 头文件
1. 头文件通常用于声明某些函数类型，以便可以用于整个程序中，因为在在链接时我们只能定义一个函数一次，所以需要一个共同的地方存放函数声明，告诉编译单元这个函数存在，就不需要将函数声明到处复制粘贴
2. `#pragma once` 意味着一个翻译单元只包含一个头文件一次
```cpp
// Common.h
#pragma once
#include "Log.h"

// Log.h
void InitLog();
void Log(const char* message);

struct Player {};

// Main.cpp
#include "Common.h"
#include "Log.h"

#include <iostream>

void InitLog() {
	Log("Initializing Log");
}

void Log(const char* message) {
	std::cout << message << std::endl;
}

int main()
{
	InitLog();
	return 0;
}
```
- 预处理后的编译单元中 `struct` 出现了两次
```
......<iostream>

# 0 "main.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "main.cpp"
# 1 "Common.h" 1
       
# 1 "Log.h" 1
void InitLog();
void Log(const char* message);

struct Player {};
# 3 "Common.h" 2
# 2 "main.cpp" 2
# 1 "Log.h" 1
void InitLog();
void Log(const char* message);

struct Player {};
# 3 "main.cpp" 2



void InitLog() {
 Log("Initializing Log");
}

void Log(const char* message) {
 std::cout << message << std::endl;
}

int main()
{
 InitLog();
 return 0;
}
```
- `Log.h` 中加入 `#pragma once` 后可以看到第二处 `struct` 并没有在预编译时被加入
```
# 0 "main.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "main.cpp"
# 1 "Common.h" 1
       
# 1 "Log.h" 1
       
void InitLog();
void Log(const char* message);

struct Player {};
# 3 "Common.h" 2
# 2 "main.cpp" 2




void InitLog() {
 Log("Initializing Log");
}

void Log(const char* message) {
 std::cout << message << std::endl;
}

int main()
{
 InitLog();
 return 0;
}
```
- 更传统的处理方法是使用 `#if #endif`
```cpp
#ifndef _LOG_H
#define _LOG_H

void InitLog();
void Log(const char* message);

struct Player {};

#endif
```
- 相当于将文件粘贴到源文件中，如果_LOG_H 被定义了，则不会被重复定义
```cpp

#include <iostream>

#ifndef _LOG_H
#define _LOG_H

void InitLog();
void Log(const char* message);

struct Player {};

#endif

#ifndef _LOG_H
#define _LOG_H

void InitLog();
void Log(const char* message);

struct Player {};

#endif

void InitLog() {
	Log("Initializing Log");
}

void Log(const char* message) {
	std::cout << message << std::endl;
}

int main()
{
	InitLog();
	return 0;
}
```
1. 尖括号是在编译时有办法告诉编译器的包含路径，而引号包含的文件存在于源文件的相对位置或者是编译器知道的包含路径
2. 为了区分 c 标准库和 c++ 标准库，c 库中的头文件一半有 `.h` 扩展名而 c++ 没有
## 调试
1. 调试包括下断点和查看内存
2. 箭头表示在所指的代码上但是并没有实际执行那段代码
3. 调试时如何跳出循环：在想到达的地方下一个端点并 continue 
## 条件语句
1. 条件结构就是当条件为真时执行一部分代码
2. 所有 c++ 中的运算符都某种方式被实现过了
3. 在检测两个 int 是否相等时，实际上是将每个值从内存中抓取出来并做逐字节的比较
4. 条件判断直接使用一个变量相当于直接去存储该变量的内存块中查看该变量是否为 0
	1. 这种方法同时也能用来检验一个指针是否为空
5. 把判断语句和将要执行的语句放在一行在调试时无法查看执行语句的具体情况
6. `else if` 只是把 else 和 if 结合起来了
```cpp
const char* white = "Moe";
else if (white == "Moe")
	Log("White is very cute.");
//等同于
else {
	if (white == "Moe")
		Log("White is very cute.");
}
```