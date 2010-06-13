<?php
	echo "PHP-Test in SVN";
	$command  = "echo -e "Startstation\nEndstation\n" | ./fahrplanauskunft ubahn.txt"
	$output = new array();
	$return_val;
	$result = exec ($command, $output, $return_var);
	echo "result: ".$result;
	printv($output);
	echo "return_var: ".$return_var;
?>
