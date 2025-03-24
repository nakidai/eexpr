#include "eexpr.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


struct Expression *parse(struct Token tokens[], size_t tokens_length)
{
    assert(tokens);

    while (tokens_length >= 2)
    {
        if (tokens[0].type == POPEN && tokens[tokens_length - 1].type == PCLOSE)
        {
            ++tokens;
            tokens_length -= 2;
        } else
        {
            break;
        }
    }

    assert(tokens_length != 0 && "empty parens are not supported yet");

    struct Expression *res = malloc(sizeof(*res));
    assert(res != NULL);

    struct { ssize_t i, depth; } selected =
    { -1, -1 };
    size_t depth = 0;

    if (tokens_length == 1)
    {
        assert(tokens[0].type == NUMBER);
        *res = (struct Expression)
        {
            .type = LITERAL,
            .number = tokens[0].number,
        };
        goto end;
    }

    for (size_t i = 0; i < tokens_length; ++i)
    {
        switch (tokens[i].type)
        {
        case POPEN:
        {
            ++depth;
        } break;
        case PCLOSE:
        {
            assert(--depth >= 0);
        } break;
        case PLUS: case MINUS: 
        {
            if (depth == selected.depth)
                if (tokens[selected.i].type == ASTERISK
                    || tokens[selected.i].type == SLASH)
                {
                    selected.i = i;
                    break;
                }
        } /* FALLTHROUGH */
        case ASTERISK: case SLASH:
        {
            if (selected.i == -1 || depth < selected.depth)
            {
                selected.i = i;
                selected.depth = depth;
                break;
            }
        } break;
        }
    }

    assert(depth == 0 && "too many opening parenthesis");
    assert(selected.i >= 0 && "multiple numbers in a row");

    switch (tokens[selected.i].type)
    {
    break; case PLUS: res->type = SUM;
    break; case MINUS: res->type = SUB;
    break; case ASTERISK: res->type = MUL;
    break; case SLASH: res->type = DIV;
    }

    if ((res->type == SUM || res->type == SUB) && selected.i == 0)
    {
        res->left = malloc(sizeof(*res->left));
        *res->left = (struct Expression)
        {
            .type=LITERAL,
            .number=0,
        };
    } else
    {
        res->left = parse(tokens, tokens_length - (tokens_length - selected.i));
    }
    res->right = parse(tokens + selected.i + 1, tokens_length - selected.i - 1);

end:
    return res;
}
