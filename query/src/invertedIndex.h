/* ========================================================================== */
/* File: hashtable.h
 *
 * Project name: CS50 Tiny Search Engine
 * Component name: Indexer
 *
 * This file contains the definitions for a hashtable of words.
 *
 */
/* ========================================================================== */
#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

// ---------------- Constants
#define MAX_HASH_SLOT 10000                  // number of "buckets"

// ---------------- Structures/Types

typedef struct DocumentNode {
        struct DocumentNode *next;		//pointer to  next node
        int doc_id;				// id of file
        int freq;				//frequency with which the word comes up in the file
} DocumentNode;

typedef struct InvertedIndexNode {
	char *word;				//word that the node holds
	DocumentNode *page;                     //first documentnode associated with word
    	struct InvertedIndexNode *next;             // pointer to next node
} InvertedIndexNode;


typedef struct InvertedIndex {
	InvertedIndexNode *table[MAX_HASH_SLOT];	//Inverted Index
} InvertedIndex;

// ---------------- Public Variables
//extern InvertedIndex WordsFound;


// ---------------- Prototypes/Macros

/*
 * jenkins_hash - Bob Jenkins' one_at_a_time hash function
 * @str: char buffer to hash
 * @mod: desired hash modulus
 *
 * Returns hash(str) % mod. Depends on str being null terminated.
 * Implementation details can be found at:
 *     http://www.burtleburtle.net/bob/hash/doobs.html
 */

int AddToInvertedIndex(char *word, InvertedIndex *WordsFound);

int UpdateInvertedIndex(char *word, int DocumentId, InvertedIndex *WordsFound);

int InInvertedIndex(char *word, InvertedIndex *WordsFound);

InvertedIndex *ReadFile(char *file);

int FreeInvertedIndex(InvertedIndex *WordsFound);
#endif // INVERTEDINDEX_H
