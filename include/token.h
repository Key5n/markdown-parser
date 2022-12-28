#ifndef TOKEN_H
#define TOKEN_H

typedef struct token Token_t;

struct token {
  char *content;
  const char *elm_type;
};

#endif