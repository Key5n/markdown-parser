#ifndef REGEX_H
#define REGEX_H

#define SUCCESS 0
#define FAILURE -1
#define NO_FLAG 0
#define STR_BUF_SIZE 1024
#define ALL_MATCH_GROUP 0
#define ALL_MATCH_STR_NR 1
#define NULL_TERMINATION_SIZE 1

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 正規表現によるパターンマッチを行い、processに応じた文字列操作を行う。
 * @param regex_pattern 正規表現パターン
 * @param target 検索対象の文字列
 * @param result
 * 文字列操作結果を格納するための二次元配列（二次元目のみ自動でメモリ確保を行う）
 * @param process 文字列操作を行う関数へのポインタ
 * @return 正の値（マッチングした文字列の数）：成功、FAILURE：失敗
 * @note
 * 正の値が返った場合は、その数の分だけresultにメモリ確保を行っているため、メモリ解放しなければいけない。
 */
extern int regexp(const char *regex_pattern, const char *target,
                  char *result[]);

#endif