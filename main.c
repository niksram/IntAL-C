#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intal.h"

int main()
{
    char c1[10001] = "00001020304050607080901020304050607080901020304050607080903210";
    char c2[10001] = "000102030405060708090102030405060708090102030405060708090";
    char c3[10001]="010203040506070";
    char c4[10001]="00000090807060504030";
    char c5[10001]="001234567890123456789";
    char** arr=malloc(5*sizeof(char*));
    arr[0]=c3;
    arr[1]=c4;
    arr[2]=c5;
    arr[3]=c2;
    arr[4]=c1;
    char c6[10001]="99";
    char c7[10001]="9";
    printf("cmp %d\n",intal_compare(c2,c1));
    char* add=intal_add(c6,c7);
    printf("add %s\n",add);
    free(add);
    char* diff=intal_diff(c2,c1);
    printf("diff %s\n",diff);
    free(diff);
    char* fact=intal_factorial(100);
    printf("fact %s\n",fact);
    free(fact);
    char *mul = intal_multiply(c1, c2);
    printf("wholeMul %s\n",mul);
    free(mul);
    char* fib=intal_fibonacci(10000);
    printf("fib %s\n",fib);
    free(fib);
    char* mod=intal_mod(c1,c2);
    printf("mod %s\n",mod);
    free(mod);
    char* gcd=intal_gcd(c1,c2);
    printf("gcd %s\n",gcd);
    free(gcd);
    char* bin=intal_bincoeff(100,20);
    printf("bin %s\n",bin);
    free(bin);
    printf("max %d\n",intal_max(arr,5));
    printf("min %d\n",intal_min(arr,5));
    printf("bsearch %d\n",intal_binsearch(arr,5,c1));
    intal_sort(arr,5);
    printf("SORTED ARRAY\n");
    for(int i=0;i<5;i++)
    {
        printf("%s\n",arr[i]);
    }
    free(arr);
}