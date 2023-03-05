---
title: Vim基础
categories:
  - CS
  - 杂项
cover: https://file.chriswhite.top/Cover/3.jpg
abbrlink: 539de644
date: 2022-07-08 17:45:54
tags: 杂项
description: 是Vim娘(/≧▽≦)/
---

{% note pink no-icon %}
<p>初识Vim娘，很可能觉得很沮丧，因为用尽浑身解数也不能让她笑一笑，难道注定与她无缘？No！任何想要接近她的人都要学习一张密密麻麻、五颜六色的秘笈……然后为了能够和她更好的性……嗯，幸福生活，可能还需要自己创造秘笈。</p><br/><p align="right">——《萌娘百科》</p>
{% endnote %}

{% note primary no-icon %}
由ChrisWhite翻译自{% btn 'https://quickref.me/vim',Vim cheatsheet,,outline larger %}
{% endnote %}

快速开始 
---------------

### 光标动作图示 

```bash
▼/▶ Cursor   ▽/▷ Target
```
#### 左右移动
```bash
┌───────────── |      
├───────────── 0      $ ──────────────┐ 
│  ┌────────── ^      fe ────────┐    │
│  │  ┌─────── Fo     te ───────┐│    │
│  │  │┌────── To     30| ───┐  ││    │
│  │  ││ ┌──── ge     w ───┐ │  ││    │
│  │  ││ │ ┌── b      e ─┐ │ │  ││    │
│  │  ││ │ │  ┌h      l┐ │ │ │  ││    │
▽  ▽  ▽▽ ▽ ▽  ▽▼      ▼▽ ▽ ▽ ▽  ▽▽    ▽
   echo "A cheatsheet from quickref.me"
```
#### 上下移动
```bash
                 - SCREEN 1 START
   ┌─┬─────────▷ #!/usr/bin/python
   │ │     ┌───▷     
   │ │     │     print("Hello")
   │ │     { } ▶ print("Vim")
   │ │       │   print("!")
   │ │       └─▷    
   │ │ ┌───┬───▷ print("Welcome")
G gg H M L k j ▶ print("to")
│        │   └─▷ print("quickref.me")
│        │       print("/vim")
│        │     
│        └─────▷ 
│                - SCREEN 1 END
└──────────────▷ print("SCREEN 2")
```

### 光标动作(Motions)

| Shortcut                       | Description   |
| ------------------------------ | ------------- |
| `h` _\|_ `j` _\|_ `k` _\|_ `l` | 光标          |
| `<C-u>` _/_ `<C-d>`            | 上/下移动半页 |
| `<C-b>` _/_ `<C-f>`            | 上/下移动整页 |


#### 按词移动
| Shortcut     |Description|
| ------------ | ------------- |
| `b` _/_ `w`  | 前/后单词     |
| `ge` _/_ `e` | 前/后单词末尾 |


#### 在行内移动

| Shortcut             | Description        |
| -------------------- | ------------------ |
| `0` _(zero)_ _/_ `$` | 行首/尾            |
| `^`                  | 行首（不包含空格） |


#### 按字符移动

| Shortcut       | Description              |
| -------------- | ------------------------ |
| `Fe` _/_ `fe`  | 移动到前/后一个 `e`      |
| `To` _/_ `to`  | 移动到前/后一个 `o`后/前 |
| `｜` _/_ `n｜` | 前往第 `1` /`n` 列       |


#### 在文档内移动

| Shortcut       | Description |
| -------------- | ----------- |
| `gg` _/_ `G`   | 首/末行     |
| `:n` _\|_ `nG` | 前往 `n` 行 |
| `}` _/_ `{`    | 后/前一空行 |


#### 在窗口内移动

| Shortcut                | Description                |
| ----------------------- | -------------------------- |
| `H` _/_ `M` _/_ `L`     | 屏幕顶部/中间/底部         |
| `zt` _/_ `zz` _/_  `zb` | 将当前行置于顶部/中间/底部 |



