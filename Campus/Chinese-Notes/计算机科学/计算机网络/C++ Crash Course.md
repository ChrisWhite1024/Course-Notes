# C++ Crash Course
## 编译过程
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
## 链接过程
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
## 条件
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
## 循环
1. `for loop`
2. 不用先声明变量或每次循环更新值时，用 `while` 通常是更好的选择
3. `do while` 的 body 至少会被执行一次
## 控制
1. `continue`
2. `break`
3. `return`
## 指针
1. 指针存储了内存地址的数值
2. 指针的类型只对操作内存有用
- 可以使用 `new` 在让程序在堆上分配一段空间
```cpp
char* buffer = new char[8];
memset(buffer, 0, 8);

delete[] buffer;
```
1. 二级指针只是指向一个指针，而这个指针又指向一个内存地址
```cpp
char* buffer = new char[8];
memset(buffer, 0, 8);

char** ptr buffer;

delete[] buffer;
```
## 引用
1. 在本质上来说，引用就是指针
2. 引用必须引用一个已经存在的变量，引用本身并不是一个新的变量，并不占据内存空间
```cpp
int a = 5;
int& ref = a;
ref = 2;
```
- Passing by reference, 所做的事情是相同的，引用只是指针的一种语法🍬，所以声明引用时必须立刻给引用赋值
```cpp
void Increment(int* value) {
	(*value)++;
}

int main() {
	int a = 5;
	Increment(&a)
}
```

```cpp
void Increment(int& value) {
	value++;
}

int main() {
	int a = 5;
	Increment(a)
}
```
- 如果想改变引用指代的内容，需要用到指针才行
```cpp
	int a = 5;
	int b = 8;

	int& ref = a;
	ref = b; // 变量 a 内存地址的值被赋为 8 

	int* ref = &a;
	*ref = 2;
	ref = &b;
	*ref = 1;
```
## 类
1. 类是一种将数据和函数组织在一起的方式
2. 注意类的结尾还有一个分号
3. 创建类时可以指定类中成员的可见性，默认情况下类中的成员访问控制都是私有的
4. 类和结构的区别是默认情况下类的成员是私有的，C++ 中结构体存在的意义是保持和 C 的兼容性
5. Cherno 在使用一些简单数据结构 POD (plain old data) 或者仅包含一些变量的结构
6. 如果需要用到继承，使用类比较合适
### 从头开始写一个类
```cpp
#include <iostream>

class Log {
public:
	const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;
private:
	int m_LogLevel = LogLevelInfo;
public:
	void SetLevel(int level) {
		m_LogLevel = level;
	}

	void Error(const char* message) {
		if (m_LogLevel >= LogLevelError)
			std::cout << "[Warning]: " << message << std::endl;		
	} 
	void Warn(const char* message) {
		if (m_LogLevel >= LogLevelWarning)
			std::cout << "[Warning]: "<< message << std::endl;		
	} 
	void Info(const char* message) {
		if (m_LogLevel >= LogLevelInfo)
			std::cout << "[Info]: "<< message << std::endl;		
	} 
};

int main() {
	Log log;
	log.SetLevel(log.LogLevelError);
	log.Warn("Hello");
	log.Info("Hello");
	log.Error("Hello");
	std::cin.get();	
}
```

## `static` 关键字
1. 类外 `static` 关键字在链接阶段修饰的函数是局部的，只对定义它的编译单元可见
2. 类和结构体内部的 `static` 表示被修饰的这部分内存是这个类的所有实例共享的
### 类和结构体外的`static`
1. `extern` 关键字，在另外的编译单元中寻找该名称的定义，这又被称为 external linking
2. 什么时候用 `static` 就像对类成员使用 `private` 一样
### 类和结构体内的 `static`
1. 通过类实例引用静态变量是没有意义的 (this)
2. 静态方法不用通过类的实例就可以调用 (类名加规范解析运算符就可以访问)
3. 在静态方法内部也无法访问到类的实例，不能写引用类的实例的代码，也不能访问非静态变量
4. 不同类实例中使用的静态变量指向同一个内存空间，就像在命名空间里一样，通常使用 `[Class Name]::[Variable]` 来调用
5. 本质上在类里写的每个非静态方法都会获得当前的类实例作为参数 (this 指针)，静态方法因为并没有传入隐藏参数 (this) 所以不知道怎么访问类实例中的数据
## 局部作用域中的 static 
1. 之前了解的是全局作用域中的 static 以及类和结构体内的 static 
2. 生命周期：变量在被删除之前在内存中停留多久
3. 作用域：可以访问这个变量的范围
4. local static 变量允许声明一个生命周期是整个程序的生存期的变量，但是作用域被限制在声明变量的函数中 (不一定是函数，if 语句之类的也行)
```cpp
#include <iostream>

void Function() {
	static int i = 0;
	i++;
	std::cout << i << std::endl
}

int main() {
	Function();
	std::cin.get();
	return 0;
}
```
1. 当然可以通过声明全局变量来做到这一点，但是在任何地方都能访问到这个变量
2. 不使用静态局部变量时，如果要创建一个单例类，需要写很多的代码
```cpp
#include <iostream>

class Singleton {
private:
	static Singleton* s_Instance;
public:
	static Singleton& Get() { return *s_Instance; }
	void Hello() {}
};

class Singleton {
public:
	static Singleton& Get() {
		static Singleton instance; //如果没有 static 关键字在跳出函数作用域时栈上的 instance 在一段时间后会被销毁，而这在C++中是不安全的，此时通过引用访问它可能会导致未定义的行为，一段时间后访问这个引用可能会出错
		return instance;
	}
	
	void Hello() {}
};

int main() {
	Singleton::Get().Hello();

	std::cin.get();
}
```
1. 单例类（Singleton Class）是一种常见的设计模式，用来确保一个类只有一个实例，并且提供一个全局的访问点来获取这个唯一实例。单例模式通常用于管理共享资源，如数据库连接或文件系统，以及在应用程序中实现全局状态或配置管理
## 枚举
1. 用于给一个值指定一个名称，增加代码的可读性
2. 可以通过在名称后加入 `:` 指定枚举的数据类型
3. 枚举实际上就是整数
```cpp
enum Example : unsigned char {
	A = 5, B, C
}
```

