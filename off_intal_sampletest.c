#include "intal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int n = 12;
    char **a = (char **) malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        a[i] = (char *) malloc(1001 * sizeof(char));
    }
    strcpy(a[0], "5");
    strcpy(a[1], "10");
    strcpy(a[2], "10");
    strcpy(a[3], "10");
    strcpy(a[4], "10");
    strcpy(a[5], "10");

    // strcpy(a[0], "1234512345123451234512345");
    // strcpy(a[1], "543215432154321543215432154321");
    // strcpy(a[2], "0");
    // strcpy(a[3], "1234512345123451234512345");
    // strcpy(a[4], "1234512345123451234512344");
    // strcpy(a[5], "12");
    strcpy(a[6], "265252859812191058636308480000000");
    strcpy(a[7], "265252859812191058636308480000000");
    strcpy(a[8], "5432154321543215432154321");
    strcpy(a[9], "3");
    strcpy(a[10],
           "1000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "0000000000000000000000000000000000000000000000000000000000000000000"
           "00000000000000000000000000000000000000000000000000000000000000");
    strcpy(
        a[11],
        "1230231922161117176931558813276752514640713895736833715766118029160058"
        "8006146729487753600678385934595824296492540518049085128841808982368235"
        "8508248206534833123495935035584501741302332011136066692262472823975688"
        "0416434478315693675013413090757208690376793296658810662941824493488451"
        "7265053037129160053467479086237026734809193539368131057366204023527447"
        "7690384047788365110032240930198348836380293054048248790976348409825394"
        "0728685132044408863734754271212592471778643949486688511721051561970432"
        "7807474548237768084641806971030838618121843485655227401957966826222055"
        "1184551208055201031005025580158934964592800113374547422071501368341390"
        "7542779063759833876101354235184245096670042160720629411581502371248008"
        "4304471848420986103205804179922066622473287221220885136436839076703602"
        "0916265367064113093699700217050067550137472399876600582757930072325347"
        "4890612250135171889174899079911291512399773872178519018229989376123456789012345678901234567890");
    char *result1;
    int index1;
    // {
    //     char *a = "99999999999999999999999999999999999999999999999999999999999999";
    //     char *b = "00000000000000000000000000000000000000000000000001";
    //     result1 = intal_add(a, b);
    //     printf("%s+%s=%s\n", a, b, result1);
    //     free(result1);
    // }
    // {
    //     char *a = "1000";
    //     char *b = "000000001001";
    //     index1 = intal_compare(a, b);
    //     printf("%s>%s=%d\n", a, b, index1);
    // }
    // {
    //     char *a = "001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    //     char *b = "000999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999";
    //     result1 = intal_diff(a, b);
    //     printf("%s-%s=%s\n", a, b, result1);
    //     free(result1);
    // }
    // {
    //     char *a = "000018742361298374612983746192387634961928743612837412873461192873190280371298374612983746";
    //     char *b = "0000000187689217346817254182735421837582937462918374623414387981456923847651987326489273461928734";
    //     result1 = intal_multiply(a, b);
    //     printf("%s*%s=%s\n", a, b, result1);
    //     free(result1);
    // }
    {
        char *a = "887";
        char *b = "0";
        result1 = intal_mod(a, b);
        printf("%s mod %s=%s\n", a, b, result1);
        free(result1);
    }
    {
        char *a = "2";
        int b = 100;
        result1 = intal_pow(a, b);
        printf("%s^%d=%s\n", a, b, result1);
        free(result1);
    }
    {
        char *a = "3274618723468127364";
        char *b = "0003274618723468127364";
        result1 = intal_gcd(a, b);
        printf("gcd(%s,%s)=%s\n", a, b, result1);
        free(result1);
    }
    // {
    //     int n = 30000;
    //     result1 = intal_fibonacci(n);
    //     printf("fib(%d)=%s\n", n, result1);
    //     free(result1);
    // }
    // {
    //     int n = 5000;
    //     result1 = intal_factorial(n);
    //     printf("fact(%d)=%s\n", n, result1);
    //     free(result1);
    // }
    // {
    //     int a = 1000;
    //     int b = 500;
    //     result1 = intal_bincoeff(a, b);
    //     printf("C(%d,%d)=%s\n", a, b, result1);
    //     free(result1);
    // }
    // {
    //     int a = 100;
    //     result1 = intal_bincoeff(a, b);
    //     printf("C(%d,%d)=%s\n", a, b, result1);
    //     free(result1);
    // }
    // index1 = intal_max(a, n);
    // if (10 == index1)
    // {
    //     printf("Test intal_max PASSED\n");
    // }
    // else
    // {
    //     printf("Test intal_max FAILED.\nYour answer: %d\nExpected answer: %d\n",
    //            index1, 6);
    // }

    // index1 = intal_min(a, n);
    // if (2 == index1)
    // {
    //     printf("Test intal_min PASSED\n");
    // }
    // else
    // {
    //     printf("Test intal_min FAILED.\nYour answer: %d\nExpected answer: %d\n",
    //            index1, 2);
    // }

    index1 = intal_binsearch(a, n, a[5]);
    if (1 == index1)
    {
        printf("Test intal_binsearch PASSED\n");
    }
    else
    {
        printf(
            "Test intal_binsearch FAILED.\nYour answer: %d\nExpected answer: %d\n",
            index1, 0);
    }

    // result1 = coin_row_problem(a, n);
    // if (!result1)
    // {
    //     printf("Test coin_row_problem FAILED.\n");
    // }
    // else
    // {
    //     if (0 ==
    //         strcmp("10000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000265796081911012046846190578820987",
    //                result1))
    //     {
    //         printf("Test coin_row_problem PASSED\n");
    //     }
    //     else
    //     {
    //         printf("Test coin_row_problem FAILED.\nYour answer: %s\nExpected "
    //                "answer: %s\n",
    //                result1,
    //                "10000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000000000000000000000000000000000000000"
    //                "00000000000000000000000265796081911012046846190578820987");
    //     }
    //     free(result1);
    // }

    // intal_sort(a, n);
    // printf("\nTest intal_sort PASSED only if the following sequence of %d "
    //        "intals are sorted in nondecreasing order.\n",
    //        n);
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%s\n", a[i]);
    // }
    // printf("\n");

    // index1 = intal_binsearch(a, n, "3");
    // if (1 == index1)
    // {
    //     printf("Test intal_binsearch and probably intal_sort PASSED\n");
    // }
    // else
    // {
    //     printf("Test intal_binsearch and probably intal_sort FAILED.\nYour "
    //            "answer: %d\nExpected answer: %d\n",
    //            index1, 1);
    // }

    // Don't forget to free all the memory that is dynamically allocated.
    for (int i = 0; i < n; i++)
    {
        free(a[i]);
    }
    free(a);
    return 0;
}
