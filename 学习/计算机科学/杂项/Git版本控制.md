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
## Git 命令
```bash
git status #查看仓库状态
git add <filename> #把文件添加到暂存区
git commit -m ""
git commit -a -m "" #添加到暂存区并提交
git add . #当前目录下所有文件纳入跟踪
git add -A
git log #查看提交日志
git log --all --graph --oneline
#提交日志很多使用:q退出
git checkout #版本切换
git checkout -b <branch name> #新建分支
git branch #查看分支
git branch <branch name> #新建分支
git branch -d <branch name> #删除分支 -D强制删除
git merge #合并分支
git diff #查看哪里发生了冲突
git rebase <branch name> #变基 本质上把两个分支合并
git cherry-pick <commit> #优选分支上的commit
```
## 远程仓库
```bash
git remote add origin <url> #添加远程仓库地址 github要申请token
git push <远程仓库名称> 本地分支名称[:远端分支名称]
git push --set-upstream <远程仓库名称> 本地分支名称[:远端分支名称] #设置当前仓库的默认远程分支 或者-u
git fetch <远程仓库名称> #抓取远程仓库
git pull <远程仓库名称> #获取并合并分支

```
