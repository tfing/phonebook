#include <stdlib.h>
#include <string.h>
#include "stdio.h"
#include "phonebook_opt.h"

#ifdef OPT

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}
#elif defined(OPT_HASH)

static entry** hash_p = NULL;
static int *hash_cnt = NULL;
static int hash_size = 0;
int prepareHash(int size)
{
    hash_cnt = (int*)malloc(sizeof(int)*size);
    hash_p = (entry**)malloc(sizeof(entry*)*size);
    if (hash_p == NULL) {
        return -1;
    }
    memset(hash_p, 0, sizeof(entry*)*size);
    memset(hash_cnt, 0, sizeof(int)*size);
    hash_size = size;
    return 0;
}

static unsigned int hashIndex(char lastName[])
{
    char *c = lastName;
    unsigned int hash = 0;
    while (*c != 0) {
        hash = (hash << 5) + *c;
        c = c+1;
    }

    return hash % hash_size;
}

entry *append(char lastName[], entry *not_used)
{
    unsigned int idx;
    entry *e = NULL;
    entry **head = NULL;

    // calc hash index
    idx = hashIndex(lastName);
    head = &hash_p[idx];
    // link on the head on hash_p[index]
    e = (entry *) malloc(sizeof(entry));
    strcpy(e->lastName, lastName);
    if (*head == 0) {
        e->pNext = NULL;
    } else {
        e->pNext = *head;
    }
    *head = e;

    return e;
}

entry *findName(char lastname[], entry *pHead)
{
    unsigned int idx = hashIndex(lastname);
    pHead = hash_p[idx];

    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

#include <stdlib.h>
int cmp(const void*a, const void*b)
{
    return (*(int*) a - *(int*)b);
}

void printHashCnt(void)
{
    int i;
    entry *pHead;
    for (i = 0; i < hash_size; i++) {
        pHead = hash_p[i];
        while (pHead != NULL) {
            hash_cnt[i]++;
            pHead = pHead->pNext;
        }
    }
    qsort(hash_cnt, hash_size, sizeof(int), cmp);

    for (i = 0; i < hash_size; i++) {
        printf("%d\n", hash_cnt[i]);
    }

}


#elif defined(OPT_2)

entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        int  idx = 0;
        while (idx != NAME_SET) {
            if (strcasecmp(lastname, pHead->lastNames[idx]) == 0) {
                strcpy(pHead->lastName,pHead->lastNames[idx]);
                return pHead;
            }
            idx++;
        }
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e)
{
    if (e->idx == NAME_SET) {
        e->pNext = (entry *) malloc(sizeof(entry));
        e = e->pNext;
        e->idx = 0;
    }
    strcpy(e->lastNames[e->idx], lastName);
    e->idx++;

    return e;
}

#endif
