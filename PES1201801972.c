#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intal.h"
#include <limits.h>

//code tested on valgrind, no memory errors or memory leaks found

typedef struct Node //node structure of double linked list
{
    int ele;
    struct Node *great; //successive digit
    struct Node *less;  //predecessive digit
} Node;

typedef struct IntStore //head structure of doubly linked list
{
    Node *msd; //most significant digit
    Node *lsd; //least significant digit
} IntStore;

static IntStore *init_intstore();                                      //initialise DLL
static Node *create_node(int);                                         //create node for DLL
static void insert_intstore(IntStore *, Node *, int);                  //insert node into DLL
static IntStore *string_to_intstore(const char *);                     //Intal string to DLL
static char *intstore_to_string(IntStore *);                           //DLL to Intal string
static void free_intstore(IntStore *);                                 //freeing DLL
static int len_instore(IntStore *);                                    //len of intal number
static char *single_multiply(const char *, int, int);                  //multiply an intal_string with single digit integer
static void mergesort(char **, int, int);                              //mergesort for recursion
static void merge_sortedhalves(char **, int, int, int);                //merging function for mergesort
static char *rec_intal_bincoeff(unsigned int, unsigned int, char ***); //recursive function for binary coefficient
static char *mallcopy(const char *source);

static char *mallcopy(const char *source) //mallocs memory and copies string to it
{
    char *dest = (char *)malloc((strlen(source) + 1) * sizeof(char));
    strcpy(dest, source);
    return dest;
}

IntStore *init_intstore() //initialise the DLL
{
    IntStore *istore = (IntStore *)malloc(sizeof(IntStore));
    istore->msd = NULL;
    istore->lsd = NULL;
    return istore;
}

int len_instore(IntStore *istore) //to fing length of Intal number
{
    Node *node = istore->lsd;
    int len = 0;
    while (node) //traversing DLL to find the length
    {
        node = node->great;
        len++;
    }
    return len;
}

void free_intstore(IntStore *istore) //freeing the DLL
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

Node *create_node(int val) //creating a node for a digit
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->ele = val;
    node->great = NULL;
    node->less = NULL;
    return node;
}

void insert_intstore(IntStore *istore, Node *node, int pos) //insert a digit node into IntStore DLL
{
    if (istore->lsd == NULL && istore->msd == NULL)
    {
        istore->lsd = node;
        istore->msd = node;
    }
    else if (pos == -1) //if pos==-1, insert at msd side
    {
        node->less = istore->msd;
        istore->msd = node;
        if (node->less)
            node->less->great = node;
    }
    else if (pos == 0) //if pos==0, insert at lsd side
    {
        node->great = istore->lsd;
        istore->lsd = node;
        if (node->great)
            node->great->less = node;
    }
    else //insert at nth position
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
    } //wrong inputs of pos not taken care of, as this function is called only internally
}

IntStore *string_to_intstore(const char *intal1) //convert string to DLL
{
    int len = strlen(intal1);
    IntStore *istore = init_intstore();
    int j = 0;
    while (j < len && intal1[j] == '0') //stripping zeros on the msb side
    {
        j++;
    }
    for (int i = j; i < len; i++) //inserting nodes
    {
        Node *node = create_node((int)(intal1[i]) - (int)('0'));
        insert_intstore(istore, node, 0);
    }
    return istore;
}

char *intstore_to_string(IntStore *istore) //convert DLL to string
{
    Node *node = istore->msd;
    while (node && node->ele == 0)
    {
        node = node->less;
    } //stripping zeros if present (most unlikely)
    Node *nodecopy = node;
    int len = 0;
    while (node) //determining length of the string
    {
        node = node->less;
        len++;
    }
    char *s;
    if (len != 0)
    {
        s = (char *)malloc((len + 1) * sizeof(char));
        for (int i = 0; i < len && nodecopy; i++)
        {
            s[i] = (char)(nodecopy->ele + (int)('0'));
            nodecopy = nodecopy->less;
        }
        s[len] = '\0';
    }
    else //if len=0, then 0 must be stored
    {
        s = mallcopy("0\0");
    }
    return (s);
}

