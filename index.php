<head>
	<title>Fahrplanauskunft</title>
</head>
<body>
	<h1>Fahrplanauskunft U-Bahn Wien</h1>
	<form action='<?php echo $_SERVER["PHP_SELF"]; ?>' method='GET'>
		<table>
			<tr>
				<td>Aktuelle Station:</td><td><input type='text' name='start' /></td>
			</tr>
			<tr>
				<td>Ziel-Station:</td><td><input type='text' name='end' /></td>
			</tr>
			<tr>
				<td /><td><input type='submit'/></td>
			</tr>
		</table>
	</form>
</body>

<?php
	if(isset($_GET['start']) && isset($_GET['end'])) {
		$command  = "echo -e \"".$_GET['start']."\\n".$_GET['end']."\\n\" | ./fahrplanauskunft ubahn.txt";
		$output = array();
		$return_val;
		$result = exec ($command, $output, $return_var);
		//echo "result: ".$result."<br />\n";
		if($return_var == 0) {
			foreach($output as $line) {
				echo $line."<br />\n";
			}
		}
	}
?>
