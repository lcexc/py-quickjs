#include <Python.h>
#include <stdio.h>
#include "libqjs.h"


static PyObject* qjs_init(PyObject* self, PyObject *args) {

    return Py_BuildValue("b", 0);
}

static PyObject* qjs_runcode(PyObject* self, PyObject *args) {
    JSRuntime *rt;
    JSContext *ctx;
    const char *s;
    char *code;
    JSValue val, global_obj;
    int ret, tag, code_len, has_module=0, eval_flags;

    if (!PyArg_ParseTuple(args, "s", &code))
        return NULL;
    code_len = strlen(code);
    rt = JS_NewRuntime();
    ctx = JS_NewContext(rt);

    /* loader for ES6 modules */
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

    js_std_add_helpers(ctx, 0, NULL); // int argc, char **argv

    /* system modules */
    js_init_module_std(ctx, "std");
    js_init_module_os(ctx, "os");

    has_module = JS_DetectModule((const char *)code, code_len);

    if (has_module)
        eval_flags = JS_EVAL_TYPE_MODULE;
    else
        eval_flags = JS_EVAL_TYPE_GLOBAL;

    if ((eval_flags & JS_EVAL_TYPE_MASK) == JS_EVAL_TYPE_MODULE) {
        /* for the modules, we compile then run to be able to set
           import.meta */
        val = JS_Eval(ctx, code, code_len, "<input>",
                      eval_flags | JS_EVAL_FLAG_COMPILE_ONLY);
        
        if (JS_IsException(val)) {

            js_std_dump_error(ctx);
            return NULL;
        }

        js_module_set_import_meta(ctx, val, 1, 1);
        val = JS_EvalFunction(ctx, val);
        // 如果包含模块,返回值要写入全局变量
        global_obj = JS_GetGlobalObject(ctx);
        val = JS_GetPropertyStr(ctx, global_obj, "_r");
        JS_FreeValue(ctx, global_obj);
    } else { // 不包含模块,直接运行
        val = JS_Eval(ctx, code, code_len, "<input>", eval_flags);
    }
    // //  buf, buf_len, filename, eval_flags
    // val = JS_Eval(ctx, code, strlen(code), "<input>", -1);
    
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
        return NULL;
    }

    tag = JS_VALUE_GET_TAG(val);
    
    s = JS_ToCString(ctx, val);

    JS_FreeValue(ctx, val);
    // printf("return val[%d]: %s \n", tag, s);

    js_std_free_handlers(rt);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    return Py_BuildValue("s", s);
    
}

static PyMethodDef qjs_funcs[] = {
    {"init", (PyCFunction)qjs_init, METH_VARARGS, "helloworld_docs"},
    {"eval_js", (PyCFunction)qjs_runcode,  METH_VARARGS, "helloworld_docs"},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef qjs_module = {
    PyModuleDef_HEAD_INIT,
    "qjs",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    qjs_funcs
};


PyMODINIT_FUNC PyInit_qjs() {
    return PyModule_Create(&qjs_module);
}
