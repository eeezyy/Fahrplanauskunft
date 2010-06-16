<head>
	<title>Fahrplanauskunft</title>
</head>
<body>
	<h1>Fahrplanauskunft U-Bahn Wien</h1>
	<table>
	<tr><td>
	<form onSubmit='getXML()' name='search'>
		<table>
			<tr>
				<td>Aktuelle Station:</td><td><input type='text' name='start' <?php if(isset($_GET['start'])) echo "value='".$_GET['start']."'"; ?>onkeypress='noenter();'/></td>
			</tr>
			<tr>
				<td>Ziel-Station:</td><td><input type='text' name='end' <?php if(isset($_GET['end'])) echo "value='".$_GET['end']."'"; ?>onkeypress='noenter()'/></td>
			</tr>
			<tr>
				<td /><td><input type='button' value='suchen' onSubmit='getXML()' onclick='getXML()'/></td>
			</tr>
		</table>
	</form>
	</td>
	<td><div name='time'></div></td>
	<tr>
	</table>
	
		<script src="http://maps.google.com/maps?file=api&v=2&key=ABQIAAAAzf03MVeHzU_wJ2vX5hn7zRRIFV45slZifYGa4RUcYNz-B1Cj2RRE8AfSxR8gxJM8apFR4c-ItN7yHQ" type="text/javascript"></script>
    <script type="text/javascript" src="mapstraction.js"></script>
	<div id="mapstraction" style="position:left;  height: 600px; width: 100%; border: 1px solid black"></div>
	<script src="jquery.js" type="text/javascript"></script>
	<script src="jqXMLUtils.js" type="text/javascript"></script>
	<script type="text/javascript">
		function getXML()
		{
			$.ajax(
			{
				type: "GET", url: "output.xml.php", data: {start: document.forms['search'].start.value, end: document.forms['search'].end.value}, dataType: "xml", complete: function(data)
				{
					//var myXMLDocumentObject = XMLObjectifier.textToXML(text);
					var itemsXML = $.xmlToJSON(data.responseXML);
					mapstraction.removeAllMarkers();
					var markers = new Array();
					var pointPrev = null;
					var markPrev = null;
					//if(itemsXML.time.length > 0 && (typeof(itemsXML.time[0].Text) != "undefined" || itemsXML.time[0].Text != ''))
					if(typeof(itemsXML.time[0].Text) != "undefined" && itemsXML.time[0].Text != "")
						document.getElementsByName('time')[0].innerHTML = "<div style='font-size:20px'><b>Fahrtdauer: </b>"+itemsXML.time[0].Text+" min.</div>";
					else
						document.getElementsByName('time')[0].innerHTML = '';
					if(itemsXML.station)
					for(var i=0; i < itemsXML.station.length; i++) {
						var bubbleinfo = itemsXML.station[i].name[0].Text;
						var point = new LatLonPoint(itemsXML.station[i].lat[0].Text, itemsXML.station[i].lon[0].Text);
						markers[i] = point;
						var marker = new Marker(point);
						marker.setInfoBubble(bubbleinfo);
						marker.setHover(true);
						marker.setIcon('u.png', [18,18]);
						marker.setShadowIcon('u.png', [0, 0]);
						mapstraction.addMarker(marker);
						if(pointPrev != null && markPrev != null) {
							var polyline = new Polyline([pointPrev, point]);
							polyline.setColor(markColor(markPrev));
							polyline.setOpacity(0.7);
							mapstraction.addPolyline(polyline);
						}
						pointPrev = point;
						markPrev = itemsXML.station[i].mark[0].Text;
					}
					if(markers.length > 0)
						mapstraction.centerAndZoomOnPoints(markers);
					else
						mapstraction.setCenterAndZoom(centerPoint, 12);
				}
			});
		}
		
		function noenter(event) {
			if (event && event.which == 13)
				getXML();
			return false;
		}
		
		function markColor($mark) {
			switch($mark) {
				case 'u1':
					return '#ff0000';
				case 'u2':
					return '#9f66aa';
				case 'u3':
					return '#f5821f';
				case 'u4':
					return '#00a650';
				case 'u6':
					return '#a76534';
				default:
					return '#000000';
			}
		}
		
		
		var mapstraction = new Mapstraction('mapstraction','google');
		var markers = new Array();
		var point;
		mapstraction.addLargeControls();
		mapstraction.setMapType(Mapstraction.ROAD);
		var centerPoint = new LatLonPoint(48.2092062, 16.3727778);
		mapstraction.setCenterAndZoom(centerPoint, 12);
		mapstraction.enableScrollWheelZoom();
		if(markers.length > 0)
			mapstraction.centerAndZoomOnPoints(markers);
		getXML();
</script>
</body>