char *intal_add(const char *intal1, const char *intal2)
{
    IntStore *istore1 = string_to_intstore(intal1); //generate IntStore DLL's
    IntStore *istore2 = string_to_intstore(intal2);
    IntStore *sumstore = init_intstore(); //for storing sum
    int carry = 0;
    Node *node1 = istore1->lsd;
    Node *node2 = istore2->lsd;
    while (node1 && node2) //while both node exists from lsd side
    {
        Node *new = create_node((node1->ele + node2->ele + carry) % 10); //single digit at its position
        carry = (node1->ele + node2->ele + carry) / 10;                  //carry
        node1 = node1->great;
        node2 = node2->great;
        insert_intstore(sumstore, new, -1);
    }
    while (node1) //when only node1 exists(when intal1 is longer than intal2)
    {
        Node *new = create_node((node1->ele + carry) % 10);
        carry = (node1->ele + carry) / 10;
        node1 = node1->great;
        insert_intstore(sumstore, new, -1);
    }
    while (node2) //when only node2 exists(when intal2 is longer than intal1)
    {
        Node *new = create_node((node2->ele + carry) % 10);
        carry = (node2->ele + carry) / 10;
        node2 = node2->great;
        insert_intstore(sumstore, new, -1);
    }
    if (carry) // if carry still resides
    {
        Node *new = create_node(carry % 10);
        insert_intstore(sumstore, new, -1);
    }
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
    if (l1 != l2) //if there exists a difference in the length, then result can be concluded immediately
    {
        free_intstore(istore1);
        free_intstore(istore2);
        if (l1 > l2)
            return 1;
        else
            return -1;
    }
    else //if length is same for both the strings
    {
        Node *n1 = istore1->msd;
        Node *n2 = istore2->msd;
        int val = 0;
        while (n1 && n2) //traverse from msd side
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
        } //if both are equal
        free_intstore(istore1);
        free_intstore(istore2);
        return val;
    }
}

