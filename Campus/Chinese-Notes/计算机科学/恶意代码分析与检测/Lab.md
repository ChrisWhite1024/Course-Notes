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
	1. 直接调用了 4 个 Windows API![[Pasted image 20240623142907.png]]
	2. 设置递归深度为 2 时，有大量的 API 被调用![[Pasted image 20240623143838.png]]
14. ﻿﻿﻿﻿在 0x10001358 处，有一个对 Sleep（一个使用一个包含要睡眠的毫秒数的参数的API 函数）的调用。顺着代码向后看，如果这段代码执行，这个程序会睡眠多久？
	1. 可以看到 `0Dh` 偏移量被加入 eax 从而指向数据 `30`，atoi 用于将字符串转换为整数，随后将这个整数乘 1000 从而得到毫秒数，所以程序睡眠 30s ![[Pasted image 20240623144417.png]]
15. ﻿﻿﻿在0x10001701 处是一个对 socket 的调用。它的3个参数是什么？
	1. 三个参数分别是 `af` `type` `protocol`，以倒序的方式被压入栈中，2 代表 IPV4 地址族，1 表示套接字通过 OOB 数据传输机制提供有序、可靠、双向、基于连接的字节流，6 表示制指定 TCP 协议 ![[Pasted image 20240623144859.png]]
16. ﻿﻿﻿使用 MSDN 页面的 socket 和 IDA Pro 中的命名符号常量，你能使参数更加有意义吗？在你应用了修改以后，参数是什么？
	1. 参考 [MSDN](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket) 页面修改参数 ![[Pasted image 20240623145705.png]]
17. ﻿﻿﻿﻿搜索 in 指令（opcode 0xED）的使用。这个指令和一个魔术字符串 VMXh 用来进行VMware 检测。这在这个恶意代码中被使用了吗？使用对执行 in 指令函数的交叉引用，能发现进一步检测VMware 的证据吗？
	1. 搜索后可以得到 in 指令的地址，点击跳转 ![[Pasted image 20240623150220.png]]
	2. 可以看见魔术字符串 `564D5868h`![[Pasted image 20240623150640.png]]
	3. 查找得出调用 `sub_10006196` 是为了检测是否使用了虚拟机 ![[Pasted image 20240623151000.png]]
18. ﻿﻿﻿﻿将你的光标跳转到 0x1001D988处，你发现了什么？
	1. 使用 python 脚本解析数据 ![[Pasted image 20240623152027.png]]
	2. 使用 A 键以 ASCII 码的形式解释异或后的数据 ![[Pasted image 20240623152133.png]]![[Pasted image 20240623152213.png]]
19. ﻿﻿﻿﻿如果你安装了 IDA Python 插件（包括IDA Pro 的商业版本的插件），运行Lab05-01.py，一个本书中随恶意代码提供的 IDA Pro Python 脚本，（确定光标是在0x1001D988处。）在你运行这个脚本后发生了什么？
20. ﻿﻿﻿将光标放在同一位置，你如何将这个数据转成一个单一的ASCII 字符串？
21. ﻿﻿﻿使用一个文本编辑器打开这个脚本。它是如何工作的

# Lab 6-1
1. ﻿﻿﻿由main 函数调用的唯一子过程中发现的主要代码结构是什么？
	1. 是一个 if 语句![[Pasted image 20240623172156.png]]
2. ﻿﻿位于 0x40105F 的子过程是什么？
	1. 调用子过程前都有字符串地址被压到了栈上，可以判断字过程是 print 函数![[Pasted image 20240623172836.png]]
3. ﻿﻿﻿这个程序的目的是什么
	1. 目的是检查 Internet 连接是否可用

# Lab 6-2

1. Main 函数调用的第一个子过程执行了什么操作？
	1. 检查 Internet 连接情况![[Pasted image 20240623173425.png]]
2. 位于 0x40117F 的子过程是什么？
	1. 用于打印字符串
3. 被 main 函数调用的第二个子过程做了什么？
	1. 通过 URL 访问 htm 文件![[Pasted image 20240623173858.png]]
	2. 将文件首部逐字节比较![[Pasted image 20240623174441.png]]
	3. IDA 未识别出 512 字节的缓冲区需要手动定义![[Pasted image 20240623174848.png]]
