/* ========================================================================== */
/* File: list.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * This file contains the definitions for a doubly-linked list of WebPages.
 *
 */
/* ========================================================================== */
#ifndef LIST_H
#define LIST_H

// ---------------- Prerequisites e.g., Requires "math.h"

// ---------------- Constants

// ---------------- Structures/Types

typedef struct ListNode {
    int doc_id;
	int score;                           // the data for a given page
    struct ListNode *prev;                   // pointer to previous node
    struct ListNode *next;                   // pointer to next node
} ListNode;

typedef struct List {
    ListNode *head;                          // "beginning" of the list
    ListNode *tail;                          // "end" of the list
} List;

// ---------------- Public Variables

// ---------------- Prototypes/Macros
int AppendList(int doc_id, List *URLList);
int PopList(int doc_id, List *URLList);
#endif // LIST_H
