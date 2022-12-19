#include <stdlib.h>

#include "../include/markdown.h"
#include "../include/token.h"

const char TEXT[] = "text";
const char STRONG[] = "strong";

const char STRONG_ELM_REGEXP[] = "\\*\\*(.*?)\\*\\*";

Token_t *gen_text_elem(int id, char *text, Token_t *parent) {
  Token_t *token = NULL;
  token = (Token_t *)malloc(sizeof(Token_t));

  token->id = id;
  token->parent = parent;
  token->elm_type = TEXT;
  token->content = text;

  return token;
}

Token_t *gen_strong_elem(int id, char *text, Token_t *parent) {
  Token_t *token = NULL;
  token = (Token_t *)malloc(sizeof(Token_t));

  token->id = id;
  token->parent = parent;
  token->elm_type = STRONG;
  token->content = text;

  return token;
}
