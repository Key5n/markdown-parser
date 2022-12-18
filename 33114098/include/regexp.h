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

/* regexp.c */
extern regmatch_t *malloc_match_buf(regex_t regex);
extern int _regexec(regex_t *regex, const char *target, regmatch_t *match);
extern int extract_string(const char *target, regex_t *regex, regmatch_t *match,
                          char *result[]);
extern int regexp(const char *regex_pattern, const char *target,
                  char *result[]);
#endif