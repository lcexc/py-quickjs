
#ifndef LIB_QJS_LIBC_H
#define LIB_QJS_LIBC_H

#include <stdio.h>

#include "quickjs.h"
#include "quickjs-libc.h"

int eval_buf(JSContext *ctx, const void *buf, int buf_len,
                    const char *filename, int eval_flags);

int eval_file(JSContext *ctx, const char *filename, int module);                

#endif /* LIB_QJS_LIBC_H */
