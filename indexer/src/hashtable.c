/* ========================================================================== */
/* File: hashtable.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Crawler
 *
 * Author:
 * Date:
 *
 * You should include in this file your functionality for the hashtable as
 * described in the assignment and lecture.
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// ---------------- Local includes  e.g., "file.h"
#include "hashtable.h"                       // hashtable functionality

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types


// ---------------- Private variables

// ---------------- Public variables
//HashTable WordsFound;


// ---------------- Private prototypes



unsigned long JenkinsHash(const char *str, unsigned long mod)
{
    size_t len = strlen(str);
    unsigned long hash, i;

    for(hash = i = 0; i < len; ++i)
    {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % mod;
}

// Add the input URL to the hash table
int AddToHashTable(char *word, HashTable *WordsFound) {
	HashTableNode *node;
	if ((node = calloc(1, sizeof(HashTableNode))) == NULL) {
		return 1;
	}
	node->word = word;
	unsigned long hashIndex = JenkinsHash(word, MAX_HASH_SLOT);
	
	HashTableNode *currentNode;
	currentNode = WordsFound->table[hashIndex];
	if (currentNode == NULL) {
		WordsFound->table[hashIndex] = node;
	}
	else {
		while (currentNode->next != NULL) {
		currentNode = currentNode->next;
		}
	currentNode->next = node;
	}
	return 0;
}

int UpdateHashTable(char *word, int DocumentId, HashTable *WordsFound) {
	HashTableNode *node = WordsFound->table[JenkinsHash(word, MAX_HASH_SLOT)];

	//Find the node in the slot
	while (strcmp(node->word, word) != 0) {
		node = node->next;
	}
	DocumentNode *currentDocNode = node->page;
	
	//if the node doesn't have a docnode yet then make one
	if (currentDocNode == NULL) {					
		DocumentNode *newDocNode = calloc(1, sizeof(DocumentNode));
		newDocNode->doc_id = DocumentId;
		newDocNode->freq = 1;
		node->page = newDocNode;
		return 0;
	}

	//Go through each docnode until the right one is found and increment its freq
	while ( currentDocNode->next != NULL ) {
		if (currentDocNode->doc_id == DocumentId) {
			currentDocNode->freq++;
			return 0;
		}
		currentDocNode = currentDocNode->next;
	}
	
	//Check the last one as well because the while loop didn't reach it
	if (currentDocNode->doc_id == DocumentId) {
		currentDocNode->freq++;
		return 0;
	}

	//If the node had a docnode list and the doc wasn't in there then make a new one
	DocumentNode *newDocNode = calloc(1, sizeof(DocumentNode));
	newDocNode->doc_id = DocumentId;
	newDocNode->freq = 1;
	currentDocNode->next = newDocNode;
	return 1;
}
	

//Check if the input url is inside the Hash Table
int InHashTable(char *word, HashTable *WordsFound) {
	unsigned long bucket = JenkinsHash(word, MAX_HASH_SLOT);
	HashTableNode *currentNode;
	currentNode = WordsFound->table[bucket];
	while (currentNode != NULL) {
		if (strcmp(currentNode->word, word) == 0) {
			return 1;
		}
		currentNode = currentNode->next;
	}
	return 0;
}


// Free the memory allocated to the hash table nodes
int FreeHashTable(HashTable *WordsFound) {
	int currentBucket = 0;

	//Go through all the hash slots
	while (currentBucket <  MAX_HASH_SLOT) {
		HashTableNode *currentNode = WordsFound->table[currentBucket];
		
		//Go through all the nodes in the slot
		while (currentNode != NULL) {
			HashTableNode *tempNode = currentNode;
			currentNode = currentNode->next;
			DocumentNode* currentDocNode = tempNode->page;

			//Go through all the document nodes in the node
			while (currentDocNode != NULL) {
				DocumentNode *tempDocNode = currentDocNode;
				currentDocNode = currentDocNode->next;
				free(tempDocNode);
			}
			free(tempNode->word);
			free(tempNode);	
		}
		currentBucket++;
	}
	free(WordsFound);
	return 0;
}

//int main() {
//	AddToHashTable("dartmouth.edu");
//	if (InHashTable("dartmouth.edu") == 1) {
//		printf("Yes");
//	}
//	printf("%s", URLsVisited.table[JenkinsHash("dartmouth.edu", MAX_HASH_SLOT)]->url);
//	return 0;
//}
