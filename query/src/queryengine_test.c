#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "invertedIndex.h"
#include "list.h"
#include "hashtable.h"
#include "../../util/web.h"

// each test should start by setting the result count to zero
//
#define START_TEST_CASE  int rs=0

// check a condition and if false print the test condition failed
// // e.g., SHOULD_BE(dict->start == NULL)
// // note: the construct "#x" below is the sstringification preprocessor operator that
// //       converts the argument x into a character string constant
//
#define SHOULD_BE(x) if (!(x))  {rs=rs+1; \
printf("Line %d test [%s] Failed\n", __LINE__,#x); \
}

// return the result count at the end of a test
//
#define END_TEST_CASE return rs

// general macro for running a best
// // e.g., RUN_TEST(TestDAdd1, "DAdd Test case 1");
// // translates to:
// // if (!TestDAdd1()) {
// //     printf("Test %s passed\n","DAdd Test case 1");
// // } else { 
// //     printf("Test %s failed\n", "DAdd Test case 1");
// //     cnt = cnt +1;
// // }
// //
//
#define RUN_TEST(x, y) if (!x()) {              \
     printf("Test %s passed\n", y);              \
} else {                                        \
     printf("Test %s failed\n", y);              \
     cnt = cnt + 1;                              \
}

List *search(char *user_input, InvertedIndex *index) {
        List *URLList = calloc(1, sizeof(URLList));
	if (user_input == NULL) {
		return NULL;
	}
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
		return 1;
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

int Testsearch1() {
	START_TEST_CASE;
	InvertedIndex *index = ReadFile("index.dat");
	SHOULD_BE(search(NULL, index) == NULL);
	FreeInvertedIndex(index);
	END_TEST_CASE;
}
	
	

//Test for case of empty list, should return 1
int TestPrintResults1() {
	START_TEST_CASE;
	List *testList = calloc(1, sizeof(testList));
	SHOULD_BE(PrintResults(testList, "./target/") == 1);
	free(testList);
	END_TEST_CASE;
}

int main(int argc, char** argv) {
	int cnt = 0;	
	RUN_TEST(Testsearch1, "search Test case 1");
	RUN_TEST(TestPrintResults1, "PrintResults Test case 1");

	if (!cnt) {
		printf("All passed!\n");
		return 0;
	}

	else {
		printf("Some fails!\n");
		return 0;
	}
}
