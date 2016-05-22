#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
#define OPT
//#define OPT_2
//#define OPT_HASH
typedef struct __LAST_NANE_ENTRY entry;

#if defined(OPT)
typedef struct __PHONE_BOOK_ENTRY {
    //char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    //struct __PHONE_BOOK_ENTRY *pNext;
} detail;

struct __LAST_NANE_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *entry_detail;
    entry *pNext;
};

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);
#elif defined(OPT_HASH)

typedef struct __PHONE_BOOK_ENTRY {
    //char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    //struct __PHONE_BOOK_ENTRY *pNext;
} detail;

struct __LAST_NANE_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    detail *entry_detail;
    entry *pNext;
};

entry *findName(char lastname[], entry *e);
entry *append(char lastName[], entry *e);
int prepareHash(int size);
void printHashCnt(void);

#elif defined(OPT_2)
// use array to reduce malloc times and make dense lastname
typedef struct __PHONE_BOOK_ENTRY {
    //char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    //struct __PHONE_BOOK_ENTRY *pNext;
} detail;

#define NAME_SET 30
struct __LAST_NANE_ENTRY {
    char lastNames[NAME_SET][MAX_LAST_NAME_SIZE];
    char lastName[MAX_LAST_NAME_SIZE];
    int idx;
    detail *entry_detail;
    entry *pNext;
};

entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif

#endif
