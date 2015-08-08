#include "dlist.h"

DList DocList;

int AppendDList(DocNode *node) {
	if (!node)
		return 1;
	if (!DocList.head)
		DocList.head = node;
	else {
		DocNode *temp = DocList.head;
		while (temp != NULL) {
			temp = temp->next;
		}
		temp = node;
	}
	return 0;
