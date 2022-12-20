#include "include/func.h"
#include "include/markdown.h"
#include "include/regexp.h"

/**
 * @brief 文字列を受け取って抽象構文木を作る
 * @param markdown ターゲットの文字列
 * @return int型
 */
static int convertToHTMLString(char *markdown)
{
  size_t i = 0;
  size_t size = 0;
  char *result[100];
  const char pattern[] = "^# (.+)";
  const char *delim = "\n";
  size_t num_tokens;
  char *target = markdown;

  printf("===条件===\n");
  printf("正規表現パターン: %s\n", pattern);
  printf("検索対象の文字列: %s\n", target);

  char **tokens = split(target, delim, &num_tokens);
  for (i = 0; i < num_tokens; i++)
  {
    char *token = *tokens;
    parse(token);
  }

  size = regexp(pattern, target, result);

  if (size == FAILURE)
  {
    return EXIT_FAILURE;
  }
  for (i = 0; i < num_tokens; i++)
  {
    printf("split結果No.%d: %s\n", (int)i, tokens[i]);
  }
  /* split関数のメモリ解放 */
  for (i = 0; i < num_tokens; i++)
  {
    free(tokens[i]);
  }
  free(tokens);

  printf("===結果===\n");
  for (i = 0; i < size; i++)
  {
    printf("マッチNo.%d 結果=%s\n", (int)i, result[i]);
    free(result[i]);
  }
}

int main(void)
{
  convertToHTMLString("# aiuoe\n# aiu");
  return 0;
}
