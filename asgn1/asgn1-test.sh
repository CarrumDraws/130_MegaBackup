#!/usr/bin/bash

port=3010
if (( "$#" == 1 )) && (( "$1" > 1023 )); then
	port="$1"
elif (( "$#" == 1 )); then
	echo "Warning: Port numbers less than 1024 are reserved. Defaulting to port 3010..."
elif [[ "$#" -ne 0 ]]; then
	echo "asgn0-test: Program takes up to 1 argument (port number). Exiting..."
	exit 1
fi

# UNCOMMENT 2 LINES BELOW IF YOU WISH TO RUN BURNING's TEST BEFOREHAND
if [ -f testScript ]; then
	echo "====Running Burning's Tests===="
	./testScript
fi

iter=0
if [ ! -f "r1.txt" ]; then
	echo "Creating smaller test txt file"
	while [ $iter -le 5 ];
	do
		cat httpserver.c >> r1.txt
		((++iter))
	done
fi

if [ ! -f "r2.txt" ]; then
	echo "Creating smaller binary test file"
	cat httpserver >> r2.txt
fi

iter=0
if [ ! -f "r3.txt" ]; then
	echo "Creating smaller Makefile test file"
	while [ $iter -le 5 ];
	do
		cat Makefile >> r3.txt
		((++iter))
	done
fi

if [ ! -f "r4.txt" ]; then
	echo "Downloading larger test file"
	curl -s ftp://ccg.epfl.ch/epd/current/epd.seq | tac | tac | head -qn 40000 > r4.txt
fi

iter=0
if [ ! -f "r5.txt" ]; then
	echo "Creating second large test file"
	while [ $iter -le 13 ]
	do
		cat httpserver.c >> r5.txt
		cat Makefile >> r5.txt
		((++iter))
	done
fi

if [ ! -f "r6.txt" ]; then
	out=$(which head)
	cat $out >> r6.txt
fi

if [ ! -f "r7.txt" ]; then
	echo "Creating larger mixed test file"
	cat r4.txt >> r7.txt
	cat r6.txt >> r7.txt
	cat r5.txt >> r7.txt
fi

echo "====Running GET tests===="
NUM_IN_FILES=7
testCase=1

testIter=1
while [ $testIter -le $NUM_IN_FILES ]
do
	FILE=r"$testCase".txt
	out=$(diff <(curl -s localhost:"$port"/"$FILE") $FILE)

	printf "Test $testCase: "
	if [ "$out" = "" ]; then
		printf "PASS\n"
	else
		printf "FAIL. Difference found. Command run: diff <(curl -s localhost:$port/$FILE) <(cat $FILE)\n"
	fi

	((++testCase))
	((++testIter))
done

echo "====Running PUT tests===="
testIter=1
while [ $testIter -le $NUM_IN_FILES ]
do
	INFILE=r"$testIter".txt
	OUTFILE=r"$(($testIter + $NUM_IN_FILES))".txt

	curl -s -T "$INFILE" localhost:"$port"/"$OUTFILE" > /dev/null
	chmod +rw $OUTFILE
	out=$(diff <(cat $INFILE) <(cat $OUTFILE))

	printf "Test $testCase: "
	if [ "$out" = "" ]; then
		printf "PASS\n"
	else
		printf "FAIL. Difference found. Command run: 	curl -s -T $INFILE localhost:$port/$OUTFILE > /dev/null && chmod +rw $OUTFILE && diff $INFILE $OUTFILE\n"
	fi
	((++testCase))
	((++testIter))
done

testIter=1
outIter=$((2*$NUM_IN_FILES+1))
while [ $testIter -le $NUM_IN_FILES ]
do
	INFILE=r"$testIter".txt
	OUTFILE=r"$outIter".txt

	curl -s -T "$INFILE" localhost:"$port"/"$OUTFILE" > /dev/null
	chmod +rw $OUTFILE
	out=$(diff <(cat $INFILE) <(cat $OUTFILE))

	printf "Test $testCase: "
	if [ "$out" = "" ]; then
		printf "PASS\n"
	else
		printf "FAIL. Difference found. Command run: 	curl -s -T $INFILE localhost:$port/$OUTFILE > /dev/null && chmod +rw $OUTFILE && diff $INFILE $OUTFILE\n"
	fi
	((++testCase))
	((++testIter))
	((++outIter))
done

echo "====Running GETs on files created/updated with PUTs above===="
testIter=1
while [ $testIter -le $NUM_IN_FILES ]
do
	INFILE=r"$testIter".txt
	OUTFILE=r"$(($testIter + $NUM_IN_FILES))".txt

	out=$(diff <(cat $INFILE) <(curl -s localhost:"$port"/"$OUTFILE"))

	printf "Test $testCase: "
	if [ "$out" = "" ]; then
		printf "PASS\n"
	else
		printf "FAIL. Difference found. Command run: 	curl -s -T $INFILE localhost:$port/$OUTFILE > /dev/null && chmod +rw $OUTFILE && diff $INFILE $OUTFILE\n"
	fi
	((++testCase))
	((++testIter))
done

testIter=1
outIter=$((2*$NUM_IN_FILES+1))
while [ $testIter -le $NUM_IN_FILES ]
do
	INFILE=r"$testIter".txt
	OUTFILE=r"$outIter".txt

	out=$(diff <(cat $INFILE) <(curl -s localhost:"$port"/"$OUTFILE"))

	printf "Test $testCase: "
	if [ "$out" = "" ]; then
		printf "PASS\n"
	else
		printf "FAIL. Difference found. Command run: 	curl -s -T $INFILE localhost:$port/$OUTFILE > /dev/null && chmod +rw $OUTFILE && diff $INFILE $OUTFILE\n"
	fi
	((++testCase))
	((++testIter))
	((++outIter))
done

echo "====Calling PUT with different files, checking output===="
testIter=1
while [ $testIter -le $NUM_IN_FILES ]
do
	INFILE0=r"$testIter".txt
	INFILE1=Makefile
	OUTFILE=r"$(($testIter + $NUM_IN_FILES))".txt

	curl -s -T $INFILE0 localhost:"$port"/"$OUTFILE" > /dev/null
	curl -s -T $INFILE1 localhost:"$port"/"$OUTFILE" > /dev/null

	out0=$(diff $INFILE0 <(curl -s localhost:"$port"/"$OUTFILE"))
	out1=$(diff $INFILE1 <(curl -s localhost:"$port"/"$OUTFILE"))

	printf "Test $testCase: "
	if [ ! "$out0" = "" ] && [ "$out1" = "" ]; then
		printf "PASS\n"
	else
		printf "FAIL. Difference found. Command run: 	curl -s -T $INFILE localhost:$port/$OUTFILE > /dev/null && chmod +rw $OUTFILE && diff $INFILE $OUTFILE\n"
	fi
	((++testCase))
	((++testIter))
done

testIter=1
outIter=$((2*$NUM_IN_FILES+1))
while [ $testIter -le $NUM_IN_FILES ]
do
	INFILE0=r"$testIter".txt
	INFILE1=Makefile
	OUTFILE=r"$(($testIter + $NUM_IN_FILES))".txt

	curl -s -T $INFILE0 localhost:"$port"/"$OUTFILE" > /dev/null
	curl -s -T $INFILE1 localhost:"$port"/"$OUTFILE" > /dev/null

	out0=$(diff $INFILE0 <(curl -s localhost:"$port"/"$OUTFILE"))
	out1=$(diff $INFILE1 <(curl -s localhost:"$port"/"$OUTFILE"))

	printf "Test $testCase: "
	if [ ! "$out0" = "" ] && [ "$out1" = "" ]; then
		printf "PASS\n"
	else
		printf "FAIL. Difference found. Command run: 	curl -s -T $INFILE localhost:$port/$OUTFILE > /dev/null && chmod +rw $OUTFILE && diff $INFILE $OUTFILE\n"
	fi
	((++testCase))
	((++testIter))
done

echo "====Running Bad Request tests===="
FILE=r1.txt

# Invalid HostName for GET
printf "Test $testCase: "
out=$(diff <(curl -s localhost:"$port"/"$FILE" -H "Host: a a") <(echo Bad Request))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. Difference found. Command run: diff <(curl -s localhost:$port/$FILE -H \"Host: a a\") <(echo Bad Request)\n"
fi
((++testCase))

# Invalid HostName for HEAD
#printf "Test $testCase: "
#out=$(diff <(curl -s -I localhost:"$port" -H "Host: a a") <(echo Bad Request))

#if [ "$out" = "" ]; then
#	printf "PASS\n"
#else
#	printf "FAIL\n"
#fi
#((++testCase))

# Invalid HostName for PUT
printf "Test $testCase: "
out=$(diff <(curl -s -T r1.txt localhost:"$port"/"$FILE" -H "Host: a a") <(echo Bad Request))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. Difference found. Command run: diff <(curl -s -T r1.txt localhost:$port/$FILE -H \"Host: a a\") <(echo Bad Request)\n"
fi
((++testCase))

# Invalid Content-Length for PUT
printf "Test $testCase: "
out=$(diff <(curl -s -T r1.txt localhost:$port/"$FILE" -H "Content-Length: a") <(echo Bad Request))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. Difference found. Command run: diff <(curl -s -T r1.txt localhost:$port/$FILE -H \"Content-Length: a\") <(echo Bad Request)\n"
fi
((++testCase))

printf "Test $testCase: "
out=$(diff <(curl -s -T r1.txt localhost:"$port"/"$FILE" -H "Content-Length: 333a") <(echo Bad Request))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. Difference found. Command run: diff <(curl -s -T r1.txt localhost:$port/$FILE -H \"Content-Length: 333a\") <(echo Bad Request)\n"
fi
((++testCase))

printf "Test $testCase: "
out=$(diff <(curl -s -T r1.txt localhost:"$port"/"$FILE" -H "Content-Length: a333a") <(echo Bad Request))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. Difference found. Command run: diff <(curl -s -T r1.txt localhost:$port/$FILE -H \"Content-Length: a333a\") <(echo Bad Request)\n"
fi
((++testCase))

FILE=this_file_is_more_than_19_characters.txt

# Resource name too long for GET
printf "Test $testCase: "
out=$(diff <(curl -s r1.txt localhost:"$port"/"$FILE") <(echo Bad Request))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. Difference found. Command run: diff <(curl -s r1.txt localhost:$port/$FILE) <(echo Bad Request)"
fi
((++testCase))

# Resource name too long for PUT
printf "Test $testCase: "
out=$(diff <(curl -s -T r1.txt localhost:"$port"/"$FILE") <(echo Bad Request))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. Difference found. Command run: diff <(curl -s -T r1.txt localhost:$port/$FILE -H \"Content-Length: a333a\") <(echo Bad Request)\n"
fi
((++testCase))

fn="this\$#@^%()&*!"
FILE="$fn".txt

# Resource has illegal characters for GET
printf "Test $testCase: "
out=$(diff <(curl -s r1.txt localhost:"$port"/"$FILE") <(echo Bad Request))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. Difference found. Command run: diff <(curl -s r1.txt localhost:$port/$FILE) <(echo Bad Request)"
fi
((++testCase))

# Resource has illegal characters for PUT
printf "Test $testCase: "
out=$(diff <(curl -s -T r1.txt localhost:"$port"/"$FILE") <(echo Bad Request))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. Difference found. Command run: diff <(curl -s -T r1.txt localhost:$port/$FILE) <(echo Bad Request)\n"
fi
((++testCase))

echo ====Running File Not Found tests====
FILE=non_existent.txt

# Invalid HostName for GET
printf "Test $testCase: "
out=$(diff <(curl -s localhost:"$port"/"$FILE") <(echo File Not Found))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. diff <(curl -s localhost:$port/$FILE) <(echo File Not Found)\n"
fi
((++testCase))

# Invalid HostName for HEAD
#printf "Test $testCase: "
#out=$(diff <(curl -s -I localhost:"$port"/"$FILE") <(printf "HTTP/1.1 404 File Not Found\nContent-Length: 15\n\n"))
#
#if [ "$out" = "" ]; then
#	printf "PASS\n"
#else
#	printf 'FAIL. Difference found. Command run: diff <(curl -s -I localhost:"$port"/'
#	printf "$FILE"
#	printf ') <(printf "HTTP/1.1 404 File Not Found\\nContent-Length: 15\\n\\n")\n'
#fi
#((++testCase))

echo ====Running Forbidden tests====
FILE=forbidden.txt

if [ ! -f "forbidden.txt" ]; then
	touch forbidden.txt
	chmod -rw forbidden.txt
fi

# Invalid HostName for GET
printf "Test $testCase: "
out=$(diff <(curl -s localhost:"$port"/"$FILE") <(echo Forbidden))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. diff <(curl -s localhost:$port/$FILE) <(echo Forbidden)\n"
fi
((++testCase))

printf "Test $testCase: "
out=$(diff <(curl -T r1.txt -s localhost:"$port"/"$FILE") <(echo Forbidden))

if [ "$out" = "" ]; then
	printf "PASS\n"
else
	printf "FAIL. diff <(curl -s localhost:$port/$FILE) <(echo Forbidden)\n"
fi
((++testCase))

printf "====All Done. Removing r$((2*$NUM_IN_FILES+1)).txt-r$((3*$NUM_IN_FILES)).txt====\n"
iter=$((2*$NUM_IN_FILES+1))
while [ $iter -le $((3*$NUM_IN_FILES)) ]; do
	rm -f r"$iter".txt
	((++iter))
done
