#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
  int id;
  Token_t *parent;
  char *elm_type;
  char *content;
} Token_t;

#endif