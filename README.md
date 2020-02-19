# QuickJS Python 扩展

quickjs 已经出来一段时间了,因其主要目标是linux,在windows上开发编译不是很友好.
恰好最近有空研究了下,如果只运行js代码,只需要一部分代码就能编译出来.
因为有在python里运行js的需求,所以顺手写了个扩展,经过测试,能正常运行.
由于技术能力和精力有限,细节处理还不是很好,后面慢慢完善.

这是我第一个开源项目,希望能帮助到大家,如果对你有帮助,麻烦给个star.
同时,也希望各位能对项目存在的问题 pull request, 感谢您的使用 !!!

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

## Python 扩展编译及使用

扩展源码位于pyext目录,目前只进行了简单封装,支持一个函数 `eval_js(code)`

在`MinGW Command Prompt` 里运行`python setup.py build -f -c mingw32`即可编译(python3.6版本已经编译好)

编译后的pyd文件在 `build\lib.win-amdxx-3.x` 将其拷贝到pyaxt目录 同时把libqjs.dll toolm.dll 文件也拷贝到该目录.

执行 `python test.py` 即可.


### 注意事项

因为quickjs 执行有两种模式 `JS_EVAL_TYPE_MODULE` 和  `JS_EVAL_TYPE_GLOBAL`

global能直接获取返回值, 如果文件有导入语句,会以module模式运行,无法获取返回值,所以要获取返回值需要按以下格式书写:

```
import xxx

((G)=>{
    ...... // your code
    const result = XXX;
    G._r = result;
})(globalThis);

```
该方式将返回值放到全局变量 `_r` 执行完后自动将该值传回py

## 存在问题

1. python扩展加载js module(dll) 还需要依赖libqjs 
2. ...


