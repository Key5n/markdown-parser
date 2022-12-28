#include "../include/markdown.h"
const char H1[] = "h1";
const char paragraph[] = "p";

text_elm_regexp_t h1_regexps = {.elm_type = H1, .regexp = "^# (.+)\n$"};

/**
 * @brief listにタグ名をelm_name, 中の文章をresult[1]としたトークンを作る
 * @param list ArrayList<Token_t> この中に入れる
 * @param result
 * 正規表現とマッチしたものが入っている。result[0]は全体一致、result[1]は文章が入っている
 * @param elm_name トークンのタグ名 (e.g. h1, h2, p)
 * @param size result配列のサイズ
 * 正規表現の実行で確保したresult配列のメモリを解放するのに使う
 */
static List_T __tokenize(List_T list, char **result, const char *elm_name,
                         size_t size);

List_T __parse(char *original_text, List_T asts) {
  const size_t num_match = 2;
  char *result[num_match];
  size_t size = 0;
  size_t i = 0;
  text_elm_regexp_t t = h1_regexps;

  if ((size = regexp(t.regexp, original_text, result)) != FAILURE) {
    asts = __tokenize(asts, result, t.elm_type, size);

    return asts;
  } else {
    Token_t *paragraph_token = (Token_t *)malloc(sizeof(Token_t));
    paragraph_token->content = original_text;
    paragraph_token->elm_type = paragraph;
    asts = List_push(asts, &paragraph_token);

    return asts;
  }
}

static List_T __tokenize(List_T asts, char **result, const char *elm_name,
                         size_t size) {
  size_t i = 0;
  List_T list = (List_T)malloc(sizeof(Token_t));
  Token_t *token = (Token_t *)malloc(sizeof(Token_t));
  token->content = (char *)malloc(sizeof(char) * STRING_BUF);
  strcpy(token->content, result[1]);
  token->elm_type = elm_name;
  list = List_push(asts, token);
  print_list(list);
  for (i = 0; i < size; i++) {
    free(result[i]);
  }
  return list;
}