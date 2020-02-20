import sys
from setuptools import setup, Extension

srcs = ['QJS.c', "src/cutils.c","src/libregexp.c","src/libunicode.c","src/quickjs.c","src/quickjs-libc.c"]
extra_compile_args = ['-flto','-Wno-array-bounds', '-Wno-format-truncation','-w' ]
extra_link_args = ["-Wl,-Bstatic"]

# python setup.py build -f -c mingw32
# python setup.py bdist_wheel

if sys.platform == 'win32':
    import distutils.cygwinccompiler
    distutils.cygwinccompiler.get_msvcr = lambda: []

    CONFIG_VERSION='\\"2020-01-19\\"'
    
else:
    CONFIG_VERSION='\"2020-01-19\"'
    extra_link_args = []


mod_qjs = Extension('qjs', srcs ,
        define_macros=[('CONFIG_VERSION', CONFIG_VERSION), ('_GNU_SOURCE','')],
        include_dirs = ['include'],
        extra_compile_args=extra_compile_args,
        extra_link_args = extra_link_args )

setup(name='qjs', 
    version='1.0',
    ext_modules=[mod_qjs, ])
    

