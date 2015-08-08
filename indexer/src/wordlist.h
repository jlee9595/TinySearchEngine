#ifndef WLIST_H
#define WLIST_H

typedef struct WordNode {
	struct WordNode *next;
	char *word;
	DocumentNode *page;
} WordNode;

typedef struct WList {
	WordNode *head;
} WList;

extern WordList;

int AppendWList(WordNode *node);
#endif // WLIST_H
