#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "hashtable.h"
#include "invertedIndex.h"
#include "list.h"
#include "../../util/web.h"
#include "../../util/file.h"

List *search(char *user_input, char *crawlerdir, InvertedIndex *index) {
	List *URLList = calloc(1, sizeof(URLList));;
	char *wordArray[1000];
	char *token;
	token = strtok(user_input, " ");
	
	int i = 0;
	while (token != NULL) {
		wordArray[i] = calloc(strlen(token), sizeof(char));
		strcpy(wordArray[i], token);
		token = strtok(NULL, " ");
		i++;
	}
	free(token);
	
	int c;
	for (c=0; c<i; c++) {
		char *word = wordArray[c];
		if (strcmp(word, "AND") == 0 || strcmp(word, "OR") == 0) {
			continue;
		}
		NormalizeWord(word);
		if (InInvertedIndex(word, index)) {
			InvertedIndexNode *currentNode = index->table[JenkinsHash(word, MAX_HASH_SLOT)];
			while (strcmp(currentNode->word, word) != 0) {
				currentNode = currentNode->next;
			}
			DocumentNode *currentDocNode = currentNode->page;
			while (currentDocNode != NULL) {
				ListNode *currentListNode;
				currentListNode = URLList->head;
				while (currentListNode != NULL) {
					if (currentListNode->doc_id == currentDocNode->doc_id) {
						currentListNode->score += currentDocNode->freq;
						break;
					}
					currentListNode = currentListNode->next;
				}
				if (currentListNode == NULL) {
					AppendList(currentDocNode->doc_id, URLList);
					URLList->tail->score += currentDocNode->freq;
				}
				
				currentDocNode = currentDocNode->next;
			}
		}
		free(word);
	}
	ListNode *currentListNode = URLList->head;
	while (currentListNode != NULL) {
		printf("%d, %d\n", currentListNode->doc_id, currentListNode->score);
		currentListNode = currentListNode->next;
	}
	return URLList;
}

int PrintResults(List *docList, char *crawlerdir) {
	if (docList->head == NULL) {
		printf("No results found.\n");
	}
	while (docList->head != NULL) {
		ListNode *currentListNode = docList->head;
		ListNode *listTracker = docList->head;
		while (listTracker != NULL) {
			if (listTracker->score > currentListNode->score) {
				currentListNode = listTracker;
			}
			listTracker = listTracker->next;
		}
		FILE *fp;
		char *filename = calloc(1000, sizeof(char));
		char *filenum = calloc(1000, sizeof(char));
		sprintf(filenum, "%d", currentListNode->doc_id);
		strcpy(filename, crawlerdir);
		strcat(filename, filenum);
		fp = fopen(filename, "r");
		char *line = calloc(10000, sizeof(char));
		fgets(line, INT_MAX, fp);
		fclose(fp);
		printf("Document ID: %d | URL: %s", currentListNode->doc_id, line);
		free(line);
		free(filename);
		free(filenum);
		PopList(currentListNode->doc_id, docList);
	}
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("too many or too few arguments, please try again with 2 arguments.");
		exit(0);
	}
	
	if (!IsFile(argv[1])) {
		printf("invalid index file, please try again.");
		exit(0);
	}

	if (!IsDir(argv[2])) {
		printf("invalid directory, please try again.");
		exit(0);
	}
	
	InvertedIndex *index = ReadFile(argv[1]);
	int i = 0;
	while (i != 3) {
		char *user_input = calloc(1000, sizeof(char));
		printf("QUERY: ");
		fgets(user_input, 1000, stdin);
		user_input = strtok(user_input, "\n");
		List *docList = search(user_input, argv[2], index);
		PrintResults(docList, argv[2]);
		free(docList);
		free(user_input);
		i++;
	}
	FreeInvertedIndex(index);
	return 0;
}
