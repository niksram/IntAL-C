#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intal.h"
#include <limits.h>

typedef struct Node //node structure of double linked list
{
    int ele;
    struct Node *great;//successive digit
    struct Node *less;//predecessive digit
} Node;

typedef struct IntStore //head structure of doubly linked list
{
    Node *msd;//most significant digit
    Node *lsd;//least significant digit
} IntStore;

static IntStore *init_intstore(); //initialise DLL
static Node *create_node(int);//create node for DLL
static void insert_intstore(IntStore *, Node *, int);//insert node into DLL
static IntStore *string_to_intstore(const char *);//Intal string to DLL
static char *intstore_to_string(IntStore *);//DLL to Intal string
static void free_intstore(IntStore *);//freeing DLL
static int len_instore(IntStore *);//len of intal number
static char *single_multiply(const char *, int, int);//multiply an intal_string with single digit integer
static void mergesort(char **, int, int);//mergesort for recursion
static void merge_sortedhalves(char **, int, int, int);//merging function for mergesort
static char *rec_intal_bincoeff(unsigned int, unsigned int, char ***);//recursive function for binary coefficient
static char *string_intal_pow(const char *intal1, const char *intal2);//old power function
static char *looper(const char *intal1, int, long int);//loop function fo old power function
// static void mallcopy(char* dest,char* source);

// void mallcopy(char* dest,char* source)
// {
//     char* dest=(char*)malloc((strlen)sizeof(char));
// }

IntStore *init_intstore()//initialise the DLL
{
    IntStore *istore = (IntStore *)malloc(sizeof(IntStore));
    istore->msd = NULL;
    istore->lsd = NULL;
    return istore;
}

int len_instore(IntStore *istore)//to fing length of Intal number
{
    Node *node = istore->lsd;
    int len = 0;
    while (node)//traversing DLL to find the length
    {
        node = node->great;
        len++;
    }
    return len;
}

void free_intstore(IntStore *istore)//freeing the DLL
{
    Node *node = istore->lsd;
    while (node)
    {
        Node *temp = node;
        node = node->great;
        free(temp);
    }
    free(istore);
}

Node *create_node(int val)//creating a node for a digit
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->ele = val;
    node->great = NULL;
    node->less = NULL;
    return node;
}

void insert_intstore(IntStore *istore, Node *node, int pos)//insert a digit node into IntStore DLL
{
    if (istore->lsd == NULL && istore->msd == NULL)
    {
        istore->lsd = node;
        istore->msd = node;
    }
    else if (pos == -1)//if pos==-1, insert at msd side
    {
        node->less = istore->msd;
        istore->msd = node;
        if (node->less)
            node->less->great = node;
    }
    else if (pos == 0)//if pos==0, insert at lsd side
    {
        node->great = istore->lsd;
        istore->lsd = node;
        if (node->great)
            node->great->less = node;
    }
    else//insert at nth position
    {
        Node *move = istore->lsd;
        for (int i = 1; i < pos; i++)
        {
            move = move->great;
        }
        node->great = move->great;
        node->less = move;
        move->great->less = node;
        move->great = node;
    }//wrong inputs of pos not taken care of, as its called only internally
}

IntStore *string_to_intstore(const char *intal1)//convert string to DLL
{
    int len = strlen(intal1);
    IntStore *istore = init_intstore();
    int j = 0;
    while (j < len && intal1[j] == '0')//stripping zeros on the msb side
    {
        j++;
    }
    for (int i = j; i < len; i++)//inserting nodes
    {
        Node *node = create_node((int)(intal1[i]) - (int)('0'));
        insert_intstore(istore, node, 0);
    }
    return istore;
}

char *intstore_to_string(IntStore *istore)//convert DLL to string
{
    Node *node = istore->msd;
    while (node && node->ele == 0)
    {
        node = node->less;
    }//stripping zeros if present (most unlikely)
    Node *nodecopy = node;
    int len = 0;
    while (node)//determining length of the string
    {
        node = node->less;
        len++;
    }
    char *s = (char *)malloc((len + 1) * sizeof(char));
    if (len != 0)
    {
        for (int i = 0; i < len && nodecopy; i++)
        {
            s[i] = (char)(nodecopy->ele + (int)('0'));
            nodecopy = nodecopy->less;
        }
        s[len] = '\0';
    }
    else//if len=0, then 0 must be stored
    {
        strcpy(s, "0\0");
    }
    return (s);
}

