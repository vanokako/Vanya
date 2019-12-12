generate_table();

function generate_table() {
	let head = window.document.getElementsByTagName('head')[0];
	let style = window.document.createElement('link');
	style.href = '/src/main.css'
	style.rel = 'stylesheet'
	head.appendChild(style)
	var body = document.getElementsByTagName("body")[0];
	var tbl = document.createElement("table");
	tbl.className = 'center';
	 tbl.style.position = "absolute";
	 tbl.style.marginLeft = 650+"px";
	 tbl.style.marginTop = 60 +"px";
	var tblBody = document.createElement("tbody");
	let records = JSON.parse(localStorage["records"]);
	var row = document.createElement("tr");
	var cell = document.createElement("td");
	var cellText = document.createTextNode("Username");
	cell.appendChild(cellText);
	row.appendChild(cell);
	var cell = document.createElement("td");
	var cellText = document.createTextNode("Score");
	cell.appendChild(cellText);
	row.appendChild(cell);
	tblBody.appendChild(row);
	for (var i = 0; i < records.length; i++) {
		var row = document.createElement("tr");
		for (var j = 0; j < 2; j++) {
			var cell = document.createElement("td");
			if (j == 0)
				var cellText = document.createTextNode(records[i].name);
			else
				var cellText = document.createTextNode(records[i].score);

			cell.appendChild(cellText);
			row.appendChild(cell);
		}
		tblBody.appendChild(row);
	}
	tbl.appendChild(tblBody);
	body.appendChild(tbl);
	var button = document.createElement("input");
	button.style.position = 'absolute';
	button.style.marginLeft = 750+"px";
	button.className = 'button1';
	button.type = "button";
	button.value = "Replay";
	button.onclick = () => {
		window.location.href = "/";
	};
	body.appendChild(button);
	tbl.setAttribute("border", "2");
}
