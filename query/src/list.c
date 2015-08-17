/* File: list.c
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * This file contains the implementation of the functions in list.h
 *
 */

#include <stdlib.h>
#include <stdio.h>
//#include "list.h"
#include "list.h"



int AppendList(int doc_id, List *URLList) {
	ListNode *node;

	//check if the page is valid

	node = calloc(1, sizeof(ListNode));
	if (!node)
		return 0;

	node->doc_id = doc_id;
	node->score = 0;

	if (!URLList->tail) {
		URLList->tail = node;
		URLList->head = node;
	}
	
	else {
		URLList->tail->next = node;
		node->prev = URLList->tail;
		URLList->tail = node;
	}

	return 1;
}

//Remove a webpage from the list
//free(web->url);
//free(web->html);
//free(web)
int PopList(int doc_id, List *URLList) {
	
	//check if the list is empty
	if (!URLList->head)
		return NULL;

	ListNode *currentNode = URLList->head;
	while (currentNode != NULL) {
		if (currentNode->doc_id == doc_id) {
			break;
		}
		currentNode = currentNode->next;
	}
	//if the node is the head
	if (currentNode->doc_id == URLList->head->doc_id) {
	

		URLList->head = currentNode->next;	//assign new head

		if (!URLList->head)
			URLList->tail = NULL;

		if (URLList->head)
			URLList->head->prev = NULL;
		free(currentNode);
	}
	
	else if (currentNode->doc_id == URLList->tail->doc_id) {
		URLList->tail = currentNode->prev;

		if (!URLList->tail)
			URLList->head = NULL;

		if (URLList->tail)
			URLList->tail->next = NULL;
		free(currentNode);
	}

	else {
		currentNode->prev->next = currentNode->next;
		currentNode->next->prev = currentNode->prev;
		free(currentNode);
	}

	return 1;
}

//int main() {
//	WebPage *page;
//	page = calloc(1, sizeof(WebPage));
//	page->url = "dartmouth.edu";
//	if (!URLList.head)
//                printf("List is empty");
//	AppendList(page);
//	if (!URLList.head)
//                printf("List is empty");
//	printf("%s", URLList.tail->page->url);
//	
//	PopList();
//	if (!URLList.head)
//		printf("List is empty");
//}
