PROGRAM=$1
EXIT_SUCCESS=0
EXIT_FAILURE=1
COUNTTEST=0
NOPARAMETER=
ZWOPARAMETER=ubahn.txt empty
NONEXISTFILE=nonexistfile
EMPTYFILE=empty
EXAMPLEFILE=ubahn.txt

# always check after running program
# 1. Parameter which is testet with the program, use quotemarks
# 1. Expected return value
# 2. parameter is test description
checkTest () {
	COUNTTEST=`expr $COUNTTEST + 1`
	./${PROGRAM} $1 > /dev/null
	if test $? -eq $2
	then
		echo "$COUNTTEST. Test Successful: $3"
	else
		echo "$COUNTTEST. Test Fail: $3"
		echo "Return value expected $2 but was $?"
		exit $EXIT_FAILURE
	fi
}

# Test cases
# ------------

checkTest "${NOPARAMETER}" $EXIT_FAILURE "Test without parameter"
checkTest "${NONEXISTFILE}" $EXIT_FAILURE "Test with nonexist file"
checkTest "${ZWOPARAMETER}" $EXIT_FAILURE "Test with two files"
checkTest "${EMPTYFILE}" $EXIT_SUCCESS "Test with empty file"
checkTest "${EXAMPLEFILE}" $EXIT_SUCCESS "Test with example file"
