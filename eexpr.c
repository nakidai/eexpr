#include "eexpr.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>


void eexpr(const char *expr)
{
    struct Token tokens[MAX_TOKENS];
    size_t tokens_count = tokenize(expr, tokens, MAX_TOKENS);
    int x = eval(parse(tokens, tokens_count));
    printf("%d\n", x);
}
