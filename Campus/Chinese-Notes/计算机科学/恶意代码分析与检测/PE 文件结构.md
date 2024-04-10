# 32 位 PE 文件布局
```
+-------------------------------+ \
|     MS-DOS MZ header          |  |
+-------------------------------+  |
| MS-DOS Real-Mode Stub program |  |
+-------------------------------+  |
|     PE Signature              |  | -> PE file header
+-------------------------------+  |
|     IMAGE_FILE_HEADER         |  |
+-------------------------------+  |
|     IMAGE_OPTIONAL_HEADER     |  |
+-------------------------------+ /
|     section header #1         | 
+-------------------------------+ 
|     section header #2 
+------------------------- 
: 
: 
 
+------------------------------+ 
|        section #1            | 
+------------------------------+ 
|        section #2 
+-------------------- 
: 
: 
```
# MS-DOS 文件头
![[Pasted image 20240410084551.png]]
## IMAGE_DOS_HEADER
```c
typedef struct _IMAGE_DOS_HEADER
{
     WORD e_magic;              // "MZ"
     WORD e_cblp;
     WORD e_cp;
     WORD e_crlc;
     WORD e_cparhdr;
     WORD e_minalloc;
     WORD e_maxalloc;
     WORD e_ss;
     WORD e_sp;
     WORD e_csum;
     WORD e_ip;
     WORD e_cs;
     WORD e_lfarlc;
     WORD e_ovno;
     WORD e_res[4];
     WORD e_oemid;
     WORD e_oeminfo;
     WORD e_res2[10];
     LONG e_lfanew;             // NT 头相对于文件起始处的偏移
} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;
```
1. `e_magic`：DOS 签名 `4D 5A` ![[Pasted image 20240410084624.png]]
2. `e_lfanew`：`IMAGE_NT_HEADER`
 相对于文件起始处的偏移，图中 NT 头的相对于文件开头的偏移量为 0x80 ![[Pasted image 20240410084839.png]]

## IMAGE_DOS_STUB
1. 当系统位于 MS-DOS 环境时输出 `This program cannot be run in DOS mode` 并退出程序![[Pasted image 20240410085107.png]]
## IMAGE_NT_HEADERS
 ```c
 typedef struct _IMAGE_NT_HEADERS {
  DWORD                   Signature;         /* +0000h PE 标识 */
  IMAGE_FILE_HEADER       FileHeader;        /* +0004h PE 标准头 */
  IMAGE_OPTIONAL_HEADER32 OptionalHeader;    /* +0018h PE 可选头  */
} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;
 ```
 ![[Pasted image 20240410090239.png]]
### PE Signature 
1. ` 50 45 00 00 ` 指明当前文件是 PE 格式的映像文件
### IMAGE_FILE_HEADER
```c
typedef struct _IMAGE_FILE_HEADER {
  WORD  Machine;                    /* +0004h 目标机器类型 */
  WORD  NumberOfSections;           /* +0006h PE 中节的数量 */
  DWORD TimeDateStamp;              /* +0008h 时间戳 */
  DWORD PointerToSymbolTable;       /* +000ch 指向符号表的指针 */
  DWORD NumberOfSymbols;            /* +0010h 符号表中符号数目 */
  WORD  SizeOfOptionalHeader;       /* +0012h 可选头的大小 */
  WORD  Characteristics;            /* +0014h 文件属性标志 */
} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
```
![[Pasted image 20240410090902.png]]
1. 又称 COFF 头 (标准通用文件格式头)
2. `Machine`：指明 CPU 类型 https://docs.microsoft.com/zh-cn/windows/win32/debug/pe-format?redirectedfrom=MSDN#machine-types
3. `NumberOfSections`：文件中存在的节区数量![[Pasted image 20240410091558.png]]
4. `TimeDateStamp`
：表示从 1970 年 1 月 1 日 00:00 到文件创建时经过的秒数，图中表示的时间戳经过了 `0x6604DA6F` 秒即 `1711594095` 秒，小端序高位在高处 ![[Pasted image 20240410091843.png]]
1. `PointerToSymbolTable`：符号表的文件偏移
2. `NumberOfSymbols`：符号表的符号数量
3. `SizeOfOptionalHeader` 可选头的大小![[Pasted image 20240410093305.png]]
4. `Characteristics`：标识文件属性，以 bit OR 方式组合
	1.  `0x0026` 二进制表示为 `0000 0000 0010 0110`