### 插入模式(Insert Mode)
| Shortcut               | Description           |
| ---------------------- | --------------------- |
| `i` _/_ `a`            | 在光标前/后插入       |
| `I` _/_ `A`            | 在行首/尾插入         |
| `o` _/_ `O` _(letter)_ | 在下/上 `1` 行插入    |
| `s` _/_ `S`            | 删除字符/行并插入     |
| `C` _/_ `cc`           | 修改光标至行尾/当前行 |
| `gi`                   | 在最后的插入点插入    |
| `Esc` _\|_ `<C-[>`     | 退出插入模式          |




### 保存与退出
| Shortcut                  | Description          |
| ------------------------- | -------------------- |
| `:w`                      | 保存                 |
| `:q`                      | 退出文件             |
| `:wq` _\|_ `:x` _\|_ `ZZ` | 保存并退出文件       |
| `:wqa`                    | 保存并关闭退出文件   |
| `:q!` _\|_ `ZQ`           | 强制退出             |
| `:qa`                     | 关闭所有文件         |
| `:qa!`                    | 强制退出所有文件     |
| `:w` new.txt              | 写入 `new.txt`       |
| `:sav` new.txt            | 保存并编辑 `new.txt` |
| `:w` !sudo tee %          | 写入只读文件         |




### 一般模式(Normal Mode)
| Shortcut              | Description             |
| --------------------- | ----------------------- |
| `r`                   | 替换1个字符             |
| `R`                   | 进入替换模式            |
| `u` _/_ `3u`          | 撤销 `1` / `3` 次更改   |
| `U`                   | 撤销 `1` 行内的所有更改 |
| `J`                   | 合并当前行和下一行      |
| `<C-r>` _/_ 5 `<C-r>` | 重做 `1` / `5` 次更改   |



### 剪切与粘贴
| Shortcut         | Description                 |
| ---------------- | --------------------------- |
| `x`              | 删除字符 (剪切)             |
| `p` _/_ `P`      | 在光标后/前粘贴             |
| `xp`             | 交换2个字符                 |
| `D`              | 删除光标至行尾的内容 (剪切) |
| `dw`             | 删除单词 (剪切)             |
| `dd`             | 删除行 (剪切)               |
| `ddp`            | 交换上下行                  |
| `yy`             | 复制当前行 (含回车)         |
| `"*p` _\|_ `"+p` | 从系统剪贴板粘贴            |
| `"*y` _\|_ `"+y` | 复制到系统剪贴板            |



#### 在可视模式内(In visual mode)
| Shortcut     | Description        |
| ------------ | ------------------ |
| `d` _\|_ `x` | 删除选择项  (剪切) |
| `s`          | 替换选择项         |
| `y`          | 复制选择项         |




### 重复
| Shortcut | Description                            |
| -------- | -------------------------------------- |
| `.`      | 重复命令                               |
| `;`      | 重复 `f`, `t`, `F` or `T` 操作         |
| `,`      | 向反方向重复 `f`, `t`, `F` or `T` 操作 |
| `&`      | 重复 `:s`                              |
| `@:`     | 重复命令行命令                         |




### 可视模式(Visual mode)
| Shortcut    | Description     |
| ----------- | --------------- |
| `v`         | 进入可视模式    |
| `V`         | 进入行可视模式  |
| `<C-v>`     | 进入块可视模式  |
| `ggVG`      | 选择所有文本    |
| `>` _/_ `<` | 向右/左移动文本 |





### 宏
| -     | -             |
| ----- | ------------- |
| `qi`  | 录制宏 `i`    |
| `q`   | 停止录制宏    |
| `@i`  | 运行宏 `i`    |
| `7@i` | 运行7次宏 `i` |
| `@@`  | 重复宏        |


不仅是 `i` ，你可以设置宏为任何字母


Vim 操作符(Operators) 
---------

### 用法 

| Shortcut | Description  |
|----------|--------------|
| `d`      | <yel>w</yel> |
| Operator | Motion       |

将操作符和动作符结合来使用




