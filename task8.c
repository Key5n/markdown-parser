#include "include/list.h"
#include "include/markdown.h"

int main(int argc, char *argv[]) {
  FILE *input;
  FILE *output;
  char *line = NULL;
  size_t n = 0;
  size_t lineno = 0;
  List_T asts = List_init();

  // ファイル名が指定されていない場合exit
  if (argc != 2) {
    fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // input用のファイルが開けない場合exit
  if ((input = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Error: cannot open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  // output用のファイルが開けない場合exit
  if ((output = fopen("result.html", "w")) == NULL) {
    fprintf(stderr, "Error: cannot open %s\n", "result.html");
    exit(EXIT_FAILURE);
  }

  // inputファイルから一行取得してhtmlに変換
  while (getline(&line, &n, input) != EOF) {
    printf("line = %s\n", line);
    printf("row: %d\n", (int)lineno++);
    asts = __parse(line, asts);
  }

  __generate(asts, output);

  if (line) {
    free(line);
  }
  // ファイルが閉じれない場合exit
  if (fclose(input) == EOF) {
    fprintf(stderr, "Error: cannot close %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  // ファイルが閉じれない場合exit
  if (fclose(output) == EOF) {
    fprintf(stderr, "Error: cannot close %s\n", "result.html");
    exit(EXIT_FAILURE);
  }
  return 0;
}
