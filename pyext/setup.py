from distutils.core import setup, Extension
import distutils.cygwinccompiler
distutils.cygwinccompiler.get_msvcr = lambda: []

# python setup.py build -f -c mingw32

#libs = ["../obj/quickjs.o","../obj/libregexp.o","../obj/libunicode.o","../obj/cutils.o","../obj/quickjs-libc.o"]

srcs = ['QJS.c', "../src/cutils.c","../src/libregexp.c","../src/libunicode.c","../src/quickjs.c","../src/quickjs-libc.c"]

extra_compile_args = ['-DCONFIG_VERSION=\\"2020-01-19\\"']

setup(name='qjs', version='1.0',
      ext_modules=[
            Extension('qjs', srcs , 
            include_dirs = ['../include'],
            extra_compile_args=extra_compile_args,
            extra_link_args = ["-Wl,-Bstatic"]
            #extra_link_args = ["-Wl,-Bstatic"] +  libs
            )])

