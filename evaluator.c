#include "eexpr.h"

#include <stdio.h>
#include <assert.h>


int eval(struct Expression *expr)
{
    if (expr->type == LITERAL)
        return expr->number;
    else if (expr->type == SUM)
        return eval(expr->left) + eval(expr->right);
    else if (expr->type == SUB)
        return eval(expr->left) - eval(expr->right);
    else if (expr->type == MUL)
        return eval(expr->left) * eval(expr->right);
    else if (expr->type == DIV)
        return eval(expr->left) / eval(expr->right);
    printf("%d\n", expr->type);
    assert(0 && "unknown expression type");
}
