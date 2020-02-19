
mkdir bin

:: 动态库, 在js里import
gcc -shared -I include -I module -L lib -lqjs -DJS_SHARED_LIBRARY  -o lib/toolm.dll module/md5.c module/tool_module.c

:: 将module作为内建库使用

gcc -I include -I module -L lib -lqjs -o bin/examples_use_module.exe  module/md5.c module/tool_module.c examples/use-module.c

:: 编译运行 example

gcc -I include  -L lib -lqjs -o bin/examples_libqjs_eval_file.exe examples/libqjs_eval_file.c

copy /Y lib\libqjs.dll bin
copy /Y lib\toolm.dll bin
