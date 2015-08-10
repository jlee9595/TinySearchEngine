#!/bin/bash

make clean
make

DATA_PATH=./target/
INDEX_FILE=index.dat

./indexer $DATA_PATH $INDEX_FILE new_index.dat
diff 