```cpp
#include <iostream>

class Log
{
public:
	enum Level
	{
		LevelError = 0, // 和方法名存在命名冲突，此时加入前缀比较好
		LevelWarning,
		LevelInfo
	};

private:
	Level m_LogLevel = LevelInfo; // 如果需要将 LogLevel 的取值范围限制在 enum 的范围内可以将 m_LogLevel 的类型设置为 Level
public:
	void SetLevel(Level level)
	{
		m_LogLevel = level;
	}

	void Error(const char *message)
	{
		if (m_LogLevel >= LevelError)
			std::cout << "[Warning]: " << message << std::endl;
	}
	void Warn(const char *message)
	{
		if (m_LogLevel >= LevelWarning)
			std::cout << "[Warning]: " << message << std::endl;
	}
	void Info(const char *message)
	{
		if (m_LogLevel >= LevelInfo)
			std::cout << "[Info]: " << message << std::endl;
	}
};

int main()
{
	Log log;
	log.SetLevel(Log::LevelError); // Error 枚举值存在于 Log类的命名空间，也有枚举类但是对于普通的 Level 枚举不能将其当作命名空间
	log.Warn("Hello");
	log.Info("Hello");
	log.Error("Hello"); 
	std::cin.get();
}
```

## 构造函数
1. 构造函数没有返回类型，并且命名需要和类名相同
2. 没有指定构造函数实际上会使用一个空的默认构造函数
3. 不像 Java 中，C++中必须手动初始化所有基本类型，所以不要忘记初始化
4. 使用类的静态方法时构造函数不会被调用
```cpp
#include <iostream>

class Entity
{
public:
	float X, Y;

	Entity()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	// 函数重载
	Entity(float x, float y)
	{
		X = x;
		Y = y;
	}

	void Print()
	{
		std::cout << X << ", " << Y << std::endl;
	}
};

int main()
{
	Entity e;
	e.Print();
	std::cin.get();
}
```
1. 如果不想使用类的时候将实例化，有两种方法：
	1. 将构造函数设置为私有
	2. 使用 delete 删除默认构造函数
```cpp
class Log {
private:
	Log() {}
public:
	Log() = delete;
};
```

## 析构函数
1. 析构函数同时适用于栈和堆分配的内存，当用 `new` 关键字在堆上创建一个对象，调用 `delete` 时析构函数会被调用，对于栈上的对象当跳出作用域对象被删除时析构函数也会被调用
2. 在构造函数中进行初始化工作后需要在析构函数中释放内存，否则容易造成内存泄露，如果手动在堆上分配了任何类型的内存空间，也需要手动进行清除操作
```cpp
#include <iostream>

class Entity
{
public:
	float X, Y;

	Entity()
	{
		X = 0.0f;
		Y = 0.0f;
		std::cout << "Created Entity!" << std::endl;

	}

	~Entity() {
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print()
	{
		std::cout << X << ", " << Y << std::endl;
	}
};

void Function() {
	Entity e;
	e.Print();
}

int main()
{
	Function();
	std::cin.get();
}
```

## 继承
1. 类继承使类之间存在相互关联的层级关系
2. 可以帮助避免很多重复代码
3. 继承可以将一系列通用代码放入基类中
```cpp
#include <iostream>

class Entity
{
public:
	float X, Y;

	void Move(float xa, float ya) {
		X += xa;
		Y += ya;
	}
};

class Player : public Entity // Player不仅仅是Player类，同时也是Entity类，Entity中的任何公有成员Player都能访问到，Player是Entity的一个超集
{							 // 多态是使用一个符号表示多种类型
public:
	const char* Name;

	void PrintName() {
		std::cout << Name << std::endl;
	}
};

int main()
{
	std::cout << sizeof(Player) << " " << sizeof(Entity) << std::endl; // 类的大小是可变化的，如果要重写Player中的函数就要维护一个虚函数表，会占用额外的内存

	std::cin.get();
}
```
## 虚函数
1. 虚函数可以在子类中重写方法
2. 虚函数引入了动态分配，通过虚表 (vtable) 来实现编译，虚表是包含类中所有虚函数映射的列表，可以通过虚表在运行时找到正确的被重写的函数，如果要重写一个函数，需要把基类中的原函数设置为虚函数
3. 使用虚函数时的额外开销，需要额外的内存来存储虚表，基类中还有一个指针成员指向虚表，每次调用虚函数时必须遍历虚表去找到最终要运行的函数，在一些嵌入式平台上虚函数的开销可能成为考虑的内容
```cpp
#include <iostream>

class Entity
{
public:
	virtual std::string GetName() { return "Entity"; };
};

class Player : public Entity
{
private:
	std::string m_Name;

public:
	Player(const std::string &name)
		: m_Name(name) {} // 初始化列表，用于在构造函数体执行前初始化成员变量和基类

	std::string GetName() override { return m_Name; }
};

void PrintName(Entity* entity) {
	std::cout << entity->GetName() << std::endl;
}


int main()
{
	Entity* e = new Entity();
	PrintName(e);

	Player* p = new Player("Cherno");
	PrintName(p);						//在类中正常声明的函数或方法调用方法时会去调用属于该类型的方法

	std::cin.get();
}
```

