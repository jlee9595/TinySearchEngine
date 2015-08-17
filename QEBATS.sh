log='./TSETest.log'

mkdir target
cd crawler
make
printf "crawling...\n"
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ../target/ 2
cd .. 

cd indexer/src
printf "indexing...\n"
indexer ../../target/ ../../index.dat
cd ../..

cd query/src
printf "querying...\n"
query ../../index.dat ../../target/ <<endof
cat
cat dog
cat AND dog
cat OR dog
endof

printf "\nyou may now test at your leisure.\n"

query ../../index.dat ../../target/

