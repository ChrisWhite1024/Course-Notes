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
2. 在 [[CS144-Lab#虚函数|虚函数]] 实现的 `GetName()` 方法对于子类的重写是没有强制的
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