char *intal_add(const char *intal1, const char *intal2)
{
    IntStore *istore1 = string_to_intstore(intal1);//generate IntStore DLL's
    IntStore *istore2 = string_to_intstore(intal2);
    IntStore *sumstore = init_intstore();//for storing sum
    int carry = 0;
    Node *node1 = istore1->lsd;
    Node *node2 = istore2->lsd;
    while (node1 && node2)//while both node exists from lsd side
    {
        Node *new = create_node((node1->ele + node2->ele + carry) % 10);//single digit at its position
        carry = (node1->ele + node2->ele + carry) / 10;//carry
        node1 = node1->great;
        node2 = node2->great;
        insert_intstore(sumstore, new, -1);
    }
    while (node1)//when only node1 exists(when intal1 is longer than intal2)
    {
        Node *new = create_node((node1->ele + carry) % 10);
        carry = (node1->ele + carry) / 10;
        node1 = node1->great;
        insert_intstore(sumstore, new, -1);
    }
    while (node2)//when only node2 exists(when intal2 is longer than intal1)
    {
        Node *new = create_node((node2->ele + carry) % 10);
        carry = (node2->ele + carry) / 10;
        node2 = node2->great;
        insert_intstore(sumstore, new, -1);
    }
    if (carry)// if carry still resides
    {
        Node *new = create_node(carry % 10);
        insert_intstore(sumstore, new, -1);
    }
    Node *n = sumstore->lsd;
    char *c = intstore_to_string(sumstore);
    free_intstore(sumstore);
    free_intstore(istore1);
    free_intstore(istore2);
    return (c);
}

int intal_compare(const char *intal1, const char *intal2)
{
    IntStore *istore1 = string_to_intstore(intal1);
    IntStore *istore2 = string_to_intstore(intal2);
    int l1 = len_instore(istore1);
    int l2 = len_instore(istore2);
    if (l1 != l2)//if there exists a difference in the length, then result can be concluded immediately
    {
        free_intstore(istore1);
        free_intstore(istore2);
        if (l1 > l2)
            return 1;
        else
            return -1;
    }
    else//if length is same for both the strings
    {
        Node *n1 = istore1->msd;
        Node *n2 = istore2->msd;
        int val = 0;
        while (n1 && n2)//traverse from msd side
        {
            if (n1->ele > n2->ele)
            {
                val = 1;
                break;
            }
            else if (n1->ele < n2->ele)
            {
                val = -1;
                break;
            }
            n1 = n1->less;
            n2 = n2->less;
        }//if both are equal
        free_intstore(istore1);
        free_intstore(istore2);
        return val;
    }
}

char *intal_diff(const char *intal1, const char *intal2)
{
    IntStore *istore1;
    IntStore *istore2;
    int cmp = intal_compare(intal1, intal2);//to decide which string is greater
    if (cmp == 1)
    {
        istore1 = string_to_intstore(intal1);
        istore2 = string_to_intstore(intal2);
    }
    else if (cmp == -1)
    {
        istore2 = string_to_intstore(intal1);
        istore1 = string_to_intstore(intal2);
    }
    else//if both are equal
    {
        char *s = (char *)malloc(2 * sizeof(char));
        strcpy(s, "0\0");
        return s;
    }
    Node *n1 = istore1->lsd;
    Node *n2 = istore2->lsd;
    while (n1 && n2)//difference is calculated and stored in istore2
    {
        n1->ele -= n2->ele;
        if (n1->ele < 0)
        {
            n1->ele += 10;
            if (n1->great)//borrow from successor
                n1->great->ele--;
        }
        n1 = n1->great;
        n2 = n2->great;
    }
    while (n1 && n1->ele < 0)//to neutralise the negative borrows stored in the DLL
    {
        n1->ele += 10;
        if (n1->great)
            n1->great->ele--;
        n1 = n1->great;
    }
    char *s = intstore_to_string(istore1);
    free_intstore(istore1);
    free_intstore(istore2);
    return s;
}

char *single_multiply(const char *intal1, int n, int offset)//multiply a intal string with 1 integer digit, offset is a parameter used to multiply by 10^offset
{
    IntStore *istore1 = string_to_intstore(intal1);
    Node *n1 = istore1->lsd;
    long int carry = 0;
    while (n1)//similar to addition, the carry is passed on
    {
        int old_ele = n1->ele;
        n1->ele = (old_ele * n + carry) % 10;
        carry = (old_ele * n + carry) / 10;
        n1 = n1->great;
    }
    while (carry)//adding nodes, till carry prevails
    {
        Node *node = create_node(carry % 10);
        insert_intstore(istore1, node, -1);
        carry /= 10;
    }
    for (int i = 0; i < offset; i++)//inserting zeros, offset enables result=result*(10^offset), used in mod to increase efficiency
    {
        Node *node = create_node(0);
        insert_intstore(istore1, node, 0);
    }
    char *s = intstore_to_string(istore1);
    free_intstore(istore1);
    return s;
}

char *intal_multiply(const char *intal1, const char *intal2)//multiply  2 intal strings
{
    IntStore *istore2 = string_to_intstore(intal2);
    char *product = (char *)malloc(2 * sizeof(char));
    strcpy(product, "0\0");
    int count = 0;
    Node *n2 = istore2->lsd;
    while (n2)
    {
        char *s2 = single_multiply(intal1, n2->ele, count++);
        char *temp = product;
        product = intal_add(s2, product);
        free(s2);
        free(temp);
        n2 = n2->great;
    }
    free_intstore(istore2);
    return product;
}

char *intal_mod(const char *intal1, const char *intal2)
{
    char *i1 = (char *)malloc((strlen(intal1) + 1) * sizeof(char));
    strcpy(i1, intal1);
    int len;
    while (intal_compare(i1, intal2) != -1)
    {
        if (i1[0] > intal2[0])
            len = strlen(i1) - strlen(intal2);
        else
            len = strlen(i1) - strlen(intal2) - 1;
        if (len < 0)
            len = 0;
        char *temp = single_multiply(intal2, 1, len);
        char *temp2 = i1;
        i1 = intal_diff(i1, temp);
        free(temp);
        free(temp2);
    }
    return i1;
}

char *intal_fibonacci(unsigned int n)
{
    char *s1 = (char *)malloc(2 * sizeof(char));
    char *s2 = (char *)malloc(2 * sizeof(char));
    char *s3;
    strcpy(s1, "0\0");
    strcpy(s2, "1\0");
    if (n == 0)
    {
        free(s2);
        return s1;
    }
    else if (n == 1)
    {
        free(s1);
        return s2;
    }
    else
    {
        for (int i = 2; i <= n; i++)
        {
            s3 = intal_add(s1, s2);
            free(s1);
            s1 = s2;
            s2 = s3;
        }
        free(s1);
        return s3;
    }
}

char *intal_factorial(unsigned int n)
{
    char *s = (char *)malloc(2 * sizeof(char));
    strcpy(s, "1\0");
    for (int i = 2; i <= n; i++)
    {
        char *temp = s;
        s = single_multiply(s, i, 0);
        free(temp);
    }
    return s;
}

char *intal_gcd(const char *intal1, const char *intal2)
{
    char *i1 = (char *)malloc((strlen(intal1) + 1) * sizeof(char));
    strcpy(i1, intal1);
    char *i2 = (char *)malloc((strlen(intal2) + 1) * sizeof(char));
    strcpy(i2, intal2);
    char *zero = (char *)malloc(2 * sizeof(char));
    strcpy(zero, "0\0");
    char *temp;
    while (intal_compare(i1, zero) == 1 && intal_compare(i2, zero) == 1)
    {
        if (intal_compare(i1, i2) >= 0)
        {
            temp = i1;
            i1 = intal_mod(i1, i2);
        }
        else
        {
            temp = i2;
            i2 = intal_mod(i2, i1);
        }
        free(temp);
    }
    if (intal_compare(i1, zero))
    {
        free(i2);
        free(zero);
        return i1;
    }
    else
    {
        free(i1);
        free(zero);
        return i2;
    }
}

int intal_max(char **arr, int n)
{
    int max_ind = 0;
    for (int i = 1; i < n; i++)
    {
        if (intal_compare(arr[i], arr[max_ind]) == 1)
            max_ind = i;
    }
    return max_ind;
}

int intal_min(char **arr, int n)
{
    int min_ind = 0;
    for (int i = 1; i < n; i++)
    {
        if (intal_compare(arr[i], arr[min_ind]) == -1)
            min_ind = i;
    }
    return min_ind;
}

int intal_search(char **arr, int n, const char *key)
{
    for (int i = 0; i < n; i++)
    {
        if (!intal_compare(arr[i], key))
            return i;
    }
}