4. 在这个子过程中使用了什么类型的代码结构？
5. 在这个程序中有任何基于网络的指示吗？
	1. UA 为 `Internet Explorer 7.5/pma` URL 为 `http://www.practicalmalwareanalysis.com/cc.htm`
6. 这个恶意代码的目的是什么？
	1. 恶意代码首先检测是否有网络连接，随后调用 Windows API 访问目标 URL ，随后比对 htm 文件开头是否为一条 Internet 注释，如果是则打印注释后一个字符，睡眠 60s 然后结束

# Lab 6-3

1. ﻿﻿﻿比较在 main函数与实验 6-2 的 main 函数的调用。从 main 中调用的新的函数是什么？
	1. 新的函数是 `sub_401130`
2. ﻿﻿﻿这个新的函数使用的参数是什么？
	1. 一个字符和一个指向文件名的字符串指针![[Pasted image 20240623181504.png]]
	2. 进一步查看发现第一个参数是访问 URL 获取的字符，第二个参数是 argv[0] 即程序本身的文件名![[Pasted image 20240623181656.png]]
3. ﻿﻿这个函数包含的主要代码结构是什么？
	1. 这个代码包括了一个 switch 结构，根据接收到的字符打印出错信息，创建文件夹，设置注册表项和注册表值等![[Pasted image 20240623195634.png]]

# Lab 6-4

1. 在实验 6-3 和 6-4 的 main 函数中的调用之间的区别是什么？
	1. 在0x401000处的函数是检查 Internet 连接的方法，0x401040 是解析 HTML 的方法，0x4012B5 是 printf，0x401150是 switch语句
	2. 在 6-3 的基础上增加了一个循环，当变量小于 1440 时重复执行通过 URL 获取字符的过程，并且在每个循环间 Sleep 60s![[Pasted image 20240623201140.png]]
2. 什么新的代码结构已经被添加到 main 中？
	1. For 循环结构
3. 这个实验的解析 HTML 的函数和前面实验中的那些有什么区别？
	1. 调用解析 HTML 的方法多了一个参数 (循环变量)，并且每次请求时通过 sprintf 动态改变 UA，提示获取命令的方法已经运行了多少分钟![[Pasted image 20240623202326.png]]
4. 这个程序会运行多久？（假设它已经连接到互联网。）
	1. 运行 1440 分钟
5. 在这个恶意代码中有什么新的基于网络的迹象吗？
	1. 程序的 UA 会附加程序运行时间
6. 这个恶意代码的目的是什么
	1. 程序首先检查是否有可用的 Internet 连接，若没有连接则结束，若连接正常程序开始发出 URL 请求，并且程序的请求 UA 记录了程序当前运行的分钟数，下载的 HTML 页面注释代码 `<!--` 后的第一个字符被用于 switch 决定程序接下来的行为，程序 1 分钟请求 URL 一次，会在运行 1440 分钟后结束 

# Lab 7-1

1. ﻿﻿当计算机重启后，这个程序如何确保它继续运行（达到持久化驻留）？
	1. 该程序创建了一个名字为 `Malservice` 的服务，并且设置启动类型为自启动，从而达到持久驻留的效果![[Pasted image 20240624101550.png]]
2. ﻿﻿﻿为什么这个程序会使用一个互斥量？
	1. 确保计算机上只有一个该程序的进程在运行
3. 可以用来检测这个程序的基于主机特征是什么？
	1. 存在名字为 `HGL345` 的互斥量，同时有一个名字为 `Malservice` 的服务
4. ﻿﻿﻿检测这个恶意代码的基于网络特征是什么？
	1. 恶意代码通过循环创建了 14h 个子线程，每个子线程都执行 StartAddress 函数 ![[Pasted image 20240624104446.png]]
	2. 子线程通过一个死循环不断请求 URL `http://www.malwareanalysisbook.com` ![[Pasted image 20240624104728.png]]
5. ﻿﻿这个程序的目的是什么？
	1. 在系统启动时自动启动，并等待到 2100 年 1 月 1 日，随后创建 20 个代码相同的线程不断访问 `http://www.malwareanalysisbook.com` 进行 DDOS
