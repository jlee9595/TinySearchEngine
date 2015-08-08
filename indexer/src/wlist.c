#include "wlist.h"

WList WordList;

int AppendWList(WordNode *node) {
	if (!node)
		return 1;
	if (!WordList.head)
		WordList.head = node;
	else {
		WordNode *temp = WordList.head;
		while (temp != NULL) {
			temp = temp->next;
		}
		temp = node;
	}
	return 0;
