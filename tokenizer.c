#include "eexpr.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


size_t tokenize(const char *expr, struct Token tokens[], size_t tokens_length)
{
    assert(expr != NULL);
    assert(tokens != NULL);

    char token[MAX_TOKEN_LENGTH + 1] =
    { [MAX_TOKEN_LENGTH] = 0 };

    size_t tokeni = 0, chari = 0;

    do
    {
        switch (*expr)
        {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            token[chari++] = *expr;
            assert(chari < sizeof(token) - 1);
        } break;
        case ' ': case '\t': case '-': case '+':
        case '*': case '/': case '(': case ')':
        {
            if (chari)
            {
                tokens[tokeni++] = (struct Token)
                {
                    .type = NUMBER,
                    .number = atoi(token),
                };
                assert(tokeni < tokens_length);
                chari = 0;
            }

            switch (*expr)
            {
            break; case '-': tokens[tokeni++].type = MINUS;
            break; case '+': tokens[tokeni++].type = PLUS;
            break; case '*': tokens[tokeni++].type = ASTERISK;
            break; case '/': tokens[tokeni++].type = SLASH;
            break; case '(': tokens[tokeni++].type = POPEN;
            break; case ')': tokens[tokeni++].type = PCLOSE;
            }
            assert(tokeni < tokens_length);
        } break;
        default:
        {
            assert(!*expr && "invalid character in the expression");
        } break;
        }
    } while(*++expr != '\0');

    if (chari)
        tokens[tokeni++] = (struct Token)
        {
            .type = NUMBER,
            .number = atoi(token),
        };

    return tokeni;
}
