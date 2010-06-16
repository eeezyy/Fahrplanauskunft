<?php
	function umlaute($text)
	{
		$text = utf8_decode($text);
		$search  = array ('ä', 'ö', 'ü', 'ß', '-');
		$replace = array ('ae', 'oe', 'ue', 'ss', ' ');
		//$str  = str_replace($search, $replace, $text);
		$trans = array("ä" => "ae", "ö" => "oe", "ü" => "ue", "ß" => "ss");
		$str = strtr($text, $trans);
		return $str;
	}

	header('Content-Type: application/xml; charset=UTF-8');
	echo "<?xml version='1.0' encoding='UTF-8' standalone='yes'?>\n";
	echo "<stations>\n";

	if(isset($_GET['start']) && isset($_GET['end'])) {
		$objXML_geo = simplexml_load_file('geo.xml');
		$command  = "echo -e \"".umlaute($_GET['start'])."\\n".umlaute($_GET['end'])."\\n\" | ./fahrplanauskunft ubahn.txt";
		$output = array();
		$return_val;
		$result = exec ($command, $output, $return_var);
		$time = explode('Fahrtdauer: ', $output[count($output)-1]);
		echo "\t<time>".$time[1]."</time>\n";
		if($return_var == 0) {
			for($i = 3; $i < count($output); $i += 2) {
				$station = NULL;
				foreach($objXML_geo->station as $item) {
					if(umlaute($item->name) == umlaute($output[$i])) {
						$station = $item;
						break;
					}
				}
				if($station != NULL) {
					echo "\t<station>\n";
					echo "\t\t<name>".$station->name."</name>\n";
					echo "\t\t<lon>".$station->lon."</lon>\n";
					echo "\t\t<lat>".$station->lat."</lat>\n";
					$mark = explode('-> ', $output[$i+1]);
					echo "\t\t<mark>".$mark[1]."</mark>\n";
					echo "\t</station>\n";
				} else {
					echo "---------------------------------".$output[$i]."\n";
				}
			}
		}
	}
	echo "</stations>";

?>