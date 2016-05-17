#include <stdlib.h>

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
#elif defined(OPT_2)

entry *findName(char lastname[], entry *pHead)
{
    while (pHead != NULL) {
        char idx = 0;
        while (idx != NAME_SET)
        {
        if (strcasecmp(lastname, pHead->lastNames[idx]) == 0)
        {
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
    if (e->idx == NAME_SET)
    {
        e->pNext = (entry *) malloc(sizeof(entry));
        e = e->pNext;
        e->idx = 0;
    }
    strcpy(e->lastNames[e->idx], lastName);
    e->idx++;

    return e;
} 

#endif
