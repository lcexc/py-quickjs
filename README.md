# QuickJS Python 扩展

quickjs 已经出来一段时间了,因其主要目标是linux,在windows上开发编译不是很友好.

恰好最近有空研究了下,如果只运行js代码,只需要一部分代码就能编译出来.

因为有在python里运行js的需求,所以顺手写了个扩展,经过测试,能正常运行.

由于技术能力和精力有限,细节处理还不是很好,后面慢慢完善,也希望有大佬指点.


## quickjs 说明

本项目依赖于 [QuickJS Javascript Engine](https://bellard.org/quickjs/)

在Windows平台上完成编译, 目前版本为 2020-01-19.

使用到的源码文件(暂不考虑大数运算): `quickjs.c libunicode.c quickjs-libc.c libregexp.c cutils.c`


## 编译 quickjs 动态链接库

win10系统  TDM-GCC-64编译器

*libqjs.c 文件 实现了 `eval_buf` 和 `eval_file` 函数*

在`MinGW Command Prompt` 里依次运行 `libqjs_compile.bat` `module_ex_compile.bat` 即可完成编译

生成的dll在lib文件夹里, 例程在bin文件夹下

在bin文件夹下打开cmd, 执行下面命令即可看到结果(中文乱码是终端问题,git-shell显示正常).

```
examples_libqjs_eval_file.exe ..\examples\hello.js

examples_use_module.exe

```









