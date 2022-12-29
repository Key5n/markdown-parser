#ifndef MARKDOWN_H
#define MARKDOWN_H
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "regexp.h"
#include "token.h"

#define STRING_BUF 1024

typedef struct text_elm_regexp text_elm_regexp_t;

struct text_elm_regexp {
  const char *elm_type;
  const char *regexp;
};

/**
 * @brief すべての正規表現と比較してトークンを作る
 * @param original_text トークン化前の文章
 * @param asts ArrayList<Token_t> ここにトークン化したものをpushする
 * @return 1 成功, 0 失敗
 */
extern List_T __parse(char *original_text, List_T list);

/**
 * @brief HTMlを出力する
 * @param list トークンが格納されているリスト
 * @return SUCCESS 成功, FAILURE 失敗
 */
extern int __generate(List_T list, FILE *fp);

// デバッグ用
void print_list(List_T list);
#endif