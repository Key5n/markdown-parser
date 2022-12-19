#include <stdlib.h>

#include "../include/markdown.h"
#include "../include/token.h"

static int __tokenizeText(char *textElement[], int initial_id, Token_t *Token,
                          Token_t *ast[]) {}

const Token_t root_token = {
    .id = 0, .elm_type = "root", .content = "", .parent = NULL};

int parse(char *markdown_row) { return markdown_row; }
