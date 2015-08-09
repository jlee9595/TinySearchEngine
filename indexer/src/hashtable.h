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
        struct DocumentNode *next;
        int doc_id;
        int freq;
} DocumentNode;

typedef struct HashTableNode {
    char *word;
	DocumentNode *page;                               // word previously seen
    struct HashTableNode *next;              // pointer to next node
} HashTableNode;


typedef struct HashTable {
    HashTableNode *table[MAX_HASH_SLOT];     // actual hashtable
} HashTable;

// ---------------- Public Variables
extern HashTable WordsFound;


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

int AddToHashTable(char *word);

int UpdateHashTable(char *word, int DocumentId);

int InHashTable(char *word);

int FreeHashTable();
#endif // HASHTABLE_H
