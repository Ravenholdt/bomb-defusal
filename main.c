#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "wires.h"

int main()
{
    srand(time(NULL));

    int r = rand();
    wires(r);

    return 0;
}