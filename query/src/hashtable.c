/* ========================================================================== */
/* File: hashtable.c
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Query
 *
 * Author: Justin Lee
 *
 * Description: Contains functionality for hashtable used for Query
 */
/* ========================================================================== */

// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <string.h>                          // strlen
#include <stdlib.h>
#include <stdio.h>

// ---------------- Local includes  e.g., "file.h"
//#include "common.h"                          // common functionality
//#include "hashtable.h"                       // hashtable functionality

#include "hashtable.h"

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
int AddToHashTable(char *URL, HashTable URLsVisited) {
	HashTableNode *node;
	if ((node = calloc(1, sizeof(HashTableNode))) == NULL) {
		return 1;
	}
	node->url = URL;
	unsigned long hashIndex = JenkinsHash(URL, MAX_HASH_SLOT);
	
	HashTableNode *currentNode;
	currentNode = URLsVisited.table[hashIndex];
	if (currentNode == NULL) {
		URLsVisited.table[hashIndex] = node;
	}
	else {
		while (currentNode->next != NULL) {
			currentNode = currentNode->next;
		}
		currentNode->next = node;
	}
	return 0;
}

//Check if the input url is inside the Hash Table
int InHashTable(char *URL, HashTable URLsVisited) {
	unsigned long bucket = JenkinsHash(URL, MAX_HASH_SLOT);
	HashTableNode *currentNode;
	currentNode = URLsVisited.table[bucket];
	while (currentNode != NULL) {
		if (strcmp(currentNode->url, URL) == 0) {
			return 1;
		}
		currentNode = currentNode->next;
	}
	return 0;
}

// Free the memory allocated to the hash table nodes
int FreeHashTable(HashTable URLsVisited) {
	int currentBucket = 0;
	while (currentBucket <=  MAX_HASH_SLOT) {
		HashTableNode *currentNode = URLsVisited.table[currentBucket];
		while (currentNode != NULL) {
			//HashTableNode *tempNode = currentNode;
			currentNode = currentNode->next;
			//free(tempNode);	
		}
		currentBucket++;
	}
	return 0;
}

