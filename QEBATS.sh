printf "Begin TSE test at depth 1\n\n"

rm -rf target
rm index.dat

mkdir target
cd crawler
make
printf "crawling...\n"
./crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ../target/ 1
cd .. 

cd indexer/src
make
printf "indexing...\n"
./indexer ../../target/ ../../index.dat
cd ../..

cd query/src
make

printf "\nyou may now test at your leisure."

./query ../../index.dat ../../target/

