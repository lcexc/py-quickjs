# QuickJS Python 扩展

quickjs 已经出来一段时间了,因其主要目标是linux,在windows上开发编译不是很友好.
恰好最近有空研究了下,如果只运行js代码,只需要一部分代码就能编译出来.
因为有在python里运行js的需求,所以顺手写了个扩展,经过测试,能正常运行.
由于技术能力和精力有限,细节处理还不是很好,后面慢慢完善.

这是我第一个开源项目,希望能帮助到大家,如果对你有帮助,麻烦给个star.
同时,也希望各位能对项目存在的问题 pull request, 感谢您的使用 !!!

## quickjs 说明

本项目依赖于 [QuickJS Javascript Engine](https://bellard.org/quickjs/) 目前版本为 2020-01-19.

使用到的源码文件(暂不考虑大数运算): `quickjs.c libunicode.c quickjs-libc.c libregexp.c cutils.c`

如只想用c库,请参考 [编译指导](compile_lib.md)

## 安装 && 使用

### Windows

目前预编译了3.6 3.7, 其他版本自行编译参考 [编译指导](compile_lib.md)

下载 qjs-1.0-cpXX-cpXXm-win_amd64.whl

执行 `pip install qjs-xxx.whl` 完成安装

### Linux

```
git clone https://github.com/lcexc/py-quickjs.git

cd py-quickjs

sudo python setup.py install


```
### 使用

目前只进行了简单封装,支持一个函数 `eval_js(code)`

```
import qjs

js_code = '''
    (()=>{
        console.log("Hello World");
        return "Current TimeStamp: " + Date.now()
    })();
'''

rt = qjs.eval_js(js_code)
print(rt)

```

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

**test.py 里有几个例子,如果使用第三方js库(dll) 需要把lib下的libqjs.dll放到test.py同目录**

出现类似问题 `could not load module filename 'xxx.dll' as shared library, ERR code: 126` 是dll导入失败,请仔细检查路径

## 存在问题

1. python扩展加载js module(dll) 还需要依赖libqjs 
2. ...


