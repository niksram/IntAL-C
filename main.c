#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intal.h"

int main()
{
    char c1[10001]="102030405060708090102030405060708090102030405060708090";
    char c2[10001]="908070605040302010807060509040302010908070605040302010";
    char* fib=intal_fibonacci(1000);
    char* add=intal_add(c1,c2);
    char* diff=intal_diff(c1,c2);
    printf("add %s\n",add);
    printf("cmp %d\n",intal_compare(c1,c2));
    printf("diff %s\n",diff);
    // printf("wholeMul %s\n",intal_multiply(c1,c2));
    //printf("fib %s\n",fib);
    //printf("fact %s\n",intal_factorial(20));
    // printf("mod %s\n",intal_mod(c1,c2));
    // printf("gcd %s\n",intal_gcd(c1,c2));
    free(fib);
    free(add);
    free(diff);
}