### 可选的操作符
| Shortcut | Description       |
| -------- | ----------------- |
| `d`      | 删除              |
| `y`      | 复制 (拷贝)       |
| `c`      | 更改 (删除并插入) |
| `p`      | 粘贴              |
| `=`      | 格式化代码        |
| `g~`     | 切换大小写        |
| `gU`     | 大写              |
| `gu`     | 小写              |
| `>`      | 向右缩进          |
| `<`      | 向左缩进          |
| `!`      | 通过外部程序过滤  |


### 示例 

| Combination          | Description                 |
| -------------------- | --------------------------- |
| `d`<yel>d</yel>      | 删除当前行                  |
| `d`<yel>j</yel>      | 删除2行                     |
| `d`<yel>w</yel>      | 删除光标至下1个单词间的内容 |
| `d`<yel>b</yel>      | 删除单词开始至光标间的内容  |
| `d`<yel>fa</yel>     | 删除光标后内容至 `a` 字符   |
| `d`<yel>/hello</yel> | 删除光标后内容至 `hello`    |
| `c`<yel>c</yel>      | 修改当前行, 与 `S` 等价     |
| `y`<yel>y</yel>      | 拷贝当前行                  |
| `>`<yel>j</yel>      | 2行缩进                     |
| gg`d`<yel>G</yel>    | 删除文档全部内容            |
| gg`=`<yel>G</yel>    | 删除文档所有缩进            |
| gg`y`<yel>G</yel>    | 拷贝整个文档                |




### 计数
```
[count] <operator> <motion>
<operator> [count] <motion>
```
---

| Combination      | Description       |
| ---------------- | ----------------- |
| 2`d`<yel>d</yel> | 删除 `2` 行       |
| 6`y`<yel>y</yel> | 拷贝 `6` 行       |
| `d`3<yel>w</yel> | 删除 `3` 个单词   |
| `d`5<yel>j</yel> | 删除向下的 `5` 行 |
| `>`4<yel>k</yel> | 缩进向上的 `4` 行 |



Vim 文本对象(Text objects) 
------------

### 用法 

| Shortcut | Description                                               | -            |
|----------|-----------------------------------------------------------|--------------|
| `v`      | &nbsp; &nbsp; &nbsp; &nbsp; <pur>i</pur> _/_ <pur>a</pur> | <yel>p</yel> |
| Operator | <pur>i</pur>nner _/_ <pur>a</pur>round                    | Text object  |

操作属性为inner或者around的文本块




### 文本对象 

