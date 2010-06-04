PROGRAM=$1
EXIT_SUCCESS=0
EXIT_FAILURE=1
COUNTTEST=0
NONEXISTFILE=nonexistfile

# always check after running program
# 1. parameter is test description
checkTest () {
	ERRORCODE=$?
	COUNTTEST=`expr $COUNTTEST + 1`
	if test $ERRORCODE -eq $EXIT_FAILURE
	then
		echo "$COUNTTEST. Test Successful"
	else
		echo "$COUNTTEST. Test Fail"
		return $EXIT_FAILURE
	fi
}

# Test cases
# ------------

./${PROGRAM}
checkTest "Test without parameter"

./${PROGRAM} ${NONEXISTFILE}
checkTest "Test with nonexist file"
