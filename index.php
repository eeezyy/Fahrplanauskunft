<?php
	echo "PHP-Test in SVN<br />\n";
	$command  = "echo -e \"Startstation\\nEndstation\\n\" | ./fahrplanauskunft ubahn.txt";
	$output = array();
	$return_val;
	$result = exec ($command, $output, $return_var);
	echo "result: ".$result."<br />\n";
	foreach($output as $line) {
		echo $line."<br />\n";
	}
	echo "return_var: ".$return_var;
?>
