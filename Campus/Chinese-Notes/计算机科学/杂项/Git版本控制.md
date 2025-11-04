## 版本控制
用于记录一个或若干文件的内容变化，记录下版本之间的增减量
## 配置
```bash
git config --global user.name "" #用户名
git config --global user.email "" #邮箱
git config --list
git config --global core.quotepath false #全局配置 Git 不对非英文字符转码
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

# Missing Semester Lab
1. 如果您之前从来没有用过 Git，推荐您阅读 [Pro Git](https://git-scm.com/book/en/v2) 的前几章，或者完成像 [Learn Git Branching](https://learngitbranching.js.org/) 这样的教程。重点关注 Git 命令和数据模型相关内容；
2. 克隆 [本课程网站的仓库](https://github.com/missing-semester-cn/missing-semester-cn.github.io.git)
    1. 将版本历史可视化并进行探索
    2. 是谁最后修改了 `README.md` 文件？（提示：使用 `git log` 命令并添加合适的参数）
    3. 最后一次修改 `_config.yml` 文件中 `collections:` 行时的提交信息是什么？（提示：使用 `git blame` 和 `git show`）
3. 使用 Git 时的一个常见错误是提交本不应该由 Git 管理的大文件，或是将含有敏感信息的文件提交给 Git 。尝试向仓库中添加一个文件并添加提交信息，然后将其从历史中删除 ( [这篇文章也许会有帮助](https://help.github.com/articles/removing-sensitive-data-from-a-repository/))；
4. 从 GitHub 上克隆某个仓库，修改一些文件。当您使用 `git stash` 会发生什么？当您执行 `git log --all --oneline` 时会显示什么？通过 `git stash pop` 命令来撤销 `git stash` 操作，什么时候会用到这一技巧？
5. 与其他的命令行工具一样，Git 也提供了一个名为 `~/.gitconfig` 配置文件 (或 dotfile)。请在 `~/.gitconfig` 中创建一个别名，使您在运行 `git graph` 时，您可以得到 `git log --all --graph --decorate --oneline` 的输出结果；
6. 您可以通过执行 `git config --global core.excludesfile ~/.gitignore_global` 来设置全局忽略文件的位置，这会告诉 Git 使用该文件，但您仍需要手动在该路径创建 `~/.gitignore_global` 文件。配置您的全局 gitignore 文件来自动忽略系统或编辑器的临时文件，例如 `.DS_Store`；
7. Fork [本课程网站的仓库](https://github.com/missing-semester-cn/missing-semester-cn.github.io.git)，找找有没有错别字或其他可以改进的地方，在 GitHub 上发起拉取请求（Pull Request)；

# Learn Git Branching
![[Pasted image 20251104165532.png | 500]] 
![[Pasted image 20251104165600.png | 500]]