| Shortcut                                             | Description            |
| ---------------------------------------------------- | ---------------------- |
| <yel>p</yel>                                         | 段落                   |
| <yel>w</yel>                                         | 单词                   |
| <yel>W</yel>                                         | 单词 <br/>(被空白围绕) |
| <yel>s</yel>                                         | 句子                   |
| <yel>[</yel> <yel>(</yel> <yel>{</yel> <yel>\<</yel> | 1个 [], (), 或 {} 块   |
| <yel>]</yel> <yel>)</yel> <yel>}</yel> <yel>\></yel> | 1个 [], (), 或 {} 块   |
| <yel>'</yel> <yel>"</yel> <yel>\`</yel>              | 1句字符串引用          |
| <yel>b</yel>                                         | [( 内的块              |
| <yel>B</yel>                                         | [{ 内的块              |
| <yel>t</yel>                                         | 1个 HTML 标记块        |

详见 `:help text-objects`



### 删除

| Shortcut                    | Description               |
| --------------------------- | ------------------------- |
| `d`<pur>i</pur><yel>w</yel> | 删除单词 (不包含特殊字符) |
| `d`<pur>i</pur><yel>s</yel> | 删除句子                  |
| `d`<pur>i</pur><yel>"</yel> | 删除引号内内容            |
| `d`<pur>a</pur><yel>"</yel> | 删除引号内内容 (包含引号) |
| `d`<pur>i</pur><yel>p</yel> | 删除1个段落               |



### 选择
| Shortcut                                            | Description              |
| --------------------------------------------------- | ------------------------ |
| `v`<pur>i</pur><yel>"</yel>                         | 选择引号内部"`...`"      |
| `v`<pur>a</pur><yel>"</yel>                         | 选择引号 `"..."`         |
| `v`<pur>i</pur><yel>[</yel>                         | 选择括号内部[`...`]      |
| `v`<pur>a</pur><yel>[</yel>                         | 选择括号 `[...]`         |
| `v`<pur>i</pur><yel>w</yel>                         | 选择单词(不包含特殊字符) |
| `v`<pur>i</pur><yel>p</yel>                         | 选择段落 (不包含空行)    |
| `v`<pur>i</pur><yel>p</yel><pur>i</pur><yel>p</yel> | 选择更多段落             |


### 杂项

| Shortcut                    | Description               |
| --------------------------- | ------------------------- |
| `c`<pur>i</pur><yel>w</yel> | 修改单词 (不包含特殊字符) |
| `c`<pur>i</pur><yel>"</yel> | 修改引号内部              |
| `c`<pur>i</pur><yel>t</yel> | 修改内部标记 (HTML)       |
| `c`<pur>i</pur><yel>p</yel> | 修改段落 (不包含空行)     |
| `y`<pur>i</pur><yel>p</yel> | 复制段落 (不包含空行)     |
| `y`<pur>a</pur><yel>p</yel> | 复制段落 (包含空行)       |




Vim 多文件
-------------



### 缓存区
| -          | -                            |
| ---------- | ---------------------------- |
| `:e file`  | 在新的缓存区中编辑文件       |
| `:bn`      | 前往下一个缓存区             |
| `:bp`      | 返回上一个缓存区             |
| `:bd`      | 从缓存区列表中删除文件       |
| `:b 5`     | 打开缓存区 #5                |
| `:b file`  | 通过文件名前往缓存区         |
| `:ls`      | 列出打开的缓存区             |
| `:sp file` | 打开文件并纵向拆分窗口       |
| `:vs file` | 打开文件并横向拆分窗口       |
| `:hid`     | 隐藏当前缓存区               |
| `:wn`      | 写入文件并移动到下一个缓存区 |
| `:tab ba`  | 使用标签栏编辑所有缓存区     |



### 多窗口
| -                    | -                      |
| -------------------- | ---------------------- |
| `<C-w>` `s`          | 纵向拆分窗口           |
| `<C-w>` `v`          | 横向拆分窗口           |
| `<C-w>` `w`          | 切换窗口               |
| `<C-w>` `q`          | 退出窗口               |
| `<C-w>` `T`          | 将窗口打开为新标签     |
| `<C-w>` `x`          | Swap current with next |
| `<C-w>` `-`  _/_ `+` | 减少/增加 高度         |
| `<C-w>` `<`  _/_ `>` | 减少/增加 宽度         |
| `<C-w>` `｜`          | 最大化宽度             |
| `<C-w>` `=`          | 设置窗口高度宽度相等   |
| `<C-w>` `h` _/_ `l`  | 前往 左/右 窗口        |
| `<C-w>` `j` _/_ `k`  | 前往 上/下 窗口        |




### 多标签
| Shortcut       | Description               |
| -------------- | ------------------------- |
| `:tabe [file]` | 在新的标签页中编辑文件    |
| `:tabf [file]` | Open if exists in new tab |
| `:tabc`        | 关闭当前标签页            |
| `:tabo`        | 关闭其他标签页            |
| `:tabs`        | 列出所有标签页            |
| `:tabr`        | 前往第1个标签页           |
| `:tabl`        | 前往最后1个标签页         |
| `:tabm 0`      | 移动至 `0` 位置           |
| `:tabn`        | 前往下个标签页            |
| `:tabp`        | 前往上个标签页            |


#### 一般模式
| Shortcut | Description       |
| -------- | ----------------- |
| `gt`     | 前往下个标签页    |
| `gT`     | 前往上个标签页    |
| `2gt`    | 前往 `2` 号标签页 |






Vim 搜索和替换
------------------

### 搜索
| -        | -                     |
| -------- | --------------------- |
| `/foo`   | 向后搜索              |
| `/foo\c` | 向后搜索 (大小写无关) |
| `?foo`   | 向前搜索              |
| `/\v\d+` | 使用正则表达式搜索    |
| `n`      | 下1个匹配项           |
| `N`      | 前1个匹配项           |
| `*`      | 向后搜索当前单词      |
| `#`      | 向前搜索当前单词      |




### 在指定行替换
```vim
:[range]s/{pattern}/{str}/[flags]
```

---

|                   |                             |
| ----------------- | --------------------------- |
| `:s/old/new`      | 替换第1项                   |
| `:s/old/new/g`    | 替换所有项                  |
| `:s/\vold/new/g`  | 使用正则表达式替换所有项    |
| `:s/old/new/gc`   | 替换所有项 (需要验证)       |
| `:s/old/new/i`    | 替换第1项 (忽略大小写)      |
| `:2,6s/old/new/g` | 替换 `2`-`6` 行的所有匹配项 |

### 在文件中替换
```vim
:%s/{pattern}/{str}/[flags]
```

---

|                   |                          |
| ----------------- | ------------------------ |
| `:%s/old/new`     | 替换第1项                |
| `:%s/old/new/g`   | 替换所有项               |
| `:%s/old/new/gc`  | 替换所有项 (需要验证)    |
| `:%s/old/new/gi`  | 替换所有项 (忽略大小写)  |
| `:%s/\vold/new/g` | 使用正则表达式替换所有项 |



### 范围
| -       | -              |
| ------- | -------------- |
| `%`     | 整个文件       |
| `’<,’>` | 当前选中       |
| `5`     | 第 `5` 行      |
| `5,10`  | `5` 至 `10` 行 |
| `$`     | 末行           |
| `2,$`   | `2` 至末行     |
| `.`     | 当前行         |
| `,3`    | 后 `3` 行      |
| `-3,`   | 前 `3` 行      |




### 全局命令
```vim
:[range]g/{pattern}/[command]
```
---

|              |                               |
| ------------ | ----------------------------- |
| `:g/foo/d`   | 删除所有包含 `foo` 的行       |
| `:g!/foo/d`  | 删除所有不包含 `foo` 的行     |
| `:g/^\s*$/d` | 删除所有空行                  |
| `:g/foo/t$`  | 拷贝包含 `foo` 的行至文件末尾 |
| `:g/foo/m$`  | 移动包含 `foo` 的行至文件末尾 |
| `:g/^/m0`    | 反转一个文件                  |
| `:g/^/t.`    | 重复每一行                    |



### 与 :g 相反
```vim
:[range]v/{pattern}/[command]
```
---

|            |                                                |
| ---------- | ---------------------------------------------- |
| `:v/foo/d` | 删除不包含 `foo` 的行<br/>(等价于 `:g!/foo/d`) |




### 标志(Flags)

| -    | -              |
| ---- | -------------- |
| `g`  | 替换所有存在项 |
| `i`  | 忽略大小写     |
| `I`  | 不忽略大小写   |
| `c`  | 每次替换前验证 |



### Substitute expression (magic)
| -             | -                                |
| ------------- | -------------------------------- |
| `&` _\|_ `\0` | Replace with the whole matched   |
| `\1`...`\9`   | Replace with the group 0-9       |
| `\u`          | Uppercase next letter            |
| `\U`          | Uppercase following characters   |
| `\l`          | Lowercase next letter            |
| `\L`          | Lowercase following characters   |
| `\e`          | End of `\u`, `\U`, `\l` and `\L` |
| `\E`          | End of `\u`, `\U`, `\l` and `\L` |



### Examples
```c 
:s/a\|b/xxx\0xxx/g		         # Modifies "a b"      to "xxxaxxx xxxbxxx"
:s/test/\U& file/                # Modifies "test"     to "TEST FILE"
:s/\(test\)/\U\1\e file/         # Modifies "test"     to "TEST file"
:s/\v([abc])([efg])/\2\1/g	     # Modifies "af fa bg" to "fa fa gb"
:s/\v\w+/\u\0/g		             # Modifies "bla bla"  to "Bla Bla"
:s/\v([ab])|([cd])/\1x/g         # Modifies "a b c d"  to "ax bx x x"
:%s/.*/\L&/                      # Modifies "HTML"     to "html"
:s/\v<(.)(\w*)/\u\1\L\2/g        # Make every first letter of a word uppercase
:%s/^\(.*\)\n\1/\1/              # Remove duplicate lines
:%s/<\/\=\(\w\+\)\>/\U&/g        # Convert HTML-Tags to uppercase
:g/^pattern/s/$/mytext           # Find and append text to the end
:g/pattern/norm! @i              # Run a macro on matching lines
/^\(.*\)\(\r\?\n\1\)\+$          # View the duplicates lines
/\v^(.*)(\r?\n\1)+$              # View the duplicates lines (very magic)
:v/./,/./-j                      # Compress blank lines into a blank line
:g/<p1>/,/<p2>/d                 # Delete inclusively from <p1> to <p2>
```



Vimdiff 
-------


### Usage

```shell script

$ vimdiff file1 file2 [file3]
$ vim -d file1 file2 [file3]
```



### Editing 
```
:[range]diffget [bufspec]
:[range]diffput [bufspec]
```
---
| Shortcut            | Description             |
|---------------------|-------------------------|
| `do` _/_ `:diffget` | Obtain (get) difference |
| `dp` _/_ `:diffput` | Put difference          |
| `:dif`              | Re-scan differences     |
| `:diffo`            | Switch off diff mode    |
| `:1,$+1diffget`     | Get all differences     |
| `ZQ`                | Quit without changes    |


See: [Ranges](#ranges)



### Folds 

| Shortcut      | Description                  |
|---------------|------------------------------|
| `zo` _/_ `zO` | Open                         |
| `zc` _/_ `zC` | Close                        |
| `za` _/_ `zA` | Toggle                       |
| `zv`          | Open folds for this line     |
| `zM`          | Close all                    |
| `zR`          | Open all                     |
| `zm`          | Fold more _(foldlevel += 1)_ |
| `zr`          | Fold less _(foldlevel -= 1)_ |
| `zx`          | Update folds                 |




### Jumping
<br>

| Shortcut | Description         |
|----------|---------------------|
| `]c`     | Next difference     |
| `[c`     | Previous difference |







杂项
-------------


### 大小写 

| Shortcut       | Description        |
| -------------- | ------------------ |
| `vU`           | 大写当前字符       |
| `vu`           | 小写当前字符       |
| `~`            | 切换当前字符大小写 |
| `viw` `U`      | 大写选中单词       |
| `viw` `u`      | 小写选中单词       |
| `viw` `~`      | 切换选中单词大小写 |
| `VU` _/_ `gUU` | 大写当前行         |
| `Vu` _/_ `guu` | 小写当前行         |
| `V~` _/_ `g~~` | 切换当前行大小写   |
| `gggUG`        | 大写所有文本       |
| `ggguG`        | 小写所有文本       |
| `ggg~G`        | 切换所有文本大小写 |





### 跳转

| Shortcut | Description           |
| -------- | --------------------- |
| `<C-o>`  | 返回上1个文件         |
| `<C-i>`  | 前往下1个文件         |
| `gf`     | 前往光标所在文件      |
| `ga`     | 显示16进制，ascii码值 |





### 命令行杂项 
| -              | -                                          |
| -------------- | ------------------------------------------ |
| `:h`           | 打开帮助页面                               |
| `:edit!`       | 重新加载当前文件                           |
| `:2,8m0`       | 移动 `2`-`8` 行至 `0` 行                   |
| `:noh`         | 清除搜索高亮                               |
| `:sort`        | 将行排序 (字典序)                          |
| `:ter`         | 打开终端窗口                               |
| `:set paste`   | 开启插入粘贴子模式 (Insert Paste sub-mode) |
| `:set nopaste` | 开启插入粘贴子模式 (Insert Paste sub-mode) |
| `:cq`          | 退出并返回错误<br/>(终止 Git)              |


### 导航

| Shortcut       | Description            |
| -------------- | ---------------------- |
| `%`            | 最近的/匹配的 `{[()]}` |
| `[(` _\|_ `[{` | 前1个 `(` 或 `{`       |
| `])` _\|_ `]{` | 下1个 `)` 或 `}`       |
| `[m`           | Previous method start  |
| `[M`           | Previous method end    |



### 计数器

| Shortcut | Description |
| -------- | ----------- |
| `<C-a>`  | 增大数字    |
| `<C-x>`  | 减小数字    |



### 标记(Tags) 

| Shortcut             | Description                                     |
| -------------------- | ----------------------------------------------- |
| `:tag Classname`     | Jump to first definition of Classname           |
| `<C-]>`              | 转到定义                                        |
| `g]`                 | 查看所有定义                                    |
| `<C-t>`              | Go back to last tag                             |
| `<C-o> <C-i>`        | 后退/前进                                       |
| `:tselect Classname` | Find definitions of Classname                   |
| `:tjump Classname`   | Find definitions of Classname (auto-select 1st) |



### 格式化
| -       | -                     |
| ------- | --------------------- |
| `:ce 8` | 选中行在第 `8` 列居中 |
| `:ri 4` | 选中行右对齐第 `4` 列 |
| `:le`   | 选中行左对齐          |

详见 `:help formatting`




### Marks 

| Shortcut           | Description                                          |
| ---                | ---                                                  |
| <code>\`^</code>                | Last position of cursor in insert mode               |
| <code>\`.</code>    | Last change in current buffer                        |
| <code>\`"</code>    | Last exited current buffer                           |
| <code>\`0</code>    | In last file edited                                  |
| <code>''</code>    | Back to line in current buffer where jumped from     |
| <code>\`\`</code>    | Back to position in current buffer where jumped from |
| <code>\`[</code>    | To beginning of previously changed or yanked text    |
| <code>\`]</code>    | To end of previously changed or yanked text          |
| <code>\`&lt;</code> | To beginning of last visual selection                |
| <code>\`&gt;</code> | To end of last visual selection                      |
| `ma`               | Mark this cursor position as `a`                     |
| <code>\`a</code>    | Jump to the cursor position `a`                      |
| `'a`               | Jump to the beginning of the line with position `a`  |
| <code>d'a</code>   | Delete from current line to line of mark `a`         |
| <code>d\`a</code>   | Delete from current position to position of mark `a` |
| <code>c'a</code>   | Change text from current line to line of `a`         |
| <code>y\`a</code>   | Yank text from current position to position of `a`   |
| `:marks`           | List all current marks                               |
| `:delm a`          | Delete mark `a`                                      |
| `:delm a-d`        | Delete marks `a`, `b`, `c`, `d`                      |
| `:delm abc`        | Delete marks `a`, `b`, `c`                           |




### 计算器

| Shortcut         | Description |
| ---------------- | ----------- |
| `<C-r>` `=` 7*7  | 展示结果    |
| `<C-r>` `=` 10/2 | 展示结果    |


在插入模式下进行以上操作




### Shell
| -            | -                  |
| ------------ | ------------------ |
| `:!<shell>`  | 执行 Shell 命令    |
| `:r!<shell>` | 读取 Shell 的输出  |
| `:r!date`    | 插入时间           |
| `:!!date`    | 将当前行替换为时间 |




### 命令行

| Shortcut     | Description              | 
| ------------ | ------------------------ |
| `<C-r><C-w>` | 插入当前单词至命令行     |
| `<C-r>"`     | 从 " 寄存器中粘贴        |
| `<C-x><C-f>` | 在插入模式中自动补全路径 |



### 技巧
移除重复行
```shell script
:sort | %!uniq -u
```
在文件中给行编号
```shell script
:%!cat -n
```
拷贝整个文档到剪贴板
```shell script
:%w !pbcopy            # Mac OS X
:%w !xclip -i -sel c   # GNU/Linux
:%w !xsel -i -b        # GNU/Linux
```

补充
--------

- [Devhints](https://devhints.io/vim) _(devhints.io)_
- [Vim cheatsheet](https://vim.rtorr.com/) _(vim.rotrr.com)_
- [Vim documentation](http://vimdoc.sourceforge.net/htmldoc/) _(vimdoc.sourceforge.net)_
- [Interactive Vim tutorial](http://openvim.com/) _(openvim.com)_

