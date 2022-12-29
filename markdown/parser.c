#include "../include/markdown.h"
const char H1[] = "h1";
const char paragraph[] = "p";

// h1タグに変換するための正規表現
text_elm_regexp_t h1_regexps = {.elm_type = H1, .regexp = "^# (.+)$"};

/**
 * @brief listにタグ名をelm_name, 中の文章をresult[1]としたトークンを作る
 * @param list ArrayList<Token_t> この中に入れる
 * @param content トークン化したときの中身の文章
 * @param elm_name トークンのタグ名 (e.g. h1, h2, p)
 * @param size result配列のサイズ
 * 正規表現の実行で確保したresult配列のメモリを解放するのに使う
 */
static List_T __tokenize(List_T list, char *content, const char *elm_name,
                         size_t size);

List_T __parse(char *original_text, List_T asts) {
  // 今回は正規表現にマッチするグループは2つだけ
  const size_t match_size = 2;
  // char *result[match_size];
  char **result = (char **)malloc(sizeof(char) * match_size);
  size_t size = 0;
  size_t i = 0;
  text_elm_regexp_t t = h1_regexps;

  // original textを正規表現の篩にかけた結果マッチするものがあるなら
  if ((size = regexp(t.regexp, original_text, result)) != FAILURE) {
    // h1タグとして変換
    asts = __tokenize(asts, result[1], t.elm_type, size);
    // for (i = 0; i < size; i++) {
    //   free(result[i]);
    // }
    return asts;
  } else {
    // 今回はh1タグに変換できないならpタグとして変換

    asts = __tokenize(asts, original_text, paragraph, size);
    // for (i = 0; i < size; i++) {
    //   free(result[i]);
    // }
    return asts;
  }
}

static List_T __tokenize(List_T asts, char *content, const char *elm_name,
                         size_t size) {
  size_t i = 0;
  List_T list = (List_T)malloc(sizeof(Token_t));
  Token_t *token = (Token_t *)malloc(sizeof(Token_t));

  // 文字列の領域を確保
  // 中身がSTRING_BUFを超えたらどうしよう
  token->content = (char *)malloc(sizeof(char) * STRING_BUF);
  strcpy(token->content, content);
  token->elm_type = elm_name;
  list = List_push(asts, token);
  print_list(list);
  return list;
}