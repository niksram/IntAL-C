#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intal.h"

int main()
{
    char c1[100]="1020304050607080901020304050";
    char c2[100]="1020304050607080901020304050607087000896745234694523";
    printf("add %s\n",intal_add(c1,c2));
    printf("cmp %d\n",intal_compare(c1,c2));
    printf("diff %s\n",intal_diff(c1,c2));
    printf("wholeMul %s\n",intal_multiply(c1,c2));
    printf("fib %s\n",intal_fibonacci(460));
}