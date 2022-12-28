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

extern L List_init(void);
extern L List_push(L list, void *val);
extern int List_length(L list);
extern void **List_toArray(L list);
extern L List_append(L list, L tail);
extern L List_list(L list, void *val, ...);

#undef L
#endif