# TinySearchEngine

This is a basic search engine written in C for the Dartmouth course 'CS50: Software Design and Implementation'. Unfortunately due to restrictions set by the course, this search engine is designed to restrict users from crawling anywhere outside 'http://old-www.cs.dartmouth.edu/'.

Before running, install GNU make: https://www.gnu.org/software/make/

To run the search engine, run 'QEBATS.sh'.

Note: Expect to wait for a few minutes for the indexing process to complete.

# A quick summary of how the engine works:

Crawler: takes an initial seed page and crawls web pages from there, adding the HTML files for the pages it finds to a target directory.

Indexer: Takes the target directory and analyzes each file for how often each word occurs. The words, the pages they are found at, and the frequency with which they are found are stored in an inverted index (implemented with a hash table). 

Query: Provides a user interface for the user to type in a word, at which point the query engine will check the inverted index for that word's frequency count and return a list of the webpages where that word can be found along with how many times it pops up in each page.


# Data structures used:
Doubly Linked List - Used to implement a queue that tracks which web pages still need to be crawled.

Hashtable - Used during crawling process to quickly check whether a url has been crawled or not
	  - Also extended to act as an inverted index to query from

Singly Linked List - Used to handle collisions in the hashtable. Each bucket is a singly linked list

