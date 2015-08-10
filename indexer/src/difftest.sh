#!/bin/bash
log='./indexerTest.log'
printf "Build Start: $(date)\n" >> $log
make clean
make
printf "Build End: $(date)\n" >> $log
printf "Build is a success\n\n" >> $log

DATA_PATH=./target/
INDEX_FILE=index.dat

printf "Tests\n\n" >> $log

printf "Test 1: Run with incorrect parameter number\n" >> $log
indexer $DATA_PATH >> $log
printf "\n" >> $log

printf "Test 2: Run with bad folder\n" >> $log
indexer $DATA_PATH ./dsflkj >> $log
printf "\n" >> $log

printf "Test 3: Run with 1 parameter\n" >> $log
indexer $DATA_PATH $INDEX_FILE >> $log
printf "Sample of contents of index file:\n$(cat $INDEX_FILE | head)\n"
printf "\n" >> $log

rm $INDEX_FILE

printf "Test 4: Run with 2 parameters\n" >> $log

./indexer $DATA_PATH $INDEX_FILE new_index.dat >> $log
if [ $(diff index.dat new_index.dat | wc -c ]) != 0 ]
	then
		echo "Index Storage did not pass test"
	else
		echo "Index Storage did pass test"
fi

