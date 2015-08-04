/* ========================================================================== */
/* File: crawler.c - Tiny Search Engine web crawler
 *
 * Author:
 * Date:
 *
 * Input:
 *
 * Command line options:
 *
 * Output:
 *
 * Error Conditions:
 *
 * Special Considerations:
 *
 */
/* ========================================================================== */
// ---------------- Open Issues

// ---------------- System includes e.g., <stdio.h>
#include <stdio.h>                           // printf
#include <unistd.h>
#include <curl/curl.h>                       // curl functionality
#include <string.h>
#include <strings.h>

// ---------------- Local includes  e.g., "file.h"
#include "common.h"                          // common functionality
#include "web.h"                             // curl and html functionality
#include "list.h"                            // webpage list functionality
#include "hashtable.h"                       // hashtable functionality
#include "utils.h"                           // utility stuffs
// ---------------- Constant definitions

// ---------------- Macro definitions

// ---------------- Structures/Types

// ---------------- Private variables

// ---------------- Private prototypes

/* ========================================================================== */

int CrawlPage(WebPage *page) {
	int currentdepth = page->depth;
	int pos = 0;
	char *result;
	char *html = page->html;
	char *base_url = page->url;
	while ((pos = GetNextURL(html, pos, base_url, &result)) > 0) {
		if (InHashTable(result) == 0 && strstr(result, "http://old-www.cs.dartmouth.edu/~cs50/tse/") != NULL && NormalizeURL(result) == 1) {
			printf("Parser found link - %s\n", result);
			AddToHashTable(result);
			WebPage *newpage;
			if ((newpage = calloc(1, sizeof(WebPage))) == NULL) {
				return 1;
			}
			newpage->url = result;
			newpage->depth = currentdepth + 1;
			if (GetWebPage(newpage) != 0) {
				AppendList(newpage);
			}
		}
	//	else {
	//		free(result);
	//	}
	}
	return 0;
}			

int WriteFile(WebPage *page, char *targetdirectory, int filenumber) {
	char file[10000];
	char numconverted[10000];
	strcpy(file, targetdirectory);
	sprintf(numconverted, "%d", filenumber);
	strcat(file, numconverted);
	FILE *fp;
	fp = fopen(file, "w");
	fprintf(fp, page->url);
	fprintf(fp, "\n"); 
	fprintf(fp, "%d", page->depth);
	fprintf(fp, "\n");
	fputs(page->html, fp);
	fclose(fp);
	return 0;
}

int main(int argc, char* argv[])
{
    // check command line arguments
	//correct number of parameters?
	if (argc != 4) {
		printf("Wrong number of parameters. Please try again and remember to specify seed url, target directory, and max crawling depth");
		exit(0);
	}
	//does the directory exist and is it writable?
	if (access(argv[2], W_OK) != 0) {
		printf("Directory not found, please enter an existing and writable target directory");
		exit(0);
	}
	//is the maximum depth in the right range?	
	if (atoi(argv[3]) > MAX_DEPTH) {
		printf("Max depth exceeds maximum, please try again and enter a max depth no higher than 4");
	}


    // init curl
	curl_global_init(CURL_GLOBAL_ALL);

	//initialize data structures/variables
	//List URLList;
	//HashTable URLsVisited;
	int maxDepth = atoi(argv[3]);
	WebPage *page;
	int filenumber = 1;

    // setup seed page
    	page = calloc(1, sizeof(WebPage));
	page->url = argv[1];
	page->depth = 0;
    // get seed webpage
	GetWebPage(page);
	
    // write seed file
	WriteFile(page, argv[2], filenumber);
	filenumber++;
    // add seed page to hashtable
	AddToHashTable(page->url);

    // extract urls from seed page
	CrawlPage(page);
    // while there are urls to crawl
	while (URLList.head != NULL) {
		if (URLList.head->page->depth <=  maxDepth) {
        	// get next url from list
			page = URLList.head->page;
				
 	       // write page file
			WriteFile(page, argv[2], filenumber);
			filenumber++;
        	// extract urls from webpage
			if (page->depth < maxDepth) {
				printf("Crawling - %s\n", page->url);	
				CrawlPage(page);
			}
		}
		PopList();
	}
    // cleanup curl
	curl_global_cleanup();
	//free(page->url);
	//free(page->html);
//	free(page);
	//FreeHashTable();
	return 0;
}
