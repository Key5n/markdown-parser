#include "include/token.h"

const char TEXT[] = "text";
const char STRONG[] = "strong";

const char STRONG_ELM_REGEXP[] = "\\*\\*(.*?)\\*\\*";

Token_t *gen_text_elem(int id, char *text[], Token_t *parent) {
  Token_t token = {id, parent, *TEXT, *text};
  return &token;
}

Token_t *gen_strong_elem(int id, char *text[], Token_t *parent) {
  Token_t token = {id, parent, *STRONG, NULL};
  return &token;
}
