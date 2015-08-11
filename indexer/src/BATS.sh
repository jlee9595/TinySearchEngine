#!/bin/bash
log='./indexerTest.log'
make clean
printf "Build Start: $(date)\n" >> $log
if make
	then
		printf "Build End: $(date)\n" >> $log
		printf "Build is a success\n\n" >> $log
	else
		printf "Build failed" >> $log
		exit 1
fi

DATA_PATH=./target/
INDEX_FILE=index.dat

printf "Tests\n\n" >> $log

printf "Test 1: Run with incorrect parameter number\n" >> $log
printf "Output: " >> $log
indexer $DATA_PATH >> $log
printf "\n\n" >> $log

printf "Test 2: Run with bad folder\n" >> $log
printf "Output: " >> $log
indexer ./dsflkj $INDEX_FILE  >> $log
printf "\n\n" >> $log

printf "Test 3: Run with 1 parameter\n" >> $log
indexer $DATA_PATH $INDEX_FILE >> $log
printf "\n" >>$log

printf "Sample of contents of index file:\n$(cat $INDEX_FILE | head)\n" >> $log
printf "\n" >> $log

rm $INDEX_FILE

printf "Test 4: Run with 2 parameters and check whether the 2 output files are the same\n" >> $log

./indexer $DATA_PATH $INDEX_FILE new_index.dat >> $log
if [ $(diff index.dat new_index.dat | wc -c) != 0 ]
	then
		echo "Result: Index Storage did not pass test" >> $log
	else
		echo "Result: Index Storage did pass test" >> $log
fi

