#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief javascriptにおけるsplit関数
 * @param str ターゲットの文字
 * @param delim 分割文字
 * @param size 結果の文字列配列のサイズ
 * @return 文字列配列
 * @note 最後に確保したメモリをfree(char**),
 * free(char*)のように解放する必要がある
 */
extern char** split(const char* str, const char* delim, size_t* num_tokens);

#endif