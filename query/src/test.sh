query index.dat ./target/ <<endof
`echo "hi my name is":q
stdout 
$(echo justin) justin 
endof
#exit 0


#query index.dat target/ < end
#dartmouth
#justin
#end
