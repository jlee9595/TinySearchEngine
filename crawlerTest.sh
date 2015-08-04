log='./crawlerTestlog.'$(date +"%a_%b_%d_%T_%Y") 

printf "Test 1: Run with bad url\n" >> $log
crawler http://www.cs.dartm.edu/~cs50/tse/ ./target/ 1 >> $log

printf "\n" >> $log

printf "Test 2: Run with bad directory\n" >> $log
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./fsd 1 >> $log

printf "\n" >> $log

printf "Test 3: Run with invalid depth\n" >> $log
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./target/ 6 >> $log

printf "\n" >> $log

rm ./target/*

printf "Test 4: Run with valid parameters at depth 0\n" >> $log
crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ ./target/ 0
printf "Number of files produced: $(ls ./target/ | sort -n | wc -l)\n" >> $log
