<?php
$XML_geo = file_get_contents('geo.xml');
$objXML_geo = simplexml_load_string($XML_geo);
$XML_station = file_get_contents('output.xml.php');
$objXML_station = simplexml_load_string($XML_geo);
foreach($objXML->children() as $station) {
		echo "\t<station>\n";
		echo "\t\t<name>".$station['name']."</name>\n";
		echo "\t\t<lon>".$station['lon']."</lon>\n";
		echo "\t\t<lat>".$station['lat']."</lat>\n";
		echo "\t</station>\n";
}

function umlaute($text)
{
$search  = array ('ä', 'ö', 'ü', 'ß', '-');
$replace = array ('ae', 'oe', 'ue', 'ss', ' ');
$str  = str_replace($search, $replace, $text);
return $str;
}
?>