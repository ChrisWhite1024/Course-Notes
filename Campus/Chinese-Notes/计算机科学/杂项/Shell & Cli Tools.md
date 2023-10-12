# 什么是 Shell
 - 用户与系统内核交互的界面，负责接收命令的程序，处理要做的工作交给内核执行，并处理返回输出
 - Terminal：从用户获取输入，传递给 Shell ，等待 Shell 执行完毕后将结果传递回用户
# 基础 Shell 命令
- Prompt：命令提示符，用来等待输入并提供一些信息
- 常见命令
```bash
pwd # 获取当前路径
ls -l # 列出详细信息
ls -h
touch file # 创建一个文件
rm -r # 递归删除目录 
rm -f # 强制删除
cp src dst # 复制文件或目录
cp -r # 递归复制目录
mv src dst # 移动文件或目录
find path -name pattern # 在path下查找文件名匹配pattern的文件
cat file # 输出文件内容 
cat -n # 输出行号
head -n lines files # 输出文件前lines行
tail -n lines file # 输出文件后lines行
more/less file # 分页输出文件内容
echo # 输出字符串
whoami # 获取当前用户
date # 获取当前时间
ps # 显示进程信息
grep # 查找文件内容
diff # 比较文件内容
ln # 创建软链接
whereis/which # 查找命令位置
```
- 重定向
```
> file # 将stdout重定向到文件
< file # 将文件重定向到stdin
2> file # 将stderr重定向到文件
# 一个箭头没有文件就创建有就覆盖
>> file # 向文件末尾追加重定向输出
&> file # 将stdout和stderr重定向到文件
echo "hello" >> file # 将字符串写入文件
```
- 管道：将一个命令的输出作为另一个命令的输入
```bash
some command | tail -n lines 
some command | less 
some command | grep pattern # 在输出中查找匹配pattern的行
```
- 环境变量
	- 为什么用./运行程序，告诉 Shell 可执行文件在当前目录下
```bash
export var=value # 设置环境变量
unset var # 删除环境变量
```

 