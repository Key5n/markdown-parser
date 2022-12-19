#ifndef MARKDOWN_H
#define MARKDOWN_H
#include "token.h"

/**
 * @brief
 * 1行のマークダウンを入力としてグローバル変数の抽象構文木の配列を操作する
 * @param markdown_row 文字列、読み込んだマークダウンの１行
 * @return int
 */
extern int parse(char *markdown_row);
extern Token_t *gen_text_elem(int id, char *text, Token_t *parent);
extern Token_t *gen_strong_elm(int id, char *text, Token_t *parent);

#endif