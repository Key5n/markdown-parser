#ifndef TOKEN_H
#define TOKEN_H

typedef struct token Token_t;

struct token {
  int id;
  Token_t *parent;
  const char *elm_type;
  char *content;
};

#endif