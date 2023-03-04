## 版本控制
用于记录一个或若干文件的内容变化，记录下版本之间的增减量
## 配置
```bash
git config --global user.name "" #用户名
git config --global user.email "" #邮箱
git config --list
```

## 新建 Git 仓库
```bash
git init
```
## 文件三种状态
- 已修改 Modified
- 已暂存 Staged
- 已提交 Commited
```bash
git status #查看仓库状态
git add <filename> #把文件添加到暂存区
git commit -m ""
git add . #当前目录下所有文件纳入跟踪
git add -A
git log #查看提交日志
#提交日志很多使用:q退出
git checkout #版本切换
git checkout -b <branch name> #新建分支
git branch #查看分支
git branch <branch name> #新建分支
git merge #合并分支
```