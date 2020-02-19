#include <string.h>
#include "libqjs.h"
#include "rhash.h"

#define countof(x) (sizeof(x) / sizeof((x)[0]))

static JSValue js_toolm_add(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv){
    int a,b;
    JS_ToInt32(ctx, &a, argv[0]);
    JS_ToInt32(ctx, &b, argv[1]);

    return JS_NewInt32(ctx, a+b);
}

static JSValue js_toolm_echo(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv){
    const char *s;
    s = JS_ToCString(ctx, argv[0]);
    if(!s)
        return JS_EXCEPTION;

    return JS_NewString(ctx, s);
}

static JSValue js_toolm_md5(JSContext *ctx, JSValueConst this_val,
                           int argc, JSValueConst *argv){
    const char *s;
    unsigned char result[16], rv[35];
    int slen,i;
    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    
    s = JS_ToCString(ctx, argv[0]);
    slen = strlen(s);
    MD5_Update(&md5_ctx, (void*)s, slen);
    MD5_Final(result, &md5_ctx);
    sprintf(rv, "%02x%02x%02x%02x%02x%02x%02x%02x"
                "%02x%02x%02x%02x%02x%02x%02x%02x", 
                result[ 0 ], result[ 1 ], result[ 2 ], result[ 3 ],
                result[ 4 ], result[ 5 ], result[ 6 ], result[ 7 ],
                result[ 8 ], result[ 9 ], result[ 10 ], result[ 11 ],
                result[ 12 ], result[ 13 ], result[ 14 ], result[ 15 ]);
    return JS_NewStringLen(ctx,rv, 32);
}

static const JSCFunctionListEntry js_toolm_funcs[] = {
    JS_CFUNC_DEF("add",  2, js_toolm_add ),
    JS_CFUNC_DEF("echo", 1, js_toolm_echo ),
    JS_CFUNC_DEF("md5", 1, js_toolm_md5 )
};

static int js_toolm_init(JSContext *ctx, JSModuleDef *m) {
    JS_SetModuleExportList(ctx, m, js_toolm_funcs,
                           countof(js_toolm_funcs));
}


#ifdef JS_SHARED_LIBRARY
#define JS_INIT_MODULE js_init_module
#else
#define JS_INIT_MODULE js_init_module_toolm
#endif

JSModuleDef *JS_INIT_MODULE(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_toolm_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_toolm_funcs, countof(js_toolm_funcs));

    return m;
}



