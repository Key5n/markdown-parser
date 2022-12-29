#include "../include/list.h"
#include "../include/markdown.h"
#include "../include/token.h"
void print_list(List_T list) { Token_t *a = (Token_t *)list->val; }

int __generate(List_T list, FILE *output) {
  int i = 0;
  int length = List_length(list);
  // listを配列化
  Token_t **token_array = (Token_t **)malloc(sizeof(Token_t) * length);
  token_array = (Token_t **)List_toArray(list);
  // デバッグ用の表示
  print_list(list);

  // ast配列をhtmlに変換してファイル出力
  // 配列のサイズはトークン数+1
  for (i = (int)length - 2; i >= 0; i--) {
    Token_t *token = token_array[i];
    const char *content = token->content;
    const char *elm_type = token->elm_type;
    fprintf(output, "<%s>%s</%s>\n", elm_type, content, elm_type);
  }
  return 0;
}