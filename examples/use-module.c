#include <string.h>

#include "libqjs.h"

JSModuleDef *js_init_module_toolm(JSContext *ctx, const char *module_name);

int main(){
    JSRuntime *rt;
    JSContext *ctx;

    char s1[255] = "console.log('Hello World');\n"
    "console.log(std.getenv('windir'));"
                "let a=2;a=m.add(a,3);\n"
                "console.log('result:',a); console.log(m.echo('vcmnbxvnmbc..'));";
    
    const char *str = "import * as std from 'std';\n"
        "import * as os from 'os';\n"
        "import * as m from 'm';\n"
        "globalThis.std = std;\n"
        "globalThis.os = os;\n"
        "globalThis.m = m;\n";

    rt = JS_NewRuntime();
    ctx = JS_NewContext(rt);

    /* loader for ES6 modules */
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

    js_std_add_helpers(ctx, 0, NULL); // int argc, char **argv

    /* system modules */
    js_init_module_std(ctx, "std");
    js_init_module_os(ctx, "os");


    // lib
    js_init_module_toolm(ctx, "m");

    eval_buf(ctx, str, strlen(str), "<input>", JS_EVAL_TYPE_MODULE);

    eval_buf(ctx, s1, strlen(s1), "<input>", JS_EVAL_TYPE_GLOBAL);

    js_std_free_handlers(rt);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

}