char *intal_diff(const char *intal1, const char *intal2)
{
    IntStore *istore1;
    IntStore *istore2;
    int cmp = intal_compare(intal1, intal2); //to decide which string is greater
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
    else //if both are equal
    {
        return mallcopy("0\0");
    }
    Node *n1 = istore1->lsd;
    Node *n2 = istore2->lsd;
    while (n1 && n2) //difference is calculated and stored in istore2
    {
        n1->ele -= n2->ele;
        if (n1->ele < 0)
        {
            n1->ele += 10;
            if (n1->great) //borrow from successor
                n1->great->ele--;
        }
        n1 = n1->great;
        n2 = n2->great;
    }
    while (n1 && n1->ele < 0) //to neutralise the negative borrows stored in the DLL
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

char *single_multiply(const char *intal1, int n, int offset) //multiply a intal string with integers, offset is a parameter used to multiply by 10^offset
{
    IntStore *istore1 = string_to_intstore(intal1);
    Node *n1 = istore1->lsd;
    long int carry = 0;
    while (n1) //similar to addition, the carry is passed on
    {
        int old_ele = n1->ele;
        n1->ele = (old_ele * n + carry) % 10;
        carry = (old_ele * n + carry) / 10;
        n1 = n1->great;
    }
    while (carry) //adding nodes, till carry prevails
    {
        Node *node = create_node(carry % 10);
        insert_intstore(istore1, node, -1);
        carry /= 10;
    }
    for (int i = 0; i < offset; i++) //inserting zeros, offset enables result=result*(10^offset), used in mod to increase efficiency
    {
        Node *node = create_node(0);
        insert_intstore(istore1, node, 0);
    }
    char *s = intstore_to_string(istore1);
    free_intstore(istore1);
    return s;
}

char *intal_multiply(const char *intal1, const char *intal2) //multiply  2 intal strings
{
    IntStore *istore2 = string_to_intstore(intal2);
    char *product = mallcopy("0\0"); //this pointer stores the product, initialised to 0
    long int count = 0;
    Node *n2 = istore2->lsd;
    while (n2)
    {
        char *s2 = single_multiply(intal1, n2->ele, count++); //multiply intal1 with each digit of intal2 with an offset count
        char *temp = product;
        product = intal_add(s2, product); //add the intermediate product with the resultant
        free(s2);
        free(temp);
        n2 = n2->great;
    }
    free_intstore(istore2); //freeing the DLL
    return product;
}

char *intal_mod(const char *intal1, const char *intal2)
{
    //here, i have implemented another method to improve the efficiency of mod
    IntStore *istore1 = string_to_intstore(intal1); //creating the IntStore DLL for the strings
    IntStore *istore2 = string_to_intstore(intal2); //the reason this is created is a safety to strip zeros at the msd side
    char *i1 = intstore_to_string(istore1);
    char *i2 = intstore_to_string(istore2);
    free_intstore(istore1);
    free_intstore(istore2);
    int len;
    while (intal_compare(i1, i2) != -1)
    {
        //here,  0 is append to the smaller number until its 'just' smaller than number ('just'-an additional append shall result in a greater number)
        //Regarding this approach, we had mailed to you, and you had validated this approach.
        if (i1[0] > i2[0])                 //to check whether the msd of intal1 number is greater than msd of intal2
            len = strlen(i1) - strlen(i2); //len given the number of zeros that can be appended
        else
            len = strlen(i1) - strlen(i2) - 1;
        if (len < 0)
            len = 0;
        char *temp = single_multiply(i2, 1, len); //here, appending zeros is a very efficient operation, as single_multiply takes 'offset' parameter
        char *temp2 = i1;
        i1 = intal_diff(i1, temp); //now subtraction of this modified number is done
        free(temp);
        free(temp2);
    }
    free(i2);
    return i1;
}

char *intal_fibonacci(unsigned int n)
{
    char *s1 = mallcopy("0\0");
    char *s2 = mallcopy("1\0");
    char *s3;
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
    else //fibonacci with constant memory dynamic programming
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

char *intal_factorial(unsigned int n) // calls the power function
{
    char *s = mallcopy("1\0");
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
    char *i1 = mallcopy(intal1); //intal1 and intal2 is copied
    char *i2 = mallcopy(intal2); //this helps to free unwanted memory iteratively in a cleaner fashion
    char *zero = mallcopy("0\0");
    char *temp;
    while (intal_compare(i1, zero) == 1 && intal_compare(i2, zero) == 1) //loop proceedes when intal1 and intal2 are greater than zero
    {
        if (intal_compare(i1, i2) >= 0) //euclids method by finding greater number mod smaller number
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
    if (intal_compare(i1, zero)) //if one of them is zero, then the other shall be the gcd
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

int intal_max(char **arr, int n) //traversing the array of pointers and finding the index
{
    int max_ind = 0;
    for (int i = 1; i < n; i++)
    {
        if (intal_compare(arr[i], arr[max_ind]) == 1)
            max_ind = i;
    }
    return max_ind;
}

int intal_min(char **arr, int n) // similar to intal_max
{
    int min_ind = 0;
    for (int i = 1; i < n; i++)
    {
        if (intal_compare(arr[i], arr[min_ind]) == -1)
            min_ind = i;
    }
    return min_ind;
}

int intal_search(char **arr, int n, const char *key) //linear search by traversing
{
    for (int i = 0; i < n; i++)
    {
        if (!intal_compare(arr[i], key))
            return i;
    }
    return -1;
}

int intal_binsearch(char **arr, int n, const char *key) //binary search of sorted array
{
    int lower = 0;
    int higher = n - 1;
    while (higher >= lower) //similar to binary search with integers
    {
        int mid = (lower + higher) / 2;
        if (intal_compare(arr[mid], key) == -1)
        {
            lower = mid + 1;
        }
        else if (intal_compare(arr[mid], key) == 1 || (mid > 0 && intal_compare(arr[mid - 1], key) == 0)) //inorder to find 1st occurence of key
        {                                                                                                 //if previous of mid is same as key, then the binary search should proceed towards the lower direction
            higher = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

void intal_sort(char **arr, int n) //sorts using merge sort
{
    mergesort(arr, 0, n - 1); // a recursive function
}

void mergesort(char **a, int start, int end) //takes in start and end parameters. It performs splitting array into fragments
{
    if (start - end) //while there exists an element
    {
        mergesort(a, start, (start + end) / 2);                   //first component after split
        mergesort(a, (start + end) / 2 + 1, end);                 //second component after split
        merge_sortedhalves(a, start, (start + end) / 2 + 1, end); //merging the halves
    }
}

void merge_sortedhalves(char **a, int start, int mid, int end) //merges to components
{
    int i = start;
    int j = mid;
    int pos = 0;
    char *b[end - start + 1];   //new array just to merge
    while (i < mid && j <= end) //merging
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
    while (i < mid) //filling with left out elements in component 1
    {
        b[pos++] = a[i++];
    }
    while (j < pos) //filling with left out elements in component 2
    {
        b[pos++] = a[j++];
    }
    for (int i = 0; i < pos; i++) //re-filling the elements into the array
    {
        a[start + i] = b[i];
    }
}

char *intal_bincoeff(unsigned int n, unsigned int k)
{
    char** strip=(char**)malloc((k+1)*sizeof(char*)); //dynamic memory array O(k)
    for(long int i=0;i<=k;i++)
    {
        strip[i]=mallcopy("1\0");//initialised to 1
    }
    for(long int i=1;i<=(long int)n-(long int)k;i++)
    {
        for(long int j=1;j<=k;j++)
        {
            char* temp=strip[j];               
            strip[j]=intal_add(strip[j],strip[j-1]);            
            free(temp);           
        }
    }
    char* res=mallcopy(strip[k]);
    for(long int i=0;i<=k;i++)
    {
        free(strip[i]);
    }    
    free(strip);
    return res;
}

char *intal_pow(const char *intal1, unsigned int n) //power
{
    if (n == 0) //if n==0,returns 1
    {
        return mallcopy("1\0");
    }
    else
    {
        char *temp = intal_pow(intal1, n / 2); //stores this value instead of calling this function twice in multiply
        char *res, *temp3;
        if (n % 2 == 0) // if n is even
        {
            res = intal_multiply(temp, temp);
        }
        else //if n is odd
        {
            temp3 = intal_multiply(temp, temp);
            res = intal_multiply(temp3, intal1);
            free(temp3);
        }
        free(temp);
        return res;
    }
}

char *coin_row_problem(char **arr, int n) //memory O(1)
{
    if (n == 1) //if there exists only 1 coin
    {
        return mallcopy(arr[0]);
    }
    else if (n > 1)
    {
        char *val1 = mallcopy(arr[0]); //max value for arr[0]
        int max = intal_max(arr, 2);
        char *val2 = mallcopy(arr[max]); //max value for arr[0 to 1]
        char *temp1, *temp2, *temp3;     //pointers to store intermediate values
        //val1 and val2 are the pointers which store the values of dynamic programming
        for (int i = 2; i < n; i++)
        {
            temp1 = val1;
            temp2 = val2;
            temp3 = intal_add(val1, arr[i]);      //arr[i] + coin_row_problem(arr,i-2) where i is present index
            if (intal_compare(val2, temp3) == -1) //val2=max(arr[i] + coin_row_problem(arr,i-2),coin_row_problem(arr,i-1))
            {
                val2 = (char *)malloc((strlen(temp3) + 1) * sizeof(char));
                strcpy(val2, temp3);
            }
            else
            {
                val2 = (char *)malloc((strlen(temp2) + 1) * sizeof(char));
                strcpy(val2, temp2);
            }
            val1 = temp2; //freeing intermediate values
            free(temp1);
            free(temp3);
        }
        free(val1);
        return val2;
    }
    else
    {
        return NULL;
    }
}