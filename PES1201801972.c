#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intal.h"

typedef struct Node
{
    int ele;
    struct Node *great;
    struct Node *less;
} Node;

typedef struct IntStore
{
    Node *msd;
    Node *lsd;
} IntStore;

static IntStore *init_intstore();
static Node *create_node(int);
static void insert_intstore(IntStore *, Node *, int);
static IntStore *string_to_intstore(char *);
static char *intstore_to_string(IntStore *);
static void free_intstore(IntStore *);
static int len_instore(IntStore *);
static char *single_multiply(char *, int, int);

IntStore *init_intstore()
{
    IntStore *istore = (IntStore *)malloc(sizeof(IntStore));
    istore->msd = NULL;
    istore->lsd = NULL;
    return istore;
}

int len_instore(IntStore *istore)
{
    Node *node = istore->lsd;
    int len = 0;
    while (node)
    {
        node = node->great;
        len++;
    }
    return len;
}

void free_intstore(IntStore *istore)
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

Node *create_node(int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->ele = val;
    node->great = NULL;
    node->less = NULL;
    return node;
}

void insert_intstore(IntStore *istore, Node *node, int pos)
{
    if (istore->lsd == NULL && istore->msd == NULL)
    {
        istore->lsd = node;
        istore->msd = node;
    }
    else if (pos == -1)
    {
        node->less = istore->msd;
        istore->msd = node;
        if (node->less)
            node->less->great = node;
    }
    else if (pos == 0)
    {
        node->great = istore->lsd;
        istore->lsd = node;
        if (node->great)
            node->great->less = node;
    }
    else
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
    }
}

IntStore *string_to_intstore(char *intal1)
{
    int len = strlen(intal1);
    IntStore *istore = init_intstore();
    int j = 0;
    while (j < len && intal1[j] == '0')
    {
        j++;
    }
    for (int i = j; i < len; i++)
    {
        Node *node = create_node((int)(intal1[i]) - (int)('0'));
        insert_intstore(istore, node, 0);
    }
    return istore;
}

char *intstore_to_string(IntStore *istore)
{
    Node *node = istore->msd;
    while (node && node->ele == 0)
    {
        node = node->less;
    }
    Node *nodecopy = node;
    int len = 0;
    while (node)
    {
        node = node->less;
        len++;
    }
    char *s = malloc(101 * sizeof(char));
    if (len != 0)
    {
        for (int i = 0; i < len; i++)
        {
            s[i] = (char)(nodecopy->ele + (int)('0'));
            nodecopy = nodecopy->less;
        }
        s[len] = '\0';
    }
    else
    {
        strcpy(s, "0\0");
    }
    return (s);
}

char *intal_add(char *intal1, char *intal2)
{
    IntStore *istore1 = string_to_intstore(intal1);
    IntStore *istore2 = string_to_intstore(intal2);
    IntStore *sumstore = init_intstore();
    int carry = 0;
    Node *node1 = istore1->lsd;
    Node *node2 = istore2->lsd;
    while (node1 && node2)
    {
        Node *new = create_node((node1->ele + node2->ele + carry) % 10);
        carry = (node1->ele + node2->ele + carry) / 10;
        node1 = node1->great;
        node2 = node2->great;
        insert_intstore(sumstore, new, -1);
    }
    while (node1)
    {
        Node *new = create_node((node1->ele + carry) % 10);
        carry = 0;
        node1 = node1->great;
        insert_intstore(sumstore, new, -1);
    }
    while (node2)
    {
        Node *new = create_node((node2->ele + carry) % 10);
        carry = 0;
        node2 = node2->great;
        insert_intstore(sumstore, new, -1);
    }
    if(carry)
    {
        Node *new = create_node(carry % 10);
        insert_intstore(sumstore, new, -1);        
    }
    Node* n=sumstore->lsd;
    char *c = intstore_to_string(sumstore);
    free_intstore(sumstore);
    free_intstore(istore1);
    free_intstore(istore2);
    return (c);
}

int intal_compare(char *intal1, char *intal2)
{
    IntStore *istore1 = string_to_intstore(intal1);
    IntStore *istore2 = string_to_intstore(intal2);
    int l1 = len_instore(istore1);
    int l2 = len_instore(istore2);
    if (l1 > l2)
    {
        return 1;
    }
    else if (l1 < l2)
    {
        return -1;
    }
    else
    {
        Node *n1 = istore1->msd;
        Node *n2 = istore2->msd;
        while (n1 && n2)
        {
            if (n1->ele > n2->ele)
                return 1;
            else if (n1->ele < n2->ele)
                return -1;
            n1 = n1->less;
            n2 = n2->less;
        }
        free_intstore(istore1);
        free_intstore(istore2);
        return 0;
    }
}

char *intal_diff(char *intal1, char *intal2)
{
    IntStore *istore1;
    IntStore *istore2;
    int cmp = intal_compare(intal1, intal2);
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
    else
    {
        char *s;
        strcpy(s, "0\0");
        return s;
    }
    Node *n1 = istore1->lsd;
    Node *n2 = istore2->lsd;
    while (n1 && n2)
    {
        n1->ele -= n2->ele;
        if (n1->ele < 0)
        {
            n1->ele += 10;
            if (n1->great)
                n1->great->ele--;
        }
        n1 = n1->great;
        n2 = n2->great;
    }
    while (n1 && n1->ele < 0)
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

char *single_multiply(char *intal1, int n, int offset)
{
    IntStore *istore1 = string_to_intstore(intal1);
    Node *n1 = istore1->lsd;
    long int carry = 0;
    while (n1)
    {
        int old_ele = n1->ele;
        n1->ele = (old_ele * n + carry) % 10;
        carry = (old_ele * n + carry) / 10;
        n1 = n1->great;
    }
    while (carry)
    {
        Node *node = create_node(carry % 10);
        insert_intstore(istore1, node, -1);
        carry /= 10;
    }
    for (int i = 0; i < offset; i++)
    {
        Node *node = create_node(0);
        insert_intstore(istore1, node, 0);
    }
    char *s = intstore_to_string(istore1);
    free_intstore(istore1);
    return s;
}

char *intal_multiply(char *intal1, char *intal2)
{
    IntStore *istore2 = string_to_intstore(intal2);
    char *product = malloc(100 * sizeof(char));
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
    return product;
}

char *intal_mod(char *intal1, char *intal2)
{
    while (intal_compare(intal1, intal2) != -1)
    {
        intal1 = intal_diff(intal1, intal2);
    }
    return intal1;
}

char* intal_fibonacci(unsigned int n)
{
    char *s1=(char*)malloc(100*sizeof(char));
    char *s2=(char*)malloc(100*sizeof(char));
    char* s3;
    strcpy(s1,"0\0");
    strcpy(s2,"1\0");
    if(n==1)
    {
        free(s2);
        return s1;
    }
    else if(n==2)
    {
        free(s1);
        return s2;
    }
    else
    {
        for(int i=3;i<=n;i++)
        {
            s3=intal_add(s1,s2);
            free(s1);
            s1=s2;
            s2=s3;
        }
        free(s1);
        return s3;
    }    
}