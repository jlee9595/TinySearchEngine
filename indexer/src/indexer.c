//indexer.c
//Author: Justin Lee
//Indexes a given target directory's pages to a queriable inverted index

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#include "web.h"
#include "hashtable.h"
#include "file.h"

//Converts a filename to an int
int GetDocumentId(char *fileName) {
	int filenum = atoi(fileName);
	return filenum;
}

//Loads a document's html given its filename
char *LoadDocument(char *fileName) {
	FILE *fp;
        fp = fopen(fileName, "r");	
	//check that the file is valid
        if (fp == NULL) {
                printf("fopen failed");
                exit(0);
        }

	//get size of file
	fseek(fp, 0, SEEK_END);
	int filelen = ftell(fp);
        fclose(fp);

	char *html = calloc(filelen, sizeof(char));
	char *line = calloc(filelen, sizeof(char));

	fp = fopen(fileName, "r");
	int linenum = 0;
	while (fgets(line, INT_MAX, fp) != NULL) {
		if (linenum > 1) {
			strcat(html, line);
		}
		linenum++;
	}
	free(line);
	fclose(fp);
	return html;
}

//Saves an inverted index to a file in a readable format
int SaveIndexToFile(char *file, HashTable *WordsFound) {
	FILE *fp;
	fp = fopen(file, "w");
	int hashIndex = 0;
	
	while (hashIndex < MAX_HASH_SLOT) {						//go through the entire index
		HashTableNode *currentNode = WordsFound->table[hashIndex];
				
		while (currentNode != NULL) {						//go through each word
			fprintf(fp,"%s ", currentNode->word);
			int docCount = 0;
			DocumentNode* currentDocNode = currentNode->page;
			//count how many documents contained the word
			while (currentDocNode != NULL) {				//go through each document
				docCount++;
				currentDocNode = currentDocNode->next;
			}
			fprintf(fp, "%d ", docCount);
			
			//go back to beginning of document list and print the docid and freq for each document
			currentDocNode = currentNode->page;
			while (currentDocNode != NULL) {
				fprintf(fp, "%d %d ", currentDocNode->doc_id, currentDocNode->freq);
				currentDocNode = currentDocNode-> next;
			}
			fprintf(fp, "\n");
			currentNode = currentNode->next;
		}

	hashIndex++;
	}

	fclose(fp);
	return 0;
}			

//Reads an inverted index file and recreates the data structure it represents
HashTable *ReadFile(char *file) {
	HashTable *reloadedIndex = calloc(1, sizeof(HashTable));			//allocate new index
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
				if (InHashTable(word, reloadedIndex) == 0) {
					AddToHashTable(word, reloadedIndex);
					UpdateHashTable(word, doc_id, reloadedIndex);
				}
				else {
					UpdateHashTable(word, doc_id, reloadedIndex);
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

int main(int argc, char* argv[]) {
	//check argument number
	if (argc < 3 || argc > 4) {
		printf("too many or too little arguments, please try again");
		exit(0);
	}
	
	//check directory validity
	if (!IsDir(argv[1])) {
		printf("invalid directory, please try again");
		exit(0);
	}
	
	//Initialize variables and index
	int docId;
	int pos;
	char *doc;
	char **filenames = NULL;
	int num_files = 0;
	HashTable *WordsFound = calloc(1, sizeof(HashTable));
	num_files = GetFilenamesInDir(argv[1], &filenames);

	//check whether the folder has files
	if (num_files < 0) {
		printf("failed to get any filenames");
		exit(0);
	}

	//iterate through each file in the directory
	for (int i = 0; i < num_files; i++) {
		
		//check that the file is in the correct format (title is a number)
		int filechecker = 0;
		for (int c = 0; c < strlen(filenames[i]); c++) {
			if (!isdigit(filenames[i][c])) {
				filechecker = 1;
			}
		}
		if (filechecker == 1) {
			continue;
		}

		//Load the document
		char *word;
		char file[100];
		strcpy(file, argv[1]);
		strcat(file, filenames[i]);
		doc = LoadDocument(file);
		docId = GetDocumentId(filenames[i]);
		free(filenames[i]);
		
		pos = 0;
		//Iterate through each word in the html file (doc)
		while ((pos = GetNextWord(doc, pos, &word)) > 0) {
			NormalizeWord(word);
			if (InHashTable(word, WordsFound) == 0) {
				AddToHashTable(word, WordsFound);
				UpdateHashTable(word, docId, WordsFound);
			}
			else {
				UpdateHashTable(word, docId, WordsFound);
				free(word);
			}
		}
		free(doc);
	}	
	free(filenames);
	SaveIndexToFile(argv[2], WordsFound);				//Save the index to the file specified
	FreeHashTable(WordsFound);

	//only proceed if there was a third argument specified. If so, reload the index form the file you just created
	if (argc == 4) {
		HashTable *ReloadedIndex = ReadFile(argv[2]);
		SaveIndexToFile(argv[3], ReloadedIndex);
		FreeHashTable(ReloadedIndex);
	}
	return 0;
}
