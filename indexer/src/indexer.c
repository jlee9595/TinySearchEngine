#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "web.h"
#include "dlist.h"
#include "wlist.h"


int UpdateIndex(char *word, int documentID)

int GetDocumentId(char *fileName) {
	int filenum = atoi(fileName);
	return filenum;
}

char *LoadDocument(char *fileName) {
//	char *html = calloc(1, sizeof(char));
	char *html = calloc(1, sizeof(char));
	char *line;
	FILE *fp;
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
			//printf("%s", line);
			html = realloc(html, strlen(html)+strlen(line));
			strcat(html, line);
		}
		linenum++;
	}
	free(line);
	fclose(fp);
	return html;
}

int main() {
	printf("%d", GetDocumentId("40"));
}
	
//int main() {
//
	//char *doc = LoadDocument("test.txt");
//	char *doc = LoadDocument("/net/tahoe3/jlee/cs50/labs/lab5/crawler/target/3");
//	printf("%s", doc);
//}


//int main() {
//	int docId;
//	int pos;
//	char *word;
//	char *doc;
//
//	for name in filenames {
//		doc = LoadDocument(name);
//		docId = GetDocumentId(name);
//		
//		pos = 0;
//		while ((pos = GetNextWord(doc, pos, &word)) > 0)
//			UpdateIndex(word, docId, index);
//	}
//
//	SaveIndexToFile(index);
//}
