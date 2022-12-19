#include "../include/func.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

char **split(const char *str, const char *delim, size_t *num_tokens) {
  char *s = strdup(str);
  size_t tokens_alloc = 1;
  size_t tokens_used = 0;
  char **tokens = (char **)calloc(tokens_alloc, sizeof(char *));
  char *token, *strtok_ctx;
  for (token = strtok_r(s, delim, &strtok_ctx); token != NULL;
       token = strtok_r(NULL, delim, &strtok_ctx)) {
    if (tokens_used == tokens_alloc) {
      tokens_alloc *= 2;
      tokens = realloc(tokens, tokens_alloc * sizeof(char *));
    }
    tokens[tokens_used++] = strdup(token);
  }
  // 配列を終端で終わるようにする
  if (tokens_used == tokens_alloc) {
    tokens_alloc++;
    tokens = realloc(tokens, tokens_alloc * sizeof(char *));
  }
  tokens[tokens_used] = NULL;
  *num_tokens = tokens_used;
  free(s);
  return tokens;
}