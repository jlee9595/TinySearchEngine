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
#ifndef HASHTABLE_H
#define HASHTABLE_H


// ---------------- Constants
#define MAX_HASH_SLOT 10000                  // number of "buckets"

// ---------------- Structures/Types

typedef struct DocumentNode {
        struct DocumentNode *next;		//pointer to  next node
        int doc_id;				// id of file
        int freq;				//frequency with which the word comes up in the file
} DocumentNode;

typedef struct HashTableNode {
	char *word;				//word that the node holds
	DocumentNode *page;                     //first documentnode associated with word
    	struct HashTableNode *next;             // pointer to next node
} HashTableNode;


typedef struct HashTable {
	HashTableNode *table[MAX_HASH_SLOT];	//Inverted Index
} HashTable;

// ---------------- Public Variables
//extern HashTable WordsFound;


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
unsigned long JenkinsHash(const char *str, unsigned long mod);

int AddToHashTable(char *word, HashTable *WordsFound);

int UpdateHashTable(char *word, int DocumentId, HashTable *WordsFound);

int InHashTable(char *word, HashTable *WordsFound);

int FreeHashTable(HashTable *WordsFound);
#endif // HASHTABLE_H
