# Makefile 介绍
```makefile
target … : prerequisites …
        recipe
        …
        …
```
- Target：由程序生成的文件的名称
- Prerequisites：作为创建目标的输入
- Recipe：make 执行的动作（需要在每个 recipe 行开头加上 tab，可以通过. RECIPEPREFIX 修改）
- 特定的 target 不需要 prerequisites：例如clean
## 一个简单的 Makefile
```makefile
edit : main.o kbd.o command.o display.o \
       insert.o search.o files.o utils.o
        cc -o edit main.o kbd.o command.o display.o \
                   insert.o search.o files.o utils.o

main.o : main.c defs.h
        cc -c main.c
kbd.o : kbd.c defs.h command.h
        cc -c kbd.c
command.o : command.c defs.h command.h
        cc -c command.c
display.o : display.c defs.h buffer.h
        cc -c display.c
insert.o : insert.c defs.h buffer.h
        cc -c insert.c
search.o : search.c defs.h buffer.h
        cc -c search.c
files.o : files.c defs.h buffer.h command.h
        cc -c files.c
utils.o : utils.c defs.h
        cc -c utils.c
clean :
        rm edit main.o kbd.o command.o display.o \
           insert.o search.o files.o utils.o
```
- 用反斜杠\来分行
- 使用 `make` 来创建可执行文件
- 使用 `make clean` 来清除所以可执行文件和对象文件
- 目标的任何先决条件发生变化，需要重新编译与链接，这个过程是链式的
- target clean 是一个 action，不指向文件但是代表一个 action 的是一个假目标（Phony Targets）
## make 如何处理 Makefile
- 默认目标（default goal）：第一个 target（不包括以. 开头的名称，除非包括一个或多个/），可以通过参数和. DEFAULT_GOAL 改变
- make 处理默认规则时，会先处理该规则的依赖（先处理edit）
- 当文件 edit 不存在或者 object 文件发生了更新，则 make 会重新将 object 文件链接 edit 文件
## 变量
- 声明object 变量包括所有的 object 文件是一种标准做法
- 使用‘$(var)’来使用变量
## 让 make 推导 recipes
```makefile
objects = main.o kbd.o command.o display.o \
          insert.o search.o files.o utils.o

edit : $(objects)
        cc -o edit $(objects)

main.o : defs.h
kbd.o : defs.h command.h
command.o : defs.h command.h
display.o : defs.h buffer.h
insert.o : defs.h buffer.h
search.o : defs.h buffer.h
files.o : defs.h buffer.h command.h
utils.o : defs.h

.PHONY : clean
clean :
        rm edit $(objects)
```
- 在 recipes 省略 `.c` 文件 make 会自动推导
- 有隐含规则指明通过相关联的’. c’文件，使用’cc -c’命令，来更新一个’. o’文件
- 如果一个’.c’文件使用隐含规则的时候，该’.c’文件还会自动地加入到 prerequisites 中
## 另一种风格
```makefile
objects = main.o kbd.o command.o display.o \
          insert.o search.o files.o utils.o

edit : $(objects)
        cc -o edit $(objects)

$(objects) : defs.h
kbd.o command.o files.o : command.h
display.o insert.o search.o files.o : buffer.h
```
- 我认为这是一种一对多和多对一的关系, 可以按 prerequisites 也可按 targets 分组
## 清理目录的规则
```makefile
.PHONY : clean
clean :
        -rm edit $(objects)
```
- 可以防止被当前目录名为 clean 的实际文件混淆
- 不应该被放在 makefile 的开头
# 撰写 Makefiles
## Makefile 包含什么
- 显式规则
- 隐式规则
- 变量定义
- 指令
- 注释 `#`
	- 行尾有 `\` 时 `#` 要用 `\#` 替代
	- 不能在变量引用和方法调用时使用注释
	- recipe 中的注释会被传递给shell
## Makefile 的命名
- make 查找 makefile 时会依次尝试 GNUmakefile、makefile 和 Makefile（推荐）
- 用 -f 或 --file 参数可以指定一个或多个 makefile
## 包含 Makefile
```makefile
include filenames…
```
- 使用 include 命令来包含 makefile
- 如果在特定目录中找不到文件，则先搜索用“-I”或“--include-dir”选项指定的任何目录，然后再以 `/usr/local/include, /usr/gnu/include, /usr/local/include, /usr/include` 的顺序搜索
- -include（sinclude）指令可以让make简单地忽略不存在的或者不能重新生成的makefile，并且不产生错误信息
## MAKEFILES 变量
- make 认为 MAKEFILES 的值是一系列文件名，make 先解析这些文件再解析当前文件
## 覆盖其他 makefile
- 当两个 makefile 中同一 target 的不同 recipes 是无效的
# 写作规则
## Prerequisites 的类型
- Normal prerequisites
- Order-only prerequisites
>当将一个文件同时声明为以上两种 Prerequisites 时，normal prerequisites 优先
>Order-only prerequisites 不会因为 prerequisites 的更新重新构造


```makefile
OBJDIR := objdir # := 立即赋值
OBJS := $(addprefix $(OBJDIR)/,foo.o bar.o baz.o)

$(OBJDIR)/%.o : %.c 
        $(COMPILE.c) $(OUTPUT_OPTION) $<

all: $(OBJS)

$(OBJS): | $(OBJDIR) # 防止因为生成.o文件时间戳发生变化而重新构造

$(OBJDIR):
        mkdir $(OBJDIR)
```
