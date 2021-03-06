echo "--------------------------------------------------------"

PROGRAM=$1
EXIT_SUCCESS=0
EXIT_FAILURE=1
COUNTTEST=0
NOPARAMETER=
ZWOPARAMETER="ubahn.txt empty"
NONEXISTFILE=nonexistfile
EMPTYFILE=empty
EXAMPLEFILE=ubahn.txt
# ErrorTestCases
ETC1=errTestcase1.txt

# always check after running program
# 1. Parameter which is testet with the program, use quotemarks
# 2. Expected return value
# 3. parameter is test description
# 4. Input for startStation and endStation "\"startStation\"\n\"endStation\"\n"
checkTest () {
	COUNTTEST=`expr $COUNTTEST + 1`
	echo "$COUNTTEST. Test: $3"
	echo -e $4 | ./${PROGRAM} $1 1> /dev/null
	if test $? -eq $2
	then
		echo "Successful"
	else
		echo "Fail"
		echo "Return value expected $2 but was $?"
		exit $EXIT_FAILURE
	fi
}

# Test cases
# ------------	

# FAILURE
checkTest "${NOPARAMETER}" $EXIT_FAILURE "Test without parameter"
checkTest "${NONEXISTFILE}" $EXIT_FAILURE "Test with nonexist file"
checkTest "${ZWOPARAMETER}" $EXIT_FAILURE "Test with two files"
checkTest "${ZWOPARAMETER}" $EXIT_FAILURE "Test with two files"
checkTest "${ETC1}" $EXIT_FAILURE "Test with wrong format in file: ${ETC1}"

#SUCCESS
checkTest "${EMPTYFILE}" $EXIT_SUCCESS "Test with empty file"
checkTest "test1.txt" $EXIT_SUCCESS "Test with one line without newLine at the end" "test\nbla\n"

