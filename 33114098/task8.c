#include "include/regexp.h"

static int convertToHTMLString(char *markdown) {
  size_t i = 0;
  size_t size = 0;
  char *result[100];
  const char pattern[] = "^# (.+)";
  char *target = markdown;
  printf("===条件===\n");
  printf("正規表現パターン: %s\n", pattern);
  printf("検索対象の文字列: %s\n", target);

  size = regexp(pattern, target, result);
  if (size == FAILURE) {
    return EXIT_FAILURE;
  }
  printf("===結果===\n");
  for (i = 0; i < size; i++) {
    printf("マッチNo.%d 結果=%s\n", (int)i, result[i]);
    free(result[i]);
  }
}
int main(void) { convertToHTMLString("# aiuoe"); }
