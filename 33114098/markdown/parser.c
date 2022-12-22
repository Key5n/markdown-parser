#include <stdlib.h>
#include <string.h>

#include "../include/list.h"
#include "../include/markdown.h"
#include "../include/regexp.h"
#include "../include/token.h"

/**
 * @brief
 * テキストエレメントをトークン化する。そのテキストの中に合致する正規表現があればさらにその合致したテキストをトークン化する
 * @param text_element テキストトークン化しようとした文字列
 * @param initial_id テキストトークン化されるものの親のid
 * @param initial_root テキストトークン化されるものの親トークン
 * @return ast 抽象構文木を表すリスト
 */
static List_T __tokenizeText(char *textElement[], int initial_id,
                             Token_t *initial_root);

/**
 * @brief markdown記法に合致するシンボルがあればそれをトークン化する
 * @param original_text ターゲット文字列
 * @param parent
 */
static int __tokenize(char *original_text, Token_t *parent);

const Token_t root_token = {
    .id = 0, .elm_type = "root", .content = "", .parent = NULL};

static List_T __tokenizeText(char *text_element[], int initial_id,
                             Token_t *initial_root) {
  List_T ast = List_init();
  Token_t *parent = initial_root;
  int id = initial_id;
  __tokenize(text_element, parent);
  return ast;
}

static int __tokenize(char *original_text, Token_t *parent) {
  char *processing_text = original_text;
  while (strlen(processing_text) != 0) {
  }
}

int parse(char *markdown_row) { return markdown_row; }