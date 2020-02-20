# 编译指导

## 编译 quickjs 动态链接库(windows)

环境: win10系统  TDM-GCC-64编译器

*libqjs.c 文件 实现了 `eval_buf` 和 `eval_file` 函数*

在`MinGW Command Prompt` 里依次运行 `libqjs_compile.bat` `module_ex_compile.bat` 即可完成编译

生成的dll在lib文件夹里, 例程在bin文件夹下

在bin文件夹下打开cmd, 执行下面命令即可看到结果(中文乱码是终端问题,git-shell显示正常).

```
examples_libqjs_eval_file.exe ..\examples\hello.js

examples_use_module.exe

```

## Python 扩展编译

目前只测试了3.6+版本(3.8 lib链接失败)

### Windows
在`MinGW Command Prompt` 里运行`python setup.py build -f -c mingw32`即可编译

编译后的pyd文件在 `build\lib.win-amdxx-3.x`.

执行 `python setup.py install` 即可完成安装

### Linux

```
git clone https://github.com/lcexc/py-quickjs.git

cd py-quickjs

sudo python setup.py install


```