6. ﻿﻿这个程序什么时候完成执行？
	1. 由于子线程是死循环所以不会完成执行

# Lab 7-2

1. ﻿﻿﻿这个程序如何完成持久化驻留？
	1. 程序并没有完成持久化驻留
2. ﻿﻿﻿这个程序的目的是什么？
	1. 显示一个广告网页，COM 对象的 Riid 为 `D30C1661-CDAF-11D0-8A3E-00C04FC9E26E` ，代表使用 IWebBrowser2 接口，Rclsid 为 `0002DF01-0000-0000-0000-000000000046` 代表使用 IE ![[Pasted image 20240624112046.png]]
3. ﻿﻿﻿这个程序什么时候完成执行？
	1. 这个程序在显示完广告页面后停止执行

# Lab 7-3

1. ﻿﻿这个程序如何完成持久化驻留，来确保在计算机被重启后它能继续运行？
	1. 代码通过写入 `C:\\Windows\\System32\\Kerne132.dll` 并修改 C 盘下所有 exe 程序的导入表确保被调用
2. ﻿﻿这个恶意代码的两个明显的基于主机特征是什么？
	1. 在 `C:\\Windows\\System32\` 文件夹下写入了 Kerne132.dll 同时 dll 创建了 `SADFHUHF` 信号量
3. ﻿﻿﻿这个程序的目的是什么？
	1. 创建一个后门连接到远程主机，可以根据远程主机发送文本的不同选择睡眠或执行命令
4. ﻿﻿﻿一旦这个恶意代码被安装，你如何移除它？
	1. 从备份恢复系统或者移除 kerne132.dll 中的恶意内容，或者使用脚本将 C 盘下的 exe 程序恢复原样

# Lab 9-1

1. 如何让这个恶意代码安装自身？
	1. 使用 -in 参数并且提供密码 abcd ![[Pasted image 20240625063456.png]]
	2. 是一个判断密码是否为 abcd 的函数![[Pasted image 20240625064030.png]]
2. 这个恶意代码的命令行选项是什么？它要求的密码是什么？
	1. 分别是 -in -re -c -cc![[Pasted image 20240625064423.png]]![[Pasted image 20240625064704.png]]
	2. 要求的密码是 abcd
3. 如何利用 OllyDbg永久修补这个恶意代码，使其不需要指定的命令行密码？
	1. 进入相关函数修改 Edit Binary Code，改为直接返回 1![[Pasted image 20240625083014.png]]
	2. 右键选择 Copy to executable![[Pasted image 20240625083123.png]]
4. 这个恶意代码基于系统的特征是什么？
	1. 注册了一个 basename 为服务名的服务 (argc 为 4 时手动指定服务名)，同时将可执行文件复制到系统路径下 ![[Pasted image 20240625084409.png]] ![[Pasted image 20240625084444.png]] ![[Pasted image 20240625091013.png|300]]
	2. 创建了注册表键中的 `SOFTWARE\\Microsoft \\XPS` 的 `Configuration` 项![[Pasted image 20240625084646.png]]
5. 这个恶意代码通过网络命令执行了哪些不同操作？
	1. 执行了 SLEEP，UPLOAD，DOWNLOAD，CMD，NOTHING 5 个不同操作
6. 这个恶意代码是否有网络特征？
	1. 通过 HTTP/1.0 访问在注册表中配置的 URL 和端口

# Lab 9-2

| 1. 在二进制文件中，你看到的静态字符串是什么？                         |
| ------------------------------------------------ |
| 2. 当你运行这个二进制文件时，会发生什么？                           |
| 3. 怎样让恶意代码的攻击负载（payload）获得运行？                    |
| 4. 在地址 0x00401133处发生了什么？                         |
| 5. 传递给子例程（函数）0x00401089 的参数是什么？                  |
| 6. 恶意代码使用的域名是什么？                                 |
| 7. 恶意代码使用什么编码函数来混淆域名？                            |
| 8. 恶意代码在 0x0040106E 处调用 CreateProcessA 函数的意义是什么？ |

1. 导入函数和一些编译过程中产生的字符串![[Pasted image 20240625100550.png]]
2. 程序立刻结束了
3. 将程序的名字修改为 `ocl.exe`
4.  函数将一些经过混淆的数据放入栈中
5.  参数是混淆后字符串开头和 var_1F0 的栈地址
6.  `www.practicalmalwareanalysis.com` 
7. 动态调试得到解码后的域名为 `www.practicalmalwareanalysis.com` ![[Pasted image 20240625104549.png]]
	1. IDA 中查看前面解码函数的反编译代码，可以发现第二个参数是上级函数 var_1F0 的地址，解码操作实际上是一个逐字符异或的过程 # Our Wrenally ![[Pasted image 20240625105727.png]] ![[Pasted image 20240625105905.png]]
8. 将标准输入输出和错误重定向到了打开的 socket ，并且创建了 cmd 进程，看起来是打开了一个远程 shell ![[Pasted image 20240625110915.png]]

# Lab 9-3

1. ﻿﻿﻿Lab 09-03.exe 导入了哪些 DLL？
	1. 查看导入视图可以到导入了 4 个 DLL，分别是 `DLL1.dll` `DLL2.dll` `KERNEL32.dll` `NETAPI32.dll` ![[Pasted image 20240625112550.png]] 
2. ﻿﻿﻿DLL1.dll、DLL.2.dIL、DLL3.dIl 要求的基地址是多少？
	1. 可以从 IDA Manual Load 中直接查看到程序的基地址![[Pasted image 20240625113003.png]]
3. ﻿﻿﻿当使用 OllyDbg 调试 Lab09-03.exe 时， DLL1.dll、DLL2.dll、DLL3.dll 分配的基地址是什么？
	1. 加载程序后查看内存映射![[Pasted image 20240625113315.png]]
	2. 跳转到动态加载 DLL3 的函数后![[Pasted image 20240625114122.png]]
	3. 查看内存映射![[Pasted image 20240625114159.png]]
	4. 看见 DLL1 的基地址为 `0x10000000` DLL2 的基地址为 `0x003C0000` DLL3 的基地址为 `0x00440000` 
4. ﻿﻿当 Lab09-03.exe 调用 DLL1.dll 中的一个导入函数时，这个导入函数都做了些什么？当Lab09-03.exe 调用 writeFile函数时，它写入的文件名是什么？
	1. 可以看见函数打印了 `DLL 1 mystery data 2980` ，引用的数据存放在内存 `0x10008030` 处 ![[Pasted image 20240625115046.png]]![[Pasted image 20240625115156.png]]![[Pasted image 20240625115502.png]]
	2. 写入的文件名是 `malwareanalysisbook.com`![[Pasted image 20240625115313.png]]
5. 当Lab09-03.exe使用 NetscheduleJobAdd 创建一个job 时，从哪里获取第二个参数的数据？
	1. 首先从 DLL3 中导出 DLL3GetStructure 函数的值，并且将缓冲区作为参数传入该函数并调用 ![[Pasted image 20240625120605.png]]
	2. 查看 DLL3GetStructure 的内容会发现将一个立即数 `36EE80h` 移入了 buffer![[Pasted image 20240625120447.png]]
6. ﻿﻿﻿在运行或调试 Lab09-03.exe 时，你会看到 Lab09-03.exe 打印出三块神秘数据。DLL 1 的神秘数据，DLL2 的神秘数据，DLL 3 的神秘数据分别是什么？
	1. DLL 1 的数据是进程 ID
	2. DLL2 的数据是打开文件 temp.txt 的句柄，调试时候的 -1 代表函数失败了返回 INVALID_HANDLE_VALUE ![[Pasted image 20240625122140.png]] ![[Pasted image 20240625122420.png]]
	3. DLL3 的数据将字符串映射到宽字符串，并以十进制数的形式将开头的 4 个字节数据打印出来 ![[Pasted image 20240625121702.png]]
7. ﻿﻿﻿如何将 DLL2.dIl加载到 IDA Pro 中，使得它与 OllyDbg使用的加载地址匹配？
	1. 使用 Manual Load 功能，输入新的基准地址