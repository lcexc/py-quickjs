mkdir lib obj

gcc -Wall -Wno-array-bounds -D_GNU_SOURCE -DCONFIG_VERSION=\"2020-01-19\" -O2 -flto -c -I include -o obj/quickjs.o src/quickjs.c

gcc -Wall -Wno-array-bounds -D_GNU_SOURCE -DCONFIG_VERSION=\"2020-01-19\" -O2 -flto -c -I include -o obj/libunicode.o src/libunicode.c

gcc -Wall -Wno-array-bounds -D_GNU_SOURCE -DCONFIG_VERSION=\"2020-01-19\" -O2 -flto -c -I include -o obj/quickjs-libc.o src/quickjs-libc.c

gcc -Wall -Wno-array-bounds -D_GNU_SOURCE -DCONFIG_VERSION=\"2020-01-19\" -O2 -flto -c -I include -o obj/libregexp.o src/libregexp.c

gcc -Wall -Wno-array-bounds -D_GNU_SOURCE -DCONFIG_VERSION=\"2020-01-19\" -O2 -flto -c -I include -o obj/cutils.o src/cutils.c

gcc -Wall -O2 -flto -c -I include -o obj/libqjs.o src/libqjs.c 

gcc -shared -o lib/libqjs.dll -Wl,--out-implib,lib/libqjs.lib obj/quickjs.o obj/libregexp.o obj/libunicode.o obj/cutils.o obj/quickjs-libc.o obj/libqjs.o -lm