## 纯虚函数
1. 纯虚函数允许定义一个在基类中没有实现的函数，强制子类去实现这个函数
2. 在 [[C++ Crash Course#虚函数|虚函数]] 实现的 `GetName()` 方法对于子类的重写是没有强制的
3. 有时候需要强制子类为某个特定的函数提供自己的定义
4. 接口：只包含为实现的方法并作为一个模版的类，由于接口类实际上不包含方法实现，所以无法实例化这个类
5. 只能实例化实现了所有纯虚函数的类，纯虚函数只要在一条继承链上被实现过就可以，重点是虚函数必须被实现
```cpp
#include <iostream>

class Printable
{
public:
	virtual std::string GetClassName() = 0;
};

class Entity : public Printable
{
public:
	std::string GetClassName() override { return "Entity"; }
};

class Player : public Entity
{
private:
	std::string m_Name;

public:
	Player(const std::string &name)
		: m_Name(name) {}

	std::string GetClassName() override { return "Player"; }
};

void Print(Printable *obj)
{
	std::cout << obj->GetClassName() << std::endl;
}

int main()
{
	Entity *e = new Entity();
	Player *p = new Player("Cherno");

	Print(e);
	Print(p);

	std::cin.get();
}
```

## 可见性
1. 指一个类中的成员和方法是否可见 (能够被访问、调用或使用)
2. 可见性对于程序程序的性能不会造成影响
3. 三种基础的可见修饰符 `private` `protected` `public`
4. `private`：只有当前类可以访问到这些变量 (`friend` 允许其他类访问该类的私有成员)
5. `protected`：可见性比 `private` 更高，但要低于 `public`，当前类以及当前类的派生类都能访问到这些成员
6. 可见性更方便维护、理解和拓展代码，确保他人不会调用不应该被调用的代码
```cpp
class Entity
{
protected:
	int X, Y;
public:
	Entity() {
		X = 0;
	}
};

class Player : Entity
{
public:
	Player() {
		X = 2;
	}
};
```
## 数组
1. 数组是一些元素的集合，是按照特定顺序排列的东西
2. 当索引一个数组中的元素时，会得到一个底层的数据类型
3. 当访问一个不在数组中的索引时会产生内存访问冲突 (memory access violation) ，所以要确定在数组的规定范围内操作
4. 数组常伴随 `for` 循环，可以在特定范围内使用索引进行遍历
5. 数组就是一个指针，指向一个连续的数据块
6. 内存间接寻址，比如在类的地址处存储一个指针指向数组的内存地址，间接寻址会影响性能
7. C++11 中的数组 `std::array` ，有边界检查并且记录数组的大小，使用普通的堆上数组无法得知数组的大小，需要手动维护数组大小，而栈上数组又存在作用域限制
8. 当在栈中用数组申请内存时，数组大小需要是一个编译时就知道的常量，需要使用关键字 `constexpr` ，同时类中的 `constexpr` 变量需要是静态的
```cpp
#include <iostream>
#include <array>

class Entity
{
public:
	static const int exampleSize = 5;
	int example[exampleSize];

	std::array<int, 5> another;

	Entity() {
		for (int i = 0; i < another.size(); i++) {
			example[i] = 2;
		}
	}
}
```
### `std::array`
1. 可以用最多 N 个可转换为 T 的初始值进行聚合初始化 `std::array<int, 3> a = {1, 2, 3};`
2. `N == 0` 时 `array.begin() == array.end()` , `front()` 和 `back()` 的结果是未定义的
## 字符串
1. 字符串是一种能够表示和处理文本的方法，是一个字符数组
2. C++中处理字符的编码方式是 ASCII
3. 字符串结束的位置有一个空中止符 (the null termination character)
4. `std::string` 本质上是 `std::basic_string` 将 char 作为模版参数 (template specializaton) 的模版类实例
```cpp
#include <iostream>
// #include <string>

/*
把类对象传给一个函数实际上是创建了这个对象的拷贝然后再传给函数，
复制string意味着要在堆上创建全新的 char 数组来存储得到的完全相同的文本
这非常慢
*/
void PrintString(std::string& string) { 
	std::cout << string << std::endl;
}

int main()
{
	// C++中用字符串定义时实际的类型是 const char*
	std::string name = "Cherno"; // name 是在栈上分配的，无法使用 delete
	name += "Hello";
	name.size();
	bool contains = name.find("no") != std::string::npos; // find 返回文本的位置
	std::cout << name << std::endl; // string头文件重载了 << 操作符，允许将字符串传入输出流

	std::cin.get();
}
```

## 字符串字面量
1. 字符串字面量是在双引号之间的字符
```cpp
#include <iostream>

int main()
{
	using namespace std::string_literals;

	std::string name0 = "Cherno"s + "hello";
	std::wstring name0 = L"Cherno"s + L"hello";
	std::u32string name0 = U"Cherno"s + U"hello";

	const char* example = R"(Line1
Line2
Line3
Line4)";

	const char* ex = "Line1\n"
		"Line2\n"
		"Line3\n";

	const char* name = "Cherno";
	// name[2] = 'a'; // 不可以，实际上指针指向了字符串字面量的位置，但字符串字面量存储在内存的只读部分不可以修改
	const wchar_t* name2 = L"Cherno"; //表示字符串字面量是由宽字符组成的，wchar_t 的大小是由编译器决定的

	// C++11引入的新类型
	const char16_t* name3 = u"Cherno";
	const char32_t* name4 = U"Cherno";

	std::cin.get();
}
```

## `const`
1. `const` 像一个假关键字，因为在生成代码时并没有做什么
2. 与类和结构体成员的可见性相似，是对开发人员的限制，可以简化代码
3. `const` 即开发人员做出承诺某些东西是不会改动的，但可以绕过
```cpp
#include <iostream>

class Entity
{
private:
	int m_X, m_Y;
	int* p_X, p_Y; // p_Y 仍然是 int 类型
	// int *p_X, *p_Y;
	mutable int var;
public:
	int GetX() const // 用在方法之后，表示这个方法不会修改任何实际的类，这是一个只读的方法
	{
		var = 2; // mutable 的变量在 const 方法中仍然可以被修改
		// m_X = 2;     // 不行
		return m_X;
	}

	int GetX() // 所以在类中有可能存在同一个函数的两个版本
	{

	}

	const int* const GetpX() const // 返回了一个不能修改的指针，指针指向的内存也不能被修改，也不会修改 Entity 类
	{

	}

	void SetX(int x)
	{

	}
};

void PrintEntity(const Entity& e) {
	e = Entity(); // 不可以改变 e 的内容
	// 不仅不可以直接修改，通过方法间接修改也是不允许的
	std::cout << e.GetX() << std::endl; // 移除 GetX 后的 const 则该方法不能被调用，因为不能保证 GetX 不改变 e 的内容
}

int main()
{
	const int MAX_AGE = 90;

	int* a = new int;
	*a = 2;                // 不使用 const 可以做两件事，这里可以改变指针指向内存的内容
	a = (int *)&MAX_AGE;   // 也可以改变指针指向的内存地址

	const int* b = new int;
	// int const* b = new int;
	*b = 2;                // 在指针之前加上 const 以后无法修改内存位置的数据
	b = (int *)&MAX_AGE;   // 但是可以改变指针的地址

	int* const c = new int;
	*c = 2;                // 但是可以修改指向地址的内容
	c = (int*)&MAX_AGE;    // 在指针之后加上 const 无法修改指针指向的地址
	c = nullptr;           // 不可以

	std::cin.get();
}
```

## `mutable`
1. 与 `const` 一起使用
2. 在 `lambda` 中使用
```cpp
#include <iostream>

class Entity
{
private:
	std::string m_Name;
	mutable int m_DebugCount;

public:
	const std::string &GetName() const
	{
		m_DebugCount++;
		return m_Name;
	}
};

int main()
{
	const Entity e;
	e.GetName();

	int x = 8;
	auto f = [=]() mutable // &x引用传递 x值传递 &所有变量引用传递 =所有变量值传递
	{
		x++; // 不使用 mutable 会报错

		int y = x;
		y++;		//和使用 mutable 的结果是相同的，使用 mutable 简洁一些
		std::cout << x << std::endl;
	};

	f();
	//x = 8

	std::cin.get();
}
```

## 构造函数初始化列表
```cpp
#include <iostream>

class Example
{
public:
	Example()
	{
		std::cout << "Created Entity!" << std::endl;
	}
	Example(int x)
	{
		std::cout << "Created Entity with " << x << "!" << std::endl;
	}
};

class Entity
{
private:
	std::string m_Name;
	Example m_Example;

public:
	Entity() : m_Name("Unknown") // 尽量保持初始化列表和成员变量的声明顺序相同
	{
		// m_Name = "Unknown"; // 如果写在函数中字符串对象会被构造两次，造成性能浪费
		m_Example = Example(8);
	}

	Entity(const std::string &name) : m_Name(name)
	{
	}

	const std::string &GetName() const { return m_Name; }
};

int main()
{
	Entity e;
	std::cin.get();
}
```

```bash
(base) ➜  Dev ./a.out        
Created Entity!
Created Entity with 8!
```

## 三元运算符
1. 三元运算符只是 if 语句的语法糖
```cpp
#include <iostream>

static int s_Level = 1;
static int s_Speed = 2;

int main()
{
	s_Speed = s_Level > 5 ? 10 : 5;
	s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;

	std::string rank = s_Level > 10 ? "Master" : "Beginner"; // 没有构建中间字符串的原因和返回值优化有关

	std::cin.get();
}
```

## 类的实例化
1. 栈对象的生命周期是由声明的地方的作用域决定的，如果超出作用域，对象的内存会被释放
2. 在堆上创建的对象会在程序运行过程中一直存在直到被手动释放
```cpp
#include <iostream>

using String = std::string;

class Entity
{
private:
	String m_Name;
public:
	Entity() : m_Name("Unknown") {}
	Entity(const String& name) : m_Name(name) {}

	const String& GetName() const {return m_Name;}

};

int main()
{
	Entity* e;
	{
		Entity entity("Cherno");
		e = &entity;
		std::cout << entity.GetName() << std::endl;
	}                   // 跳出作用域时 entity 被销毁了，e 变成了野指针
	std::cin.get();
}
```
1. 如果想让 entity 离开作用域就需要把它分配到堆上
2. 如果有很多的 Entity 栈空间可能太小不足以分配，不得不在堆上分配
3. 在堆上创建的对象需要手动释放，如果忘记 `delete` 就会造成内存泄露，所以也可以使用智能指针，在指针超出作用域时，对象会被自动删除，或者使用共享指针，如果没有指向他的引用时也会被自动删除
4. **如果对象非常大或需要显示控制对象的生命周差就需要在堆上分配**

## `new`
1. `new` 的主要目的是在堆上分配内存，根据所写的类型以字节为单位决定要分配内存的大小
2. 使用 `new` 分配空间，不仅分配了空间，还调用了构造函数
3. `new` 只是一个操作符，通常使用 `new` 会调用底层的 C 函数 `malloc`
```cpp
#include <iostream>

using String = std::string;

class Entity
{
private:
	String m_Name;
public:
	Entity() : m_Name("Unknown") {}
	Entity(const String& name) : m_Name(name) {}

	const String& GetName() const {return m_Name;}

};

int main()
{
	int a = 2;
	int* b = new int[50]; // 200B

	Entity* e = new(b) Entity(); // placement new
	Entity* e = new Entity();
	// Entity* e = (Entity*)malloc(sizeof(Entity)); // 两者的区别是 new 还调用了构造函数

	delete e;
	delete[] b;
	
	std::cin.get();
	delete e;
}
```

## 隐式转换和 explicit 关键字
1. C++允许编译器对代码进行一次隐式的转换
2.  使用 `explicit` 关键字后需要显式调用构造函数, 写低级封装时会派上用场，防止偶然转换或导致性能问题 
```cpp
#include <iostream>

using String = std::string;

class Entity
{
private:
	String m_Name;
	int m_Age;
public:
	Entity(const String& name) : m_Name(name), m_Age(-1) {}
	explicit Entity(int age) : m_Name("Unknown"), m_Age(age) {}

	const String& GetName() const {return m_Name;}

};

void PrintEntity(const Entity& entity) {

}

int main()
{
	PrintEntity(22); // 构造函数加上 explicit 无法隐式转换 
	PrintEntity(Entity(22));
	//PrintEntity("Cherno"); //不可以工作，因为 Cherno 的类型是 const char*，并不是 std::string 类型，C++需要做两次隐式转换，是不符合要求的
	PrintEntity(String("Cherno"));
	PrintEntity(Entity("Cherno"));


	Entity a = String("Cherno");
	Entity b = 22; // 将 int 隐式转换为了 Entity，加上 explicit 关键字后无法隐式转换
	Entity b(22);
	Entity b = Entity(22);
	
	std::cin.get();
}
```

## 操作符和操作符重载
1. 操作符是代替函数执行某些事情的符号
2. 操作符重载指给操作符一个新的含义，定义或更改一个操作符的行为
3. 当操作符重载非常有意义时才使用
```cpp
#include <iostream>

struct Vector2
{
	float x, y;

	Vector2(float x, float y) : x(x), y(y) {
	}

	Vector2 Add(const Vector2& other) const {
		// return *this + other;
		// return operator+(other); // 像函数一样调用
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator+(const Vector2& other) const {
		return Add(other);
	}

	Vector2 Multiply(const Vector2& other) const {
		return Vector2(x * other.x, y * other.y);
	}

	Vector2 operator*(const Vector2& other) const {
		return Multiply(other);
	}

	bool operator==(const Vector2& other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2& other) const {
		return !(*this == other);
		// return !operator==(other);
	}
};

// 要重载操作符的原始定义
std::ostream& operator<<(std::ostream& stream, const Vector2& other) {
	stream << other.x << ", " << other.y;
	return stream;
}

int main()
{
	Vector2 position(4.0f, 4.0f);
	Vector2 speed(0.5f, 1.5f);
	Vector2 powerup(1.1f, 1.1f);

	Vector2 result2 = position + speed * powerup;

	std::cout << result2 << std::endl;
	std::cin.get();
}
```

## `this`
1. this 是函数所属当前对象实例的指针
```cpp
#include <iostream>

class Entity
{
public:
	int x, y;

	Entity(int x, int y);

	int GetX() const // 不能修改这个类，所以需要在 Entity* 前加上 const
	{
		const Entity *e = this;
		return x;
	}

	const Entity* const SoManyConst(const Entity* const & e) const
	{
	}
};

void PrintEntity(const Entity& e);

Entity::Entity(int x, int y)
{
	// Entity *const e = this; // const 在右边意味着不能改变 e 的指向
	// this = nullptr 不可以
	// Entity*& const e = this;
	// [const] (常量引用) [Entity* const] (引用类型)
	// const Entity *const &e = this; // 指向 Entity 对象的常量指针的引用，不能改变
	this->x = x;
	this->y = y;
	PrintEntity(*this);
}

void PrintEntity(const Entity& e)
{
	// ...
}

int main()
{
	std::cin.get();
}
```

## 对象的生命周期
1. C++每次进入一个作用域时实际上是在 push 栈帧
2. 作用域可以是类作用域，函数作用域，if / for /while 作用域等等
3. 在栈上创建的变量如果离开作用域这个变量就不存在了
```cpp
#include <iostream>

class Entity
{
public:
	Entity()
	{
		std::cout << "Created Entity!" << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}
};

class ScopedPtr
{
private:
	Entity* m_Ptr;
public:
	ScopedPtr(Entity* ptr)
		: m_Ptr(ptr)
	{

	}

	~ScopedPtr()
	{
		delete m_Ptr;
	}
};

int main()
{
	{
		ScopedPtr e = new Entity(); // e 超出作用域后调用析构函数在堆上分配的 Entity() 也被销毁了
	}
	std::cin.get();
}
```

## 智能指针
1. 使用智能指针的情况下当调用 `new` 时不用调用 `delete` 
2. `unique_ptr` 作用域指针，当指针超出作用域时就会被销毁，同时不能拷贝一个作用域指针，因为它是 `unique` ，不会产生野指针
3. `unique_ptr` 只是一个栈分配对象，当栈分配对象死亡时，会调用 `delete` 删除对象
4. `shared_ptr` 的实现方式取决于编译器和编译器中的标准库，但是几乎在所有系统中都使用引用计数来实现
5. 引用计数 (reference counting) 是一种跟踪统计指针有多少引用的方法，如果计数为 0 那就会被删除
6. `weak_ptr` 不增加 `shared_ptr` 的引用计数
7. 按照先 `unique_ptr` 后 `shared_ptr` 的顺序来考虑
```cpp
#include <iostream>
#include <memory>oo

class Entity
{
public:
	Entity()
	{
		std::cout << "Created Entity!" << std::endl;
	}

	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print() {}
};

int main()
{

	{
		std::shared_ptr<Entity> e0;
		{
			// std::unique_ptr<Entity> entity = new Entity();  unique_ptr 的构造函数是 explicit 的
			// std::unique_ptr<Entity> entity(new Entity());  显式调用构造函数
			std::unique_ptr<Entity> entity = std::make_unique<Entity>(); // 出于异常安全考虑，在构造函数抛出异常时更加安全，不会得到一个没有引用的空指针导致内存泄露
			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>(); // shared_ptr 会额外分配一块内存用于存储引用计数，如何先构造一个对象再进行隐式转换会造成两次内存分配
			// std::shared_ptr<Entity> e0 = sharedEntity;  当然 shared_ptr 可以被复制
			e0 = sharedEntity;
			std::weak_ptr<Entity> weakEntity = sharedEntity; // 不会增加 shared_ptr 的引用计数，但是可以问 weak_ptr 是否过期
			entity->Print();
		}
	}
	std::cin.get();
}
```
## 拷贝构造函数
1. 复制指的是拷贝内存中的数据，从而在内存中拥有多个副本
2. 复制需要时间，要尽量避免不必要的复制
3. 除了引用外，当写下赋值运算符时，总是在复制不管是赋值地址还是其他值
4. 当试图创建一个新的变量并把另一个相同类型的变量赋值给它时，会调用拷贝构造函数
5. C++默认提供的拷贝构造函数的作用是内存复制，将 other 对象的内存浅拷贝进成员变量，我们更想拷贝的是指针指向的内存
6. 总是通过 `const` 引用去传递对象，没有理由到处复制对象
```cpp
#include <iostream>
#include <cstring>

class String
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size];
		memcpy(m_Buffer, string, m_Size);
		m_Buffer[m_Size] = 0;
	}

	~String()
	{
		delete[] m_Buffer;
	}

	// String(const String& other) = delete;  不允许拷贝

	String(const String& other)
		: m_Size(other.m_Size)
	{
		std::cout << "Copied String!" << std::endl;

		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}

	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);

};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream; 
}

void PrintString(const String& string)
{
	String copy = string;
	std::cout << string << std::endl;
}

int main()
{
	String string = "Cherno";
	String second = string;  // 将成员变量拷贝到一块新的内存中，浅拷贝时只复制了指向字符串地址的指针，所以内存中的两个 String 具有相同的 char * 

	PrintString(string);
	PrintString(second);
	std::cin.get();			// 当到达程序末尾时 delete[] 被调用了两次，程序崩溃
}
```

## 箭头操作符
1. 有时可以重载箭头操作符让代码更简洁
```cpp
#include <iostream>
#include <cstring>

class Entity
{
public:
	void Print() const { std::cout << "Hello!" << std::endl; }
};

class ScopedPtr
{
private:
	Entity* m_Obj;
public:
	ScopedPtr(Entity* entity)
		: m_Obj(entity)
	{

	}

	~ScopedPtr()
	{
		delete m_Obj;
	}

	Entity* GetObject() { return m_Obj; }
	
	Entity* operator->()
	{
		return m_Obj;	
	}

	const Entity* operator->() const
	{
		return m_Obj;
	}
};

int main()
{
	// Entity* ptr = &e;
	// Entity& entity = *ptr;

	// ptr->Print(); // 只是一个快捷方式
	// entity.Print();
	// (*ptr).Print();

	const ScopedPtr entity = new Entity();
	// entity.GetObject()->Print(); // 这太麻烦了
	entity->Print();
	
	std::cin.get();
}
```
1. 箭头操作符也可以用来找出变量在内存中的偏移量 (相对于类起始位置)
```cpp
#include <iostream>
#include <cstring>

struct Vector3
{
	float x, y, z;
};


int main()
{
	int offset = (int)&((Vector3*)nullptr)->x;
	std::cout << offset << std::endl;
	std::cin.get();
}
```

## `std::vector`
1. 标准模版库可以模版化任何东西，容器的底层数据类型由程序员决定，所有东西都由模版组成
2. 模版可以处理程序员提供的底层数据类型
3. `vector` 更应该被称为 `arraylist` 动态数组，跟原始的 `array` 类型不同，`vector` 可以动态调整大小
```cpp
#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
	float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
	stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
	return stream;
}

void Function(const std::vector<Vertex>& vertices)
{

}

int main()
{
	/*
	应该存储堆分配的指针还是对象视情况而定，当然存储对象是理想的，
	因为动态数组的内存是连续分配的，如果要遍历、读取等更方便，但是如果要调整 vector 的大小时开销更大
	*/
	std::vector<Vertex> vertices; 
	vertices.push_back({ 1, 2, 3 }); // 列表初始化
	Function(vertices); // 确保通过引用传递
	vertices.push_back({ 4, 5, 6 });

	for (int i = 0; i < vertices.size(); i++)
	{
		std::cout << vertices[i] << std::endl;
	}

	for (const Vertex& v : vertices)
		std::cout << v << std::endl; // 如果直接使用变量实际上将每个 Vertex 都复制到了 v 中，所以使用引用可以得到相同的结果但没有拷贝过程

	vertices.erase(vertices.begin() + 1);
	vertices.clear();

	std::cin.get();
}
```

## `vector` 使用优化
1. 向 vector 中 push_back 元素时，如果 vector 不够大，需要分配新的内存，并将当前的内容复制到新内存的位置，然后释放旧位置的内存
2. 降低运行速度的原因是需要不断重新分配内存并复制元素，所以优化的方案是如何避免拷贝，需要知道拷贝是什么时候发生的
```cpp
#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
	float x, y, z;

	Vertex(float x, float y, float z)
		: x(x), y(y), z(z)
	{

	}

	Vertex(const Vertex& vertex)
		: x(vertex.x), y(vertex.y), z(vertex.z)
	{
		std::cout << "Copied!" << std::endl;
	}
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
	stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
	return stream;
}

int main()
{
	std::vector<Vertex> vertices; 
	vertices.reserve(3); // 确保拥有足够的内存 优化策略2
	// 创建 vertex 时实际上是在主函数的栈帧上创建(main)，所以 push 时需要将 Vertex 拷贝到 vector 分配的内存中
	/*
	优化策略1：在适当的位置构造 Vertex ，在 vector 分配的内存中
	优化策略2：如果了解环境，直接告诉 vector 不用再调整大小
	*/
	vertices.emplace_back(1, 2, 3); // 仅传递了构造函数的参数列表
	vertices.push_back(Vertex(4, 5, 6)); // 每次 push 一个元素，vertices 的 capacity 就增加 1
	vertices.push_back(Vertex(7, 8, 9));

	std::cin.get();
}
```

## 库
1. 在实际的解决方案的文件夹中，最好保留使用的库的版本
2. 有条件的情况下最好是实际构建源代码，将其编译为静态或动态库，如果没有库的源码，链接二进制文件可能是比较好的选择
3. 使用的是 32 位还是 64 位的库取决于目标应用程序的架构
4. C++ 库通常由两部分包含目录 (includes) 和库目录 (library) ，include 目录中存放需要使用的头文件，lib 目录中有预构建的二进制文件，通常有静态库和动态库
5. 静态链接会将库放入可执行文件，动态链接库在程序运行时被链接
6. 使用库的时候需要包含头文件，同时将链接器指向库文件
7. 引号包含头文件会先检查相对路径，再去检查编译器的 include 路径
8. cpp 中使用 c 语言库需要使用 `extern "C"`

## 动态库
1. 静态链接在编译时发生，动态链接在运行时发生，静态链接和动态链接存在性能差异，静态链接允许更多优化发生
2. 动态库具有静态的动态库版本，即应用程序已经知道动态库中存在什么函数，或可以使用什么函数，另一种是任意加载这个动态库，但不知道里面有什么
3. 头文件同时支持动态链接和动态链接
4. Windows 使用动态链接库可以将 dll 文件放在可执行程序的同一目录下

## 创建和使用库
1. Cherno 如果包含了 VS 解决方案外的东西 (完全与项目无关的外部依赖项) 会使用尖括号，如果是在解决方案中找到的会使用引号
 
## 多返回值
1. 具有多返回值时可以通过参数传递而不使用返回值，最好在参数之前加上 `out`
2. 返回一个数组，但是使用 new 导致堆分配的发生，也可以返回 `array` 和 `vector` ，由于 `array` 在栈上创建而 `vector` 数据存储在堆中，所以 `array` 通常会更快
3. 使用 `tuple` 或 `pair`，`tuple` 是一个包括多个变量的类但是不关心变量的类型
4. 使用结构体返回
```cpp
#include <iostream>
#include <string>
#include <tuple>

struct RetString
{
	std::string string1;
	std::string string2;
};

std::tuple<std::string, std::string> RetMultStringWithTuple()
{
	std::string string1("Hello");
	std::string string2("Hello");

	return std::make_pair(string1, string2);
}

std::pair<std::string, std::string> RetMultStringWithPair()
{
	std::string string1("Hello");
	std::string string2("Hello");

	return std::make_pair(string1, string2);
}

RetString RetMultStringWithStruct()
{
	std::string string1("Hello");
	std::string string2("Hello");

	return { string1, string2 }; 
}

int main()
{
	// std::tuple<std::string, std::string> sources = RetMultString();
	auto sources = RetMultStringWithTuple();
	std::string string1 = std::get<0>(sources);

	auto sources_pair = RetMultStringWithPair();
	std::string string2 = sources_pair.second; // 但是将返回值传入新函数时容易搞混每个变量分别是什么

	auto sources_struct = RetMultStringWithStruct();
	std::string string3 = sources_struct.string1;

	std::cin.get();
}
```

## 模版
1. 模版和宏有点类似，但模版被 evaluate 的时间更晚
2. 模版允许定义一个根据用途进行编译的模版，基于提供给编译器的规则让编译器写代码
```cpp
#include <iostream>

/*
三个函数的不同是输入参数，实际上定义了三个 Print 的重载函数
*/
// void Print(int value)
// {
// 	std::cout << value << std::endl;
// }

// void Print(std::string value)
// {
// 	std::cout << value << std::endl;
// }

// void Print(float value)
// {
// 	std::cout << value << std::endl;
// }

/*
在被调用时函数才被创建
*/
template <typename T> // <>中的是模版参数，类型为 typename / class ，名称是 T
void Print(T value) // 当调用函数时传入的参数就时模版中的参数类型，Print方法只是一个模版，当被调用时模版才真正被创建
{
	std::cout << value << std::endl;
}

void Print(int value) // 被调用时相当于进行了填空，在模版实例化阶段被创建
{
	std::cout << value << std::endl;
}

template <typename T>
void Printerr(T value) // 不调用函数，编译不会报错 (由编译器决定)
{
	std::cout << val << std::endl;
}

int main()
{
	Print(5);  // 根据传递参数的不同，函数被创建并作为源代码被编译
	Print("Hello"); // 自动根据传递的参数类型进行推导
	Print(5.5f);
	
	Print<int>(5); // 显式指定类型
	Print<std::string>("Hello");
	std::cin.get();
}
```
1. 模版也可以使用在类上
```cpp
#include <iostream>

template<typename T, int N>
class Array
{
private:
	T m_Array[N]; // 栈分配的数组所以在编译的时候就必须知道大小
public:
	int GetSize() const { return N; }
};

int main()
{
	Array<int, 5> array;
	Array<std::string, 50> array;

	std::cin.get();
}
```
1. 当模版变的越来越复杂时，需要花很多时间搞清楚哪些东西被编译了，所以要适度使用模版

## 堆与栈内存的比较
1. `new` 关键字实际上调用了 `malloc` 函数，随后调用操作系统底层的函数在堆上分配内存，程序维护一个空闲列表，使用 `malloc` 时程序浏览空闲列表找到空闲内存返回一个指针
2. 使用堆容易出现缓存不命中
```cpp
#include <iostream>

struct Vector3
{
	float x, y, z;
	Vector3()
		: x(10), y(11), z(12)
	{

	}
};

int main()
{
	int value = 5;
	int array[5];
	array[0] = 1;
	array[1] = 2;
	array[2] = 3;
	array[3] = 4;
	array[4] = 5;
	int* hvalue = new int;
	*hvalue = 5;
	int* harray = new int[5];
	harray[0] = 1;
	harray[1] = 2;
	harray[2] = 3;
	harray[3] = 4;
	harray[4] = 5;

	Vector3* hvector = new Vector3();

	delete hvalue;
	delete[] harray;
	delete hvector;

	std::cin.get();
}
```

## 宏
1. 使用预处理器实现自动化
2. 预处理阶段实际上是文本编辑的阶段，可以控制输入给编译器的文本
3. 使用宏可以将代码中的文本替换为其他东西，就像遍历代码执行查找和替换
```cpp
#include <iostream>

#define OPEN_CURLY {

int main()
OPEN_CURLY	
	std::cin.get();
}
```

```cpp
#include <iostream>

#define PR_DEBUG 1 

#if PR_DEBUG == 1 // 如果仅仅判断是否定义了一个 value，如果要修改的话只能注释或者删除先前的定义，取值的话比较可控
#define LOG(x) std::cout << x << std::endl
#elif defined(PR_RELEASE)
#define LOG(x)
#endif

#define MAIN int main() \ // 宏定义可以用反斜杠(Enter 的转义)包含多行，不能 \[space] 会被作为空格的转义
{\
	std::cin.get();\
}

#if 0 // if 可以将整块代码禁用
void Print()
{

}
#endif

int main()
{
	LOG("Hello");
	std::cin.get();
}
```

## `auto`
1. 使用 `auto` 可以让 C++ 自动推导出数据类型，不管是创建、初始化还是赋值时
2. 如果类型非常长使用 auto 能够简化代码，或者进入复杂的代码集包含了模版等，不得不使用 auto
3. auto 也可以用于后置返回类型
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

auto GetName() -> char* // 后置返回类型
{

}

char* GetName() // 如果将 std::string 改为 char * 在 main 函数中使用 auto 就不用重复修改了
{
	return "Cherno";
}

class Device {};

class DeviceManager
{
private:
	std::unordered_map<std::string, std::vector<Device *>> m_Devices;
public:
	const std::unordered_map<std::string, std::vector<Device *>>& GetDevices() const
	{
		return m_Devices;
	}
	
};

int main()
{
	int a = 5;
	auto b = a;

	std::cout << b << std::endl;

	/*
	如果改变 api 客户端不用做出任何改变，但是我也不知道返回值改变了，
	导致原来返回类型的一些方法可能无法使用，并破坏依赖于特定类型的代码
	所以是有两面性的
	*/
	auto name = GetName(); 
	std::string name1 = GetName();

	// name.size(); 不可以
	name1.size();

	std::vector<std::string> strings;
	strings.push_back("Apple");
	strings.push_back("Orange");

	// for (std::vector<std::string>::iterator it = strings.begin();
	// 		it != strings.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }

	for (auto it = strings.begin();
			it != strings.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	using DeviceMap = std::unordered_map<std::string. std::vector<Device*>>;
	DeviceManager dm;
	const DeviceMap&
		devices = dm.GetDevices();

	const auto& devices_auto = dm.GetDevices();
	auto d =dm.GetDevices(); // 增加一次拷贝。返回引用时要给 auto 加上引用符号
	std::cin.get();
}
```

## `std::array`
1. 处理静态数组的类，不能改变大小
2.  `std::array` 有可选的边界检查
3. `size()` 返回的类型是 constexpr 说明 `size()` 方法返回的就是一个数值
```cpp
      // Capacity.
      [[__nodiscard__, __gnu__::__const__, __gnu__::__always_inline__]]
      constexpr size_type
      size() const noexcept { return _Nm; }
```

```cpp
#include <iostream>
#include <array>
#include <algorithm>

void PrintArray(const std::array<int, 5>&  data)
{
	
}

int main()
{

	std::array<int, 5> data;
	data.size();
	std::sort(data.begin(), data.end());
	data[0] = 2;
	data[4] = 1;

	std::cin.get();
}
```

## 函数指针
1. 函数指针是将一个函数赋值给一个变量的方法
2. 通过函数指针可以将函数赋值给一个变量，也可以将函数作为参数传递给其他函数
3. 在可执行文件中找到函数指令的内存地址
```cpp
#include <iostream>

void HelloWorld(int a)
{
	std::cout << "Hello World! Value: " << a << std::endl;
}

int main()
{
	void(*chris)(int) = HelloWorld;

	auto chris = HelloWorld; // 函数只是 cpu 指令

	typedef void(*HelloWorldFunction)(int);
	HelloWorldFunction function = HelloWorld;

	function(8);

	std::cin.get();
}
```

```cpp
#include <iostream>
#include <vector>

void PrintValue(int value)
{
	std::cout << "Value: " << value << std::endl;
}

void ForEach(const std::vector<int>& values, void(*func)(int))
{
	for (int value : values)
		func(value);
}

int main()
{
	std::vector<int> values = { 1, 5, 4, 2, 3 };
	ForEach(values, PrintValue);
	ForEach(values, [](int value){std::cout << "Value: " << value << std::endl;}); // [] 捕获模式

	std::cin.get();
}
```

## `lambda`
1. 只要有函数指针就可以在 C++ 中使用 `lambda`
```cpp
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

void PrintValue(int value)
{
	std::cout << "Value: " << value << std::endl;
}

void ForEach(const std::vector<int>& values, const std::function<void(int)>& func)
{
	for (int value : values)
		func(value);
}

int main()
{
	std::vector<int> values = { 1, 5, 4, 2, 3 };
	auto it = std::find_if(values.begin(), values.end(), [](int value){ return value > 3; });
	std::cout << *it << std::endl;

	ForEach(values, PrintValue);

	int a = 5;
	auto lambda = [=](int value) mutable { a = 5; std::cout << "Value: " << a << std::endl; };

	ForEach(values, lambda); // [] 捕获模式

	std::cin.get();
}
```

## `using namespace`
1. 如果需要使用就尽量在较小的作用域下使用
```cpp
#include <iostream>
#include <string>

namespace apple {
	void print(const std::string& text)
	{
		std::cout << text << std::endl;
	}
}

namespace orange {
	void print(const char* text)
	{
		std::string temp = text;
		std::reverse(temp.begin(), temp.end());
		std::cout << temp << std::endl;
	}
}

using namespace apple;
using namespace orange;

int main()
{
	print("Hello"); // 不使用 orange 命名空间时实际发生了隐式转换，当使用 orange 其提供的 print函数 更加匹配
	// 所以不要用 using namespace

	std::cin.get();
}
```

## 名称空间
1. 名称空间的作用是防止名称冲突
2. 类本身也是一个名称空间
```cpp
#include <iostream>
#include <algorithm>
#include <string>

namespace apple {
	void print(const char* text)
	{
		std::cout << text << std::endl;
	}

	void print_again()
	{

	}
}

namespace orange {
	void print(const char* text)
	{
		std::string temp = text;
		std::reverse(temp.begin(), temp.end());
		std::cout << temp << std::endl;
	}
}

using namespace apple;
using namespace orange;

int main()
{
	using apple::print; // 如果仅仅想使用命名空间中的特定方法可以这么写
	namespace a = apple; // 当然命名空间可以嵌套 namespace a = apple::function ...

	print("Hello"); // C语言没有名称空间，所以不得不将库的名字放在 symbol 之前
	a::print("Hello");
	apple::print_again(); 

	std::cin.get();
}
```

## 线程
```cpp
#include <iostream>
#include <thread>

static bool s_Finished = false;

void DoWork()
{	
	using namespace std::literals::chrono_literals;

	std::cout << "Started thread id =" << std::this_thread::get_id() << std::endl;

	while (!s_Finished)
	{
		std::cout << "Working...\n";
		std::this_thread::sleep_for(1s);
	}
}

int main()
{
	std::thread worker(DoWork);

	std::cin.get();
	s_Finished = true;

	worker.join(); // 在主线程上等待工作进程完成所有的执行后，再继续执行主线程

	std::cout << "Finished." << std::endl;
	
	std::cin.get();
}
```

## 计时
1. 如果需要高精确度的计时需要使用操作系统库
```cpp
#include <iostream>
#include <chrono>
#include <thread>

struct Timer
{
	std::chrono::_V2::system_clock::time_point start, end;
	std::chrono::duration<float> duration;

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count() * 1000.0f;
		std::cout << "Timer took " << ms << "ms " << std::endl; 
	}
};

void Function()
{
	Timer timer;
	for (int i = 0; i < 100; i++)
		std::cout << "Hello" << std::endl; // io 多程序更慢
}

int main()
{
	using namespace std::literals::chrono_literals;

	Function();

	auto start = std::chrono::high_resolution_clock::now();

	std::this_thread::sleep_for(1s);
	
	
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;
	std::cout << duration.count() << "s" << std::endl;
	
	std::cin.get();
}
```

## 多维数组
```cpp
#include <iostream>

int main()
{
	int* array = new int[5];
	int** a2d = new int*[5];
	for (int i = 0; i < 5; i++) // 会造成内存碎片的问题
		a2d[i] = new int [5];

	for (int i = 0; i < 5; i++)
	{
		delete[] a2d[i];
	}

	delete[] a2d;

	int*** a3d = new int**[5];
	for (int i = 0; i < 5; i++)
	{
		a3d[i] = new int*[5];
		for (int j = 0; j < 5; j++)
			a3d[i][j] = new int[5];
	}

	a3d[0][0][0] = 0;

	int* array = new int[5 * 5];
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			array[x + y * 5] = 2;
		}
	}

	std::cin.get();
}
```

## 排序
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
	std::vector<int> values = {3, 5, 1, 4, 2};
	std::sort(values.begin(), values.end()); // 会使用 operator< 进行排序
	std::sort(values.begin(), values.end(), std::greater<int>()); // 使用标准库的函数进行排序
	std::sort(values.begin(), values.end(), [](int a, int b){
		if (a == 1)
			return false; // a 要排在后面
		if (b == 1)
			return true; // a 要排在前面 true 就是 a, b 这个顺序 false 交换一下
		return a < b; // 如果 a > b 返回 false 把 a 排在 b 后面
	});

	for(int value : values)
	{
		std::cout << value << std::endl;
	}

	std::cin.get();
}
```

## 类型双关
1. 比如如果有一个类，想把这个类解释为一段字节流
2. 把拥有的一段内存当作不同类型的内存来对待，将原始类型作为指针，并且将其转换为另一个指针
```cpp
#include <iostream>

struct Entity
{
	int x, y;

	int* GetPositions()
	{
		return &x;
	}
};

int main()
{
	int a = 50;
	// double value = a;  实际上做了一次隐式转换，在内存中的另一个地方存储了 value

	double value = *(double*)&a; // int 占 4 字节 double 占 8 字节
	// double& value = *(double*)&a; // dangerous
	std::cout << value << std::endl;

	Entity e = { 1, 2 }; // 结构体 2 * 4B 没有多余的空间，可以把这个结构体当作一个一维数组
	int* position = (int *)&e;

	int y = *(int*)((char*)&e + 4);

	std::cout << position[0] << ", " << position[1] << std::endl;
	std::cout << y << std::endl;

	std::cin.get();
}
```

## 联合体
1. 联合体只能拥有一个成员