#include "eexpr.h"

#include <stdio.h>


int main(int argc, char **argv)
{
    if (!argv[1])
        return 1;
    eexpr(argv[1]);
}
