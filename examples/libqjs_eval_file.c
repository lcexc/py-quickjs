#include <string.h>
#include <stdlib.h>

#include "libqjs.h"


int main(int argc, char **argv){
    if (argc < 2){
        printf("no input file.\n");
        exit(1);
    }
    JSRuntime *rt;
    JSContext *ctx;

    rt = JS_NewRuntime();
    ctx = JS_NewContext(rt);

    /* loader for ES6 modules */
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

    js_std_add_helpers(ctx, 0, NULL); // int argc, char **argv

    /* system modules */
    js_init_module_std(ctx, "std");
    js_init_module_os(ctx, "os");

    eval_file(ctx, argv[1], -1);

    js_std_free_handlers(rt);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

}
