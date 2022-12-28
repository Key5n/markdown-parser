#include "include/list.h"
#include "include/markdown.h"

int main(int argc, char *argv[]) {
  FILE *fp;
  FILE *output;
  char *line = NULL;
  size_t n = 0;
  size_t lineno = 0;
  List_T asts = List_init();

  if (argc != 2) {
    fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if ((fp = fopen("in.md", "r")) == NULL) {
    fprintf(stderr, "Error: cannot open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  if ((output = fopen("result.html", "w")) == NULL) {
    fprintf(stderr, "Error: cannot open %s\n", "result.html");
    exit(EXIT_FAILURE);
  }

  while (getline(&line, &n, fp) != EOF) {
    printf("line = %s\n", line);
    printf("row: %d\n", (int)lineno++);
    asts = __parse(line, asts);
  }

  __generate(asts, output);

  if (line) {
    free(line);
  }
  if (fclose(fp) == EOF) {
    fprintf(stderr, "Error: cannot close %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  if (fclose(output) == EOF) {
    fprintf(stderr, "Error: cannot close %s\n", "result.html");
    exit(EXIT_FAILURE);
  }
  return 0;
}
