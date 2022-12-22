#include "../include/regexp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int __regcomp(regex_t *regex, const char *pattern);
static regmatch_t *malloc_match_buf(regex_t regex);
static int __regexec(regex_t *regex, const char *target, regmatch_t *match);
static int mallocStrArray(size_t size, int element_nr, char *result[]);
static int extract_string(const char *target, regex_t *regex, regmatch_t *match,
                          char *result[]);

/**
 * @brief 正規表現パターンのコンパイルを行う。
 * @param regex
 * 正規表現パターンのコンパイル結果を記憶する。通称：正規表現オブジェクト
 * @param pattern 正規表現パターン文字列
 * @return SUCCESS：成功、FAILURE：失敗
 * @note
 * 成功時はregexにメモリを割り当てるため、regfree()によるメモリ解放が必要。
 */
static int __regcomp(regex_t *regex, const char *pattern) {
  if (regcomp(regex, pattern, REG_EXTENDED)) {
    fprintf(stderr, "%s: Fail regex pattern(=%s) compile\n", __func__, pattern);
    return FAILURE;
  }
  return SUCCESS;
}

/**
 * @brief 正規表現パターンマッチ位置を保持するためのバッファを確保する。
 * @param regex コンパイル済みの正規表現オブジェクト
 * @return NULL以外：成功、NULL：失敗
 * @note 成功時はメモリを割り当てるため、free()によるメモリ解放が必要。
 */
static regmatch_t *malloc_match_buf(regex_t regex) {
  regmatch_t *match = NULL;
  /*
   * re_nsubには"("と")"で囲まれたグループの数が格納されている。
   * つまり、正規表現パターン全体にマッチした文字列の数が含まれていない。
   */
  match = (regmatch_t *)malloc(sizeof(regmatch_t) *
                               (regex.re_nsub + ALL_MATCH_STR_NR));
  if (match == NULL) {
    fprintf(stderr, "%s: Can't malloc memory.\n", __func__);
    return NULL;
  }
  return match;
}

/**
 * @brief 正規表現によるパターンマッチを行い、その結果を返す。
 * @param regex コンパイル済みの正規表現オブジェクト
 * @param target 検索対象の文字列
 * @param match 正規表現パターンマッチ位置を保持する（マッチンググループ情報）。
 * @return SUCCESS：成功、FAILURE：失敗
 */
static int __regexec(regex_t *regex, const char *target, regmatch_t *match) {
  int err_code = 0;
  char err_msg[STR_BUF_SIZE];

  memset(err_msg, '\0', STR_BUF_SIZE);

  (err_code = regexec(regex, target, (regex->re_nsub + ALL_MATCH_STR_NR), match,
                      NO_FLAG));

  // if ((err_code = regexec(regex, target, (regex->re_nsub + ALL_MATCH_STR_NR),
  //                         match, NO_FLAG))) {
  //   /* regerror()は、regexec()のエラーメッセージを作成する。
  //    * エラーメッセージサイズはSTR_BUF_SIZEとなるため、文字列バッファサイズを超えない。*/
  //   regerror(err_code, regex, err_msg, STR_BUF_SIZE);
  //   fprintf(stderr, "%s: %s\n", __func__, err_msg);
  //   return FAILURE;
  // }
  return SUCCESS;
}

/**
 * @brief 複数の文字列を保持するためメモリ確保を行う（メモリ確保は二次元目のみ）
 * @param size 文字列のサイズ
 * @param element_nr 要素数
 * @param result
 * 文字列操作結果を格納するための二次元配列（二次元目のみ自動でメモリ確保を行う）
 * @return SUCCESS：成功、FAILURE：失敗
 */
static int mallocStrArray(size_t size, int element_nr, char *result[]) {
  size_t i = 0;
  size_t j = 0;

  for (i = 0; i < element_nr; i++) {
    result[i] = malloc(sizeof(char) * size);
    if (NULL == result[i]) {
      /* メモリ確保失敗時は、途中まで確保したメモリを解放する */
      fprintf(stderr, "%s: Can't malloc memory.\n", __func__);
      for (j = 0; j < i; j++) {
        free(result[j]);
      }
      return FAILURE;
    }
    memset(result[i], '\0', sizeof(char) * size);
  }
  return SUCCESS;
}

/**
 * @brief マッチングした文字列を抽出する。
 * @param target 検索対象の文字列
 * @param regex コンパイル済みの正規表現パターン
 * @param match 正規表現パターンマッチング結果
 * @param result マッチングした文字列
 * @return SUCCESS：成功、FAILURE：失敗
 */
static int extract_string(const char *target, regex_t *regex, regmatch_t *match,
                          char *result[]) {
  size_t i = 0;
  size_t extract_nr = regex->re_nsub + ALL_MATCH_STR_NR;
  size_t array_element_size =
      sizeof(char) * (strlen(target) + NULL_TERMINATION_SIZE);
  size_t str_size = 0;

  /*
   * 抽出文字列の最大サイズは、検索対象文字列のサイズを超えないため、
   * 「抽出文字列の数 *
   * 検索対象文字列サイズ（NULL終端含む）」のメモリ確保を行う。
   *  配列の1次元目（result[N][]のN分）は、メモリ確保済みと仮定する。
   */
  mallocStrArray(array_element_size, extract_nr, result);

  for (i = 0; i < extract_nr; i++, match++) {
    if ((match->rm_so == FAILURE) || (match->rm_eo == FAILURE)) {
      printf("No.%ld is not match\n", i);
      continue; /* 開始／終了オフセットが-1の場合は、マッチングしていない */
    }
    str_size = match->rm_eo - match->rm_so;
    strncpy(result[i], (const char *)(&target[match->rm_so]), str_size);
    result[i][str_size] = '\0'; /* 念の為、NULL終端を付与。*/
  }

  return extract_nr;
}
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
int regexp(const char *regex_pattern, const char *target, char *result[]) {
  int err_code = SUCCESS;
  regex_t regex;
  regmatch_t *match = NULL;

  if (regex_pattern == NULL || target == NULL || result == NULL) {
    fprintf(stderr, "%s: Regular expression argument is null.\n", __func__);
    return FAILURE;
  }

  memset(&regex, 0, sizeof(regex_t));

  if ((err_code = __regcomp(&regex, regex_pattern))) {
    goto all_end;
  }

  if ((match = malloc_match_buf(regex)) == NULL) {
    goto free_regex_obj;
  }

  if ((err_code = __regexec(&regex, target, match))) {
    goto free_match_obj;
  }

  /* 置換やマッチング文字の抽出などを関数ポインタに応じて行う */
  err_code = extract_string((const char *)target, &regex, match, result);

free_match_obj:
  free(match);
free_regex_obj:
  regfree(&regex);
all_end:
  return err_code;
}
