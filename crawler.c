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

#include <curl/curl.h>                       // curl functionality

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

int main(int argc, char* argv[])
{
    printf("Get cooking cs50!\n"
           "Translate the pseudo code. Data structures are in crawler.h\n"
           "Good luck\n");

    // check command line arguments

    // init curl
    curl_global_init(CURL_GLOBAL_ALL);

    // setup seed page

    // get seed webpage

    // write seed file

    // add seed page to hashtable

    // extract urls from seed page

    // while there are urls to crawl
        // get next url from list

        // get webpage for url

        // write page file

        // extract urls from webpage

    // cleanup curl
    curl_global_cleanup();

    return 0;
}
