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
	int pos = 0;
	char *result;
	char *html = page->url;
	char *base_url = page->html;
	while ((pos = GetNextURL(html, pos, base_url, &result)) > 0) {
		if (InHashTable(result) == 0) {
			AddToHashTable(result);
			WebPage *newpage = calloc(1, sizeof(WebPage));
			newpage->url = result;
			GetWebPage(newpage);
			AppendList(newpage);
		}
	}
	PopList();
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

	//initialiaze data structures/variables
	List URLList;
	HashTable URLsVisited;
	int maxDepth = atoi(argv[3]);
	WebPage *page;
	char *URLToBeVisited;

    // setup seed page
    	page = calloc(1, sizeof(WebPage));
	page->url = argv[1];
	page->depth = maxDepth;
    // get seed webpage
	GetWebPage(page);

    // write seed file
	FILE *fp;

	fp = fopen(strcat(argv[2], "1"), "w");
	fprintf(fp, strcat(page->url, "\n"));
	fprintf(fp,"%d", page->depth);
	fprintf(fp, "\n");
	fprintf(fp, page->html);
	fclose(fp);
    // add seed page to hashtable
	AddToHashTable(page->url);

    // extract urls from seed page
	CrawlPage(page);
	printf(WebList.page
    // while there are urls to crawl
        // get next url from list

        // get webpage for url

        // write page file

        // extract urls from webpage

    // cleanup curl
    curl_global_cleanup();

    return 0;
}