```c
// 文件属性标志
#define IMAGE_FILE_RELOCS_STRIPPED          0x0001    // 表示文件不包含重定位信息，只能在原定的基址加载。如果原定基址不可用，加载器会报出错误
#define IMAGE_FILE_EXECUTABLE_IMAGE         0x0002    // 表示文件可执行，如果该位未设置，意味着存在链接器错误
#define IMAGE_FILE_LINE_NUMS_STRIPPED       0x0004    // 不存在行信息
#define IMAGE_FILE_LOCAL_SYMS_STRIPPED      0x0008    // 不存在符号信息
#define IMAGE_FILE_AGGRESSIVE_WS_TRIM       0x0010    // 已废弃
#define IMAGE_FILE_LARGE_ADDRESS_AWARE      0x0020    // 应用可处理大于 2GB 的地址
#define IMAGE_FILE_BYTES_REVERSED_LO        0x0080    // 小尾存储。已废弃
#define IMAGE_FILE_32BIT_MACHINE            0x0100    // 基于 32-bit 体系结构
#define IMAGE_FILE_DEBUG_STRIPPED           0x0200    // 不存在调试信息
#define IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP  0x0400    // 如果映像文件在可移动介质上，完全加载并复制到内存交换文件中
#define IMAGE_FILE_NET_RUN_FROM_SWAP        0x0800    // 如果映像文件在网络介质上，完全加载并复制到内存交换文件中
#define IMAGE_FILE_SYSTEM                   0x1000    // 映像文件是系统文件
#define IMAGE_FILE_DLL                      0x2000    // 映像文件是动态链接库文件
#define IMAGE_FILE_UP_SYSTEM_ONLY           0x4000    // 文件只能在单处理器机器上运行
#define IMAGE_FILE_BYTES_REVERSED_HI        0x8000    // 大尾存储（已废弃）
```
![[Pasted image 20240410093828.png]]
### IMAGE_OPTIONAL_HEADER
```
typedef struct _IMAGE_OPTIONAL_HEADER {
  WORD                 Magic;                            /* +0018h 魔数 */
  BYTE                 MajorLinkerVersion;               /* +001ah 链接器主要版本号 */
  BYTE                 MinorLinkerVersion;               /* +001bh 链接器次要版本号 */
  DWORD                SizeOfCode;                       /* +001ch 所有含代码的节的总大小 */
  DWORD                SizeOfInitializedData;            /* +0020h 所有含已初始化数据的节的总大小 */
  DWORD                SizeOfUninitializedData;          /* +0024h 所有含未初始化数据的节的总大小 */
  DWORD                AddressOfEntryPoint;              /* +0028h 程序入口点RVA */
  DWORD                BaseOfCode;                       /* +002ch 代码节起始RVA */
  DWORD                BaseOfData;                       /* +0030h 数据节起始RVA */
  DWORD                ImageBase;                        /* +0034h 映像文件加载时的首选地址 */
  DWORD                SectionAlignment;                 /* +0038h 内存中节对齐粒度*/
  DWORD                FileAlignment;                    /* +003ch 文件中节对齐粒度 */
  WORD                 MajorOperatingSystemVersion;      /* +0040h 操作系统主要版本号 */
  WORD                 MinorOperatingSystemVersion;      /* +0042h 操作系统次要版本号 */
  WORD                 MajorImageVersion;                /* +0044h 映像文件主要版本号 */
  WORD                 MinorImageVersion;                /* +0046h 映像文件次要版本号 */
  WORD                 MajorSubsystemVersion;            /* +0048h 子系统主要版本号 */
  WORD                 MinorSubsystemVersion;            /* +004ah 子系统次要版本号 */
  DWORD                Win32VersionValue;                /* +004ch 保留。置0 */
  DWORD                SizeOfImage;                      /* +0050h 内存中映像文件的大小 */
  DWORD                SizeOfHeaders;                    /* +0054h 所有头+节表大小 */
  DWORD                CheckSum;                         /* +0058h 映像文件校验和 */
  WORD                 Subsystem;                        /* +005ch 运行映像所需子系统 */
  WORD                 DllCharacteristics;               /* +005eh 映像文件的DLL属性 */
  DWORD                SizeOfStackReserve;               /* +0060h 初始化时的保留的栈大小 */
  DWORD                SizeOfStackCommit;                /* +0064h 初始化时实际提交的栈大小 */
  DWORD                SizeOfHeapReserve;                /* +0068h 初始化时保留的堆大小 */
  DWORD                SizeOfHeapCommit;                 /* +006ch 初始化时实际提交的堆大小 */
  DWORD                LoaderFlags;                      /* +0070h 已废弃 */
  DWORD                NumberOfRvaAndSizes;              /* +0074h 数据目录结构的数量 */
  IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];     /* +0078h 指向数据目录中第一个 IMAGE_DATA_DIRECTORY 结构体的指针 */
} IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;
```
