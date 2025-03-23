#ifndef __EEXPR_H__
#define __EEXPR_H__

#include <stddef.h>


#define MAX_TOKENS 1024
#define MAX_TOKEN_LENGTH 16

enum TokenType
{
    NUMBER,
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    POPEN,
    PCLOSE,
};

struct Token
{
    enum TokenType type;
    int number;
};

enum ExpressionType
{
    LITERAL,
    SUM,
    SUB,
    MUL,
    DIV,
};

struct Expression
{
    enum ExpressionType type;
    union
    {
        struct
        {
            struct Expression *left, *right;
        };
        struct Expression *in;
        int number;
    };
};

void eexpr(const char *expr);
size_t tokenize(const char *expr, struct Token tokens[], size_t tokens_length);
struct Expression *parse(struct Token tokens[], size_t tokens_length);
int eval(struct Expression *expr);

#endif /* __EEXPR_H__ */
