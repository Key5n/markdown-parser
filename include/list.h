#ifndef __LIST__
#define __LIST__

#include <assert.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define L List_T
typedef struct L *L;

struct L {
  void *val;
  L next;
};

// リストのinitialize
extern L List_init(void);

// リストの先頭にvalをつける
extern L List_push(L list, void *val);

// リストのサイズ
extern int List_length(L list);

// リストを配列に
extern void **List_toArray(L list);

// リストの連結
extern L List_append(L list, L tail);

// リストのinitialize(初期値を与えるver)
extern L List_list(L list, void *val, ...);

#undef L
#endif