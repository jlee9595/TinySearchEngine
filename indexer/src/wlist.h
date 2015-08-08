#ifndef WORDLIST_H
#define WORDLIST_H

typedef struct WordNode {
	struct WordNode *next;
	char *word;
	DocumentNode *doc;
} WordNode;

typedef struct WList {
	WordNode *head
} WList;

extern WordList
#endif // WORDLIST_H
