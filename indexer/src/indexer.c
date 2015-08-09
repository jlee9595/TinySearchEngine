#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "web.h"
#include "hashtable.h"
#include "file.h"

int GetDocumentId(char *fileName) {
	int filenum = atoi(fileName);
	return filenum;
}

char *LoadDocument(char *fileName) {
//	char *html = calloc(1, sizeof(char));
	FILE *fp;
        fp = fopen(fileName, "r");
        if (fp == NULL) {
                printf("fopen failed");
                exit(0);
        }
	fseek(fp, 0, SEEK_END);
	int filelen = ftell(fp);
        fclose(fp);
	char *html = calloc(filelen, sizeof(char));
	char *line;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("fopen failed");
		exit(0);
	}
	ssize_t read;
	size_t len = 0;
	int linenum = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		if (linenum > 1) {
			strcat(html, line);
		}
		linenum++;
	}
	free(line);
	fclose(fp);
	return html;
}

int SaveIndexToFile(char *file) {
	FILE *fp;
	fp = fopen(file, "w");
	int hashIndex = 0;
	while (hashIndex <= MAX_HASH_SLOT) {
		HashTableNode *currentNode = WordsFound.table[hashIndex];
		while (currentNode != NULL) {
			fprintf(fp,"%s ", currentNode->word);
			int docCount = 0;
			DocumentNode* currentDocNode = currentNode->page;
			while (currentDocNode != NULL) {
				docCount++;
				currentDocNode = currentDocNode->next;
			}
			fprintf(fp, "%d ", docCount);
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
	
	
//int main() {
//
	//char *doc = LoadDocument("test.txt");
//	char *doc = LoadDocument("/net/tahoe3/jlee/cs50/labs/lab5/crawler/target/3");
//	printf("%s", doc);
//}


int main(int argc, char* argv[]) {
	int docId;
	int pos;
	char *word;
	char *doc;
	char **filenames = NULL;
	int num_files = 0;
	num_files = GetFilenamesInDir(argv[1], &filenames);
	if (num_files < 0) {
		printf("failed to get any filenames");
		exit(0);
	}
	for (int i = 0; i < num_files; i++) {
		char file[100];
		strcpy(file, argv[1]);
		strcat(file, filenames[i]);
		doc = LoadDocument(file);
		docId = GetDocumentId(filenames[i]);
		
		pos = 0;
		while ((pos = GetNextWord(doc, pos, &word)) > 0)
			UpdateHashTable(word, docId);
	}

	SaveIndexToFile(argv[2]);
}
