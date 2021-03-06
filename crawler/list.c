/* File: list.c
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * Author: Justin Lee
 *
 * This file contains the implementation of the functions in list.h
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"



List URLList;

int AppendList(WebPage *page) {
	ListNode *node;

	//check if the page is valid
	if (!page)
		return 0;

	node = calloc(1, sizeof(ListNode));
	if (!node)
		return 0;

	node->page = page;

	if (!URLList.tail) {
		URLList.tail = node;
		URLList.head = node;
	}
	
	else {
		URLList.tail->next = node;
		node->prev = URLList.tail;
		URLList.tail = node;
	}

	return 1;
}

//Remove a webpage from the list
WebPage *PopList() {
	WebPage *page;
	ListNode *tmp;
	
	//check if the list is empty
	if (!URLList.head)
		return NULL;

	tmp = URLList.head;		//store in a temporary variable
	page = tmp->page;	// get the head

	URLList.head = tmp->next;	//assign new head

	if (!URLList.head)
		URLList.tail = NULL;

	if (URLList.head)
		URLList.head->prev = NULL;
	free(tmp);
	
	return page;
}

