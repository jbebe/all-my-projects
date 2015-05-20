function load_functions(){
	var doc = window.document;
	var desktop = doc.getElementById("desktop");

	function create_icon(name,url){
		var icon = doc.createElement("div");
		icon.className = "icon";
		icon.setAttribute("alt",url);
		if (name == "Bin")
			icon.id = "bin";
		icon.style.backgroundImage = "url('data/img/icon/" + url + ".gif')";
		var icon_span = doc.createElement("div");
		icon_span.innerHTML = name;		
		
		desktop.appendChild(icon).appendChild(icon_span);
		
		var temp = doc.createElement("img");
		temp.src = "data/img/icon/" + url + "_on.gif";
		return 1;
	}
	
	create_icon("Unknown","Icon_1");
	create_icon("Calculator","Icon_3");
	create_icon("My Folder","Icon_4");
	create_icon("document1","Icon_2");
	create_icon("Bin","Icon_32");
	
}
if (window.addEventListener) window.addEventListener("load",load_functions);
else window.attachEvent("onload",load_functions);