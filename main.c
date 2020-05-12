#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intal.h"

int main()
{
    char c1[10001] = "1020304050607080901020304050607080901020304050607080903210";
    char c2[10001] = "102030405060708090102030405060708090102030405060708090";
    // char c1[10001] = "0";
    // char c2[10001] = "0";
    printf("cmp %d\n",intal_compare(c1,c2));
    char* add=intal_add(c1,c2);
    printf("add %s\n",add);
    free(add);
    char* diff=intal_diff(c2,c1);
    printf("diff %s\n",diff);
    free(diff);
    char* fact=intal_factorial(0);
    printf("fact %s\n",fact);
    free(fact);
    char *mul = intal_multiply(c1, c2);
    printf("wholeMul %s\n",mul);
    free(mul);
    //char* fib=intal_fibonacci(10000);
    //printf("fib %s\n",fib);
    //free(fib);
    char* mod=intal_mod(c1,c2);
    printf("mod %s\n",mod);
    free(mod);
    char* gcd=intal_gcd(c1,c2);
    printf("gcd %s\n",gcd);
    free(gcd);
}