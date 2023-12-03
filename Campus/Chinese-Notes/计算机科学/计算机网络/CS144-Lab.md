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
###  #include 做了什么事
1. 预处理器打开被 include 的文件，读取所有内容并粘贴替换掉写 #include 的语句
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
### 包含头文件的更复杂的情况