int intal_binsearch(char **arr, int n, const char *key)
{
    int lower = 0;
    int higher = n - 1;
    while (higher >= lower)
    {
        int mid = (lower + higher) / 2;
        if (intal_compare(arr[mid], key) == -1)
        {
            lower = mid + 1;
        }
        else if (intal_compare(arr[mid], key) == 1)
        {
            higher = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

void intal_sort(char **arr, int n)
{
    mergesort(arr, 0, n - 1);
}

void mergesort(char **a, int start, int end)
{
    if (start - end)
    {
        mergesort(a, start, (start + end) / 2);
        mergesort(a, (start + end) / 2 + 1, end);
        merge_sortedhalves(a, start, (start + end) / 2 + 1, end);
    }
}

void merge_sortedhalves(char **a, int start, int mid, int end)
{
    int i = start;
    int j = mid;
    int pos = 0;
    char *b[end - start + 1];
    while (i < mid && j <= end)
    {
        if (intal_compare(a[i], a[j]) == -1)
        {
            b[pos++] = a[i++];
        }
        else
        {
            b[pos++] = a[j++];
        }
    }
    while (i < mid)
    {
        b[pos++] = a[i++];
    }
    while (j < pos)
    {
        b[pos++] = a[j++];
    }
    for (int i = 0; i < pos; i++)
    {
        a[start + i] = b[i];
    }
}

char *intal_bincoeff(unsigned int n, unsigned int k)
{
    char ***cube;
    cube = (char ***)malloc((n + 1) * sizeof(char **));
    for (unsigned int i = 0; i <= n; i++)
    {
        cube[i] = (char **)malloc((k + 1) * sizeof(char *));
        for (unsigned int j = 0; j <= k; j++)
            cube[i][j] = NULL;
    }
    char *res = rec_intal_bincoeff(n, k, cube);
    for (unsigned int i = 0; i <= n; i++)
    {
        for (unsigned int j = 0; j <= k; j++)
            if (cube[i][j])
                free(cube[i][j]);
        free(cube[i]);
    }
    free(cube);
    return (res);
}

char *rec_intal_bincoeff(unsigned int n, unsigned int k, char ***cube)
{
    char *result, *cpy;
    if (cube[n][k] != NULL)
    {
        result = cube[n][k];
    }
    else
    {
        if (n == k || k == 0)
        {
            result = (char *)malloc(2 * sizeof(char));
            strcpy(result, "1\0");
            cube[n][k] = result;
        }
        else
        {
            char *first = rec_intal_bincoeff(n - 1, k - 1, cube);
            char *second = rec_intal_bincoeff(n - 1, k, cube);
            result = intal_add(first, second);
            free(first);
            free(second);
            cube[n][k] = result;
        }
    }
    cpy = (char *)malloc((strlen(result) + 1) * sizeof(char));
    strcpy(cpy, result);
    return (cpy);
}

char *intal_pow(const char *intal1, unsigned int n)
{
    if (n == 0)
    {
        char *s = (char *)malloc(2 * sizeof(char));
        strcpy(s, "1\0");
        return s;
    }
    else
    {
        char *temp = intal_pow(intal1, n / 2);
        char *res, *temp3;
        if (n % 2 == 0)
        {
            res = intal_multiply(temp, temp);
        }
        else
        {
            temp3 = intal_multiply(temp, temp);
            res = intal_multiply(temp3, intal1);
            free(temp3);
        }
        free(temp);
        return res;
    }
}

char *coin_row_problem(char **arr, int n)
{
    if (n == 1)
    {
        char *s = (char *)malloc((strlen(arr[0]) + 1) * sizeof(char));
        strcpy(s, arr[0]);
        return s;
    }
    else if (n >= 2)
    {
        char *val1 = (char *)malloc((strlen(arr[0]) + 1) * sizeof(char));
        strcpy(val1, arr[0]);
        int max = intal_max(arr, 2);
        char *val2 = (char *)malloc((strlen(arr[max]) + 1) * sizeof(char));
        strcpy(val2, arr[max]);
        char *temp1, *temp2, *temp3;
        for (int i = 2; i < n; i++)
        {
            temp1 = val1;
            temp2 = val2;
            temp3 = intal_add(val1, arr[i]);
            if (intal_compare(val2, temp3) == -1)
            {
                val2 = (char *)malloc((strlen(temp3) + 1) * sizeof(char));
                strcpy(val2, temp3);
            }
            else
            {
                val2 = (char *)malloc((strlen(temp2) + 1) * sizeof(char));
                strcpy(val2, temp2);
            }
            val1 = temp2;
            free(temp1);
            free(temp3);
        }
        free(val1);
        return val2;
    }
}

//char *string_intal_pow(const char *intal1, const char *intal2)
// {
//     long int len = strlen(intal2);
//     char *power = (char *)malloc(2 * sizeof(char));
//     char *temp, *temp2;
//     strcpy(power, "1\0");
//     for (int i = 0; i < len; i++)
//     {
//         temp2 = looper(intal1, (int)(intal2[len - 1 - i]) - (int)('0'), i);
//         temp = power;
//         power = intal_multiply(temp2, power);
//         free(temp);
//         free(temp2);
//     }
//     return power;
// }

// char *looper(const char *intal1, int val, long int place)
// {
//     char *res = (char *)malloc(2 * sizeof(char));
//     char *temp, *temp2;
//     strcpy(res, "1\0");
//     if (place == 0)
//     {
//         for (int i = 0; i < val; i++)
//         {
//             temp = res;
//             res = intal_multiply(intal1, res);
//             free(temp);
//         }
//     }
//     else
//     {
//         temp2 = looper(intal1, val, place - 1);
//         for (int i = 0; i < 10; i++)
//         {
//             temp = res;
//             res = intal_multiply(temp2, res);
//             free(temp);
//         }
//         free(temp2);
//     }
//     return (res);
// }