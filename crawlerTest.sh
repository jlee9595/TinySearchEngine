log='./crawlerTestlog.'$(date +"%a_%b_%d_%T_%Y") 

printf "Crawler Test Log\n\n" >> $log

printf "Test 1: Run with bad url\n" >> $log
crawler http://www.cs.dartm.edu/~cs50/tse/ ./target/ 1 >> $log

printf "\n\n" >> $log

printf "Test 2: Run with bad directory\n" >> $log
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./fsd 1 >> $log

printf "\n\n" >> $log

printf "Test 3: Run with invalid depth\n" >> $log
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./target/ 6 >> $log

printf "\n\n" >> $log
printf "For the following tests, use url http://old-www.cs.dartmouth.edu/~cs50/tse/ and directory ./target/\n\n" >> $log

if [ $(ls ./target/ | wc -c) != 0 ]
then
	rm ./target/*
fi

printf "Test 4: Run with valid parameters at depth 0\n" >> $log
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./target/ 0
printf "Number of files produced: $(ls ./target/ | sort -n | wc -l)\n\n" >> $log

rm ./target/*

printf "Test 5: Run with valid parameters at depth 1\n" >> $log
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./target/ 1
printf "Number of files produced: $(ls ./target/ | sort -n | wc -l)\n\n" >> $log

rm ./target/*

printf "Test 6: Run with valid parameters at depth 2\n" >> $log
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./target/ 2
printf "Number of files produced: $(ls ./target/ | sort -n | wc -l)\n\n" >> $log

rm ./target/*

printf "Test 7: Run with valid parameters at depth 3\n" >> $log
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./target/ 3
printf "Number of files produced: $(ls ./target/ | sort -n | wc -l)\n\n" >> $log

printf "The files produced by Test 7 have been left for inspection." >> $log

