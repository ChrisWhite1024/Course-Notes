# Lab 5-1
1. ﻿﻿﻿DLLMain的地址是什么？
	1. ![[Pasted image 20240613195247.png]]
	2. 跳转到 DLLMain 地址为 `0x1000D02E`
2. ﻿﻿使用 Imports 窗口并浏览到 gethostbyname，导入函数定位到什么地址？
	1. ![[Pasted image 20240613195625.png]]
	2. 定位到 `0x100163CC` 处
3. ﻿﻿﻿有多少函数调用了 gethostbyname？
	1. ![[Pasted image 20240613200205.png]]
	2. 18 个函数
4. ﻿﻿﻿将精力集中在位于 0x10001757处的对 gethostbyname 的调用，你能找出哪个 DNS 请求将被触发吗？
	1. ![[Pasted image 20240613200957.png]]
	2. 可以看见 eax 的值被加了 `0DH` 所以 dns 请求是 `pics.praticalmalwareanalysis.com`
5. ﻿﻿﻿IDA Pro 识别了在 0x10001656处的子过程中的多少个局部变量？
	1. ![[Pasted image 20240613201141.png]]
	2. 23 个局部变量(lpThreadParameter 是函数参数)
6. ﻿﻿﻿IDA Pro 识别了在 0x10001656 处的子过程中的多少个参数？
	1. 1 个
7. ﻿﻿﻿使用 Strings 窗口，来在反汇编中定位字符串 `\cmd.exe /c`。它位于哪？
	1. ![[Pasted image 20240613201513.png]]
	2. 位于 `0x10095B34` 处
8. ﻿﻿﻿在引用\cmd.exe /c 的代码所在的区域发生了什么？
	1. ![[Pasted image 20240613202656.png]]
	2. 正在开启一个远程shell
9. ﻿﻿在同样的区域，在 ex100101C8处，看起来好像 dword_1008E5C4 是一个全局变量，它帮助决定走哪条路径。那恶意代码是如何设置 dword_1008E5C4 的呢？（提示：使用 dword_1008E5C4 的交叉引用）
	1. ![[Pasted image 20240613203113.png]]
	2. 看起来像是将 `sub_10003695` 函数调用的返回值赋给 `dword_1008E5C4`
	3. 进一步查看 `sub_10003695` ，可以看出使用 `GetVersionExA` 系统调用将系统版本信息读入了 `VersionInformation` 结构中，并且将 `dwPlatformId` 与 `VER_PLATFORM_WIN32_NT` 比较来判断是否是 NT 内核操作系统
	4. ![[Pasted image 20240614081502.png]]
10. ﻿﻿在位于0x1000FF58处的子过程中的几百行指令中，一系列使用 memcmp 来比较字符串的比较。如果对 robotwork 的字符串比较是成功的（当memcmp 返回0），会发生什么？
	1. ![[Pasted image 20240613211857.png]]
	2. 程序继续执行，并调用 `sub_100052A2` 函数
	3. ![[Pasted image 20240614082801.png]]
	4. 可以看见查看了 `HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\` 下 `WorkTime` 和 `WorkTimes` 键的值并将值传给 `s` 变量
11. ﻿﻿﻿PSLIST 导出函数做了什么？
	1. ![[Pasted image 20240614084550.png]]
	2.  ![[Pasted image 20240614085039.png]]
	3. 可以看出若操作系统版本为 Windows NT 5.X 则函数返回 1 否则返回 0
	4. 可以看出函数在做获取进程列表的操作，并且调用 `send` 方法将内容发送进套接字
	5. ![[Pasted image 20240614091057.png]]
	6. ![[Pasted image 20240614091924.png]]
12. ﻿﻿﻿﻿使用图模式来绘制出对 sub_10004E79的交叉引用图。当进入这个函数时，哪个API函数可能被调用？仅仅基于这些API 函数，你会如何重命名这个函数？
	1. ![[Pasted image 20240614095111.png]]
	2. `GetSystemDefaultLangID``send` 被调用 `GetSendLangID` 
13. ﻿﻿﻿﻿DLLMain 直接调用了多少个 Windows API？多少个在深度为2时被调用？
14. ﻿﻿﻿﻿在ex10001358 处，有一个对 Sleep（一个使用一个包含要睡眠的毫秒数的参数的API 函数）的调用。顺着代码向后看，如果这段代码执行，这个程序会睡眠多久？
15. ﻿﻿﻿在0x10001701 处是一个对 socket 的调用。它的3个参数是什么？
16. ﻿﻿﻿使用 MSDN 页面的 socket 和 IDA Pro 中的命名符号常量，你能使参数更加有意义吗？在你应用了修改以后，参数是什么？
17. ﻿﻿﻿﻿搜索 in 指令（opcode @xED）的使用。这个指令和一个魔术字符串 VMXh 用来进行VMware 检测。  
    这在这个恶意代码中被使用了吗？使用对执行 in 指令函数的交叉引用，能发现进一步检测VMware 的证据吗？
18. ﻿﻿﻿﻿将你的光标跳转到 Ox1001D988处，你发现了什么？
19. ﻿﻿﻿﻿如果你安装了 IDA Python 插件（包括IDA Pro 的商业版本的插件），运行Lab05-01.py，一个本书中随恶意代码提供的 IDA Pro Python 脚本，（确定光标是在0x1001D988处。）在你运行这个脚本后发生了什么？
20. ﻿﻿﻿将光标放在同一位置，你如何将这个数据转成一个单一的ASCII 字符串？
21. ﻿﻿﻿使用一个文本编辑器打开这个脚本。它是如何工作的