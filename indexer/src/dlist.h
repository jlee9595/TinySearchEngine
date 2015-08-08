#ifndef DLIST_H
#define DLIST_H

typedef struct DocNode {
	struct DocNode *next;
	int doc_id;
	int freq;
} DocNode;

typedef struct DList {
	DocNode *head;
} DList;

extern DList DocList;

int AppendDList(DocNode *node);
#endif // DLIST_H
