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
//#include "hashtable.h"
//#include "invertedIndex.h"
#include "invertedIndex.h"
#include "hashtable.h"

// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types


// ---------------- Private variables

// ---------------- Public variables
//InvertedIndex WordsFound;


// ---------------- Private prototypes



// Add the input URL to the hash table
int AddToInvertedIndex(char *word, InvertedIndex *WordsFound) {
	InvertedIndexNode *node;
	if ((node = calloc(1, sizeof(InvertedIndexNode))) == NULL) {
		return 1;
	}
	node->word = word;
	unsigned long hashIndex = JenkinsHash(word, MAX_HASH_SLOT);
	
	InvertedIndexNode *currentNode;
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

int UpdateInvertedIndex(char *word, int DocumentId, InvertedIndex *WordsFound) {
	InvertedIndexNode *node = WordsFound->table[JenkinsHash(word, MAX_HASH_SLOT)];

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
int InInvertedIndex(char *word, InvertedIndex *WordsFound) {
	unsigned long bucket = JenkinsHash(word, MAX_HASH_SLOT);
	InvertedIndexNode *currentNode;
	currentNode = WordsFound->table[bucket];
	while (currentNode != NULL) {
		if (strcmp(currentNode->word, word) == 0) {
			return 1;
		}
		currentNode = currentNode->next;
	}
	return 0;
}


//Reads an inverted index file and recreates the data structure it represents
InvertedIndex *ReadFile(char *file) {
	InvertedIndex *reloadedIndex = calloc(1, sizeof(InvertedIndex));			//allocate new index
	FILE *fp;

	fp = fopen(file, "r");								//open the input file
	char *line = calloc(100000, sizeof(char));

	//read the file line by line, parsing each line for the word, docids and freqs
	while (fgets(line, INT_MAX, fp) != NULL) {					
		line = strtok(line, "\n");
		char *token;
		char *word = calloc(100, sizeof(char));	
		token = strtok(line, " ");
		strcpy(word, token);
		token = strtok(NULL, " ");
		token = strtok(NULL, " ");
		
		//once word has been parsed and doccount has been skipped, start reading the docids and freqs until the end of the line
		while (token != NULL) {
			int doc_id = atoi(token);
			token = strtok(NULL, " ");
			int freq = atoi(token);
			int i = 0;
			
			//increment the frequency as many times as needed
			while (i < freq) {
				if (InInvertedIndex(word, reloadedIndex) == 0) {
					AddToInvertedIndex(word, reloadedIndex);
					UpdateInvertedIndex(word, doc_id, reloadedIndex);
				}
				else {
					UpdateInvertedIndex(word, doc_id, reloadedIndex);
				}
				i++;
			}
			token = strtok(NULL, " ");
		}
		free(token);
	}
	free(line);
	fclose(fp);	
	return reloadedIndex;	
}

// Free the memory allocated to the hash table nodes
int FreeInvertedIndex(InvertedIndex *WordsFound) {
	int currentBucket = 0;

	//Go through all the hash slots
	while (currentBucket <  MAX_HASH_SLOT) {
		InvertedIndexNode *currentNode = WordsFound->table[currentBucket];
		
		//Go through all the nodes in the slot
		while (currentNode != NULL) {
			InvertedIndexNode *tempNode = currentNode;
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
//	AddToInvertedIndex("dartmouth.edu");
//	if (InInvertedIndex("dartmouth.edu") == 1) {
//		printf("Yes");
//	}
//	printf("%s", URLsVisited.table[JenkinsHash("dartmouth.edu", MAX_HASH_SLOT)]->url);
//	return 0;
//}
