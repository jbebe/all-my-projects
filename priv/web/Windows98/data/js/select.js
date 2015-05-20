function load_select(){
	var doc = window.document;
	var desktop = doc.getElementById("desktop");
	var selector = doc.getElementById("select");
	var context_menu = doc.getElementById("context_menu");
	var i;
	var ax1,ay1,ax2,ay2,bx1,bx2,by1,by2;
	var t;
	var running_apps = {};
	
	var title = doc.getElementsByTagName("title")[0];
	var tempX, tempY,startX,startY,block;
	var IE = (doc.all) ? true : false; if (!IE) doc.captureEvents(Event.MOUSEMOVE);
	var xmlhttp = (window.XMLHttpRequest) ?  new window.XMLHttpRequest : new ActiveXObject("Microsoft.XMLHTTP");
	doc.oncontextmenu = function(){ return false; }
	
	create_icon("Unknown.bat","Icon_1");
	create_icon("CALC.exe","Icon_3");
	create_icon("My Folder","Icon_4");
	create_icon("docmnt1.txt","Icon_2");
	create_icon("Bin","Icon_32");
	
	doc.onmouseover = function(e){
		e = e || window.event;
		if (e.target.className == "submenu"){
			t = setTimeout("document.getElementById('context_menu_inner').childNodes[1].childNodes[1].style.display = 'block'",700);
		}
		else {
			document.getElementById("context_menu_inner").childNodes[1].onmouseout = function(){ clearTimeout(t); }
		}
	}
	
	/* doc.onkeydown = function(e){
		e = e || window.event;
		if (e.shiftKey) alert("SHIFT");
		if (e.altKey) alert("ALT");
		if (e.ctrlKey) alert("Control");
	} */
	
	doc.onmousedown = function(e) {
		e = e || window.event;
		if (e.target.childNodes[1].className == "sub"){
			close_frame_menu();
			e.target.style.backgroundColor = "#040082";
			e.target.style.color = "#fff";
			e.target.childNodes[1].style.display = "block";
		}
		else {
			close_frame_menu();
		}
		if (doc.getElementById("context_menu").style.display == "block" && e.target.parentNode.id != "context_menu_inner")
			doc.getElementById("context_menu").style.display = "none";
		if(e.target.id == "startorb_inner") open_startmenu();
		else close_startmenu();
		
		if (IE){
			tempX = event.clientX + doc.body.scrollLeft;
			tempY = event.clientY + doc.body.scrollTop;
		} 
		else {
			tempX = e.pageX;
			tempY = e.pageY;
		}	
		if (tempX < 0) tempX = 0;
		if (tempY < 0) tempY = 0;
		startX = tempX;
		startY = tempY;
		
		if (e.target.id == "desktop"){
			clear_icon_selection();
			// div elkészítése
			block = doc.createElement("div");
			block.className = "select_rect";
			block.style.top = startY + "px";
			block.style.left = startX + "px";
			selector.appendChild(block);
			
			doc.onmousemove = function(e){
				var deskNodes = desktop.childNodes;
				if (IE) {
					movetempX = event.clientX + doc.body.scrollLeft;
					movetempY = event.clientY + doc.body.scrollTop;
				} else {
					movetempX = e.pageX;
					movetempY = e.pageY;
				}	
				if (movetempX < 0) movetempX = 0;
				if (movetempY < 0) movetempY = 0;
				// fedés
				
				// kijelölés
				if (startX < movetempX){
					ax1 = startX;
					ax2 = movetempX;
				}
				else{
					ax1 = movetempX;
					ax2 = startX;
				}
				if(startY < movetempY){
					ay1 = startY;
					ay2 = movetempY;
				}
				else{
					ay1 = movetempY;
					ay2 = startY;
				}

				for (var i = 0;i < deskNodes.length; i++){
					bx1 = deskNodes[i].offsetLeft + 19;
					by1 = deskNodes[i].offsetTop + 2;
					bx2 = bx1+32;
					by2 = by1+29;
					// alert("ax1: " + ax1 + "<br/>" +"ay1: " + ay1 + "<br/>" +"ax2: " + ax2 + "<br/>" +"ay2: " + ay2 + "<br/>" +"bx1: " + bx1 + "<br/>" +"by1: " + by1 + "<br/>" +	"bx2: " + bx2 + "<br/>" +				"by2: " + by2 + "<br/>");
					if(ax1 < bx2 && ax2 > bx1 && ay1 < by2 && ay2 > by1){
						deskNodes[i].style.backgroundImage = "url('data/img/icon/" + deskNodes[i].getAttribute("alt") + "_on.gif')";
						deskNodes[i].childNodes[0].className = "on";
					}
					else {
						deskNodes[i].style.backgroundImage = "url('data/img/icon/" + deskNodes[i].getAttribute("alt") + ".gif')";
						deskNodes[i].childNodes[0].className = "";
					}
				}
				// 32 29			
				
				if (movetempX < startX && movetempY > startY){
					block.style.width = (startX - movetempX) + "px";     //           |
					block.style.left = movetempX + "px";                 //  ---------|-----------
					block.style.height = (movetempY - startY) + "px";    //      #    |
					return false;
				}
				if ( movetempX < startX && movetempY < startY ){
					block.style.width = (startX - movetempX) + "px";     //      #    |
					block.style.left = movetempX + "px";                 //  ---------|-----------
					block.style.top = movetempY + "px";                  //           |
					block.style.height = (startY - movetempY) + "px";
					return false;
				}
				if ( movetempX > startX && movetempY < startY ){          //           |    #
					block.style.width = (movetempX-startX) + "px";        //  ---------|-----------
					block.style.top = movetempY + "px";                   //           |
					block.style.height = (startY - movetempY) + "px";
					return false;
				}
				if(true){                                                 //           |
					block.style.width = (movetempX-startX) + "px";        //  ---------|-----------
					block.style.height = (movetempY-startY) + "px";       //           |     #
					return false;
				}
			}
		}
		else {
			if(e.target.className == "submenu" && e.target.childNodes[1].style.display == "none"){
				e.target.childNodes[1].style.display = "block";
				return false;
			}
			if (e.target.parentNode.className != "sub")
				document.getElementById("context_menu_inner").childNodes[1].childNodes[1].style.display = "none";
			if (e.target.className.indexOf("icon") == 0)
				return false;
			if (e.target.id == "titlebar"){
				var window_frame = (e.target.parentNode.className.indexOf("app") != -1) ? doc.getElementById("applications").getElementsByTagName("div")[0] : doc.getElementById("dialog").getElementsByTagName("div")[0];
				window_frame.style.top = window_frame.offsetTop + "px";
				window_frame.style.left = window_frame.offsetLeft + "px";
				var differenceY = startY - window_frame.offsetTop;
				var differenceX = startX - window_frame.offsetLeft;
				doc.onmousemove = function(e){
					e = e || window.event;
					if (IE) {
						movetempX = event.clientX + doc.body.scrollLeft;
						movetempY = event.clientY + doc.body.scrollTop;
					} else {
						movetempX = e.pageX;
						movetempY = e.pageY;
					}	
					if (movetempX < 0) movetempX = 0;
					if (movetempY < 0) movetempY = 0;
					window_frame.style.top = movetempY - differenceY + "px";
					window_frame.style.left = movetempX - differenceX + "px";
				}
				return false;
			}
		}	
	}
	
	doc.onmouseup = function(e) {
		doc.onmousemove = null;
		var leftright = mouse_event(e);
		if (leftright == "RIGHT"){
			e = e|| window.event;
			var left= parseInt(e.clientX);
			var top = parseInt(e.clientY);
			context_menu.style.top = top + "px";
			context_menu.style.left = left + "px";
			context_menu.style.display = "block";
		}
		while ( selector.getElementsByTagName("*").length > 0 )
			selector.removeChild(doc.getElementById("select").firstChild);
	}
	
	doc.onclick = function(e){
		if (e.target.className.indexOf("icon") != -1){
			clear_icon_selection();
			if (e.target.className.indexOf("selected") == -1){
				e.target.style.backgroundImage = "url('data/img/icon/" + e.target.getAttribute("alt") + "_on.gif')";
				e.target.childNodes[0].className = "on";
			}
			// switch(e.target.innerHTML)
		}
	}
	
	doc.ondblclick = function(e){
		e = e|| window.event;
		if (e.target.className == "icon"){
			var filename = e.target.childNodes[0].innerHTML.substr(0,e.target.childNodes[0].innerHTML.length-4).toLowerCase();
			var extension = e.target.childNodes[0].innerHTML.substr(e.target.childNodes[0].innerHTML.length-3,e.target.childNodes[0].innerHTML.length).toLowerCase();
			switch(e.target.childNodes[0].innerHTML){
				case "My Folder":
					alert("Open my folder");
					break;
				case "My Computer":
					alert("Open my computer");
					break;
				case "Bin":
					alert("Open bin!");
					break;
				default:
					switch(extension){
						case "exe":
							file_execute(filename);
							break;
						case "txt":
							alert("Run notepad");
							break;
						case "doc":
							alert("Run wysiwyg editor");
							break;
						default:
							dialog_window("Error - File Type","Unknown application. Please reboot.",false);
							break;
					}
					break;
			}
		}
	}
	
	// functions
	function close_frame_menu(){
		var elems = doc.getElementById("applications").getElementsByTagName("div");
		for (var i = 0;i < elems.length; i++){
			if(elems[i].className == "sub"){
				elems[i].style.display = "none";
				elems[i].parentNode.style.backgroundColor = "#c0c0c0";
				elems[i].parentNode.style.color = "#000";
			}
		}
	}
	function start_application(){
		
	
	}
	
	function dialog_window(title,text,yesno){
		doc.getElementById("dialog").innerHTML = '<div class="dialog_window"> \
				<div class="dialog_window_inner"> \
					<div class="titlebar disableSelect" id="titlebar"> \
						&nbsp;' + title + ' \
						<div class="close_button"> \
							<div class="close_button_inner"></div> \
						</div> \
					</div> \
					<div class="logo"></div> \
					<div class="message disableSelect">' + text + '</div> \
					<div class="buttons"> \
						<div class="button disableSelect"><button onclick="document.getElementById(\'dialog\').removeChild(document.getElementById(\'dialog\').firstChild);"><div class="button_inner">Ok</div></button></div> \
						' + (yesno ? '<div class="button disableSelect"><button onclick="document.getElementById(\'dialog\').removeChild(document.getElementById(\'dialog\').firstChild);">Cancel</button></div>' : '') + ' \
					</div> \
				</div> \
			</div> ';
	}
	
	function file_execute(file){
		if (running_apps[file]) return;
		running_apps[file] = true;
		var js = doc.createElement("script");
		js.src="data/apps/" + file + "/" + file + ".js";
		doc.getElementsByTagName("head")[0].appendChild(js);
		xmlhttp.open("GET", "data/apps/" + file + "/" + file + ".html", true);
		xmlhttp.send();
		xmlhttp.onreadystatechange = function(){
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200){
				document.getElementById("applications").innerHTML += xmlhttp.responseText;
			}
		}
	}
	
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
	
	function open_startmenu(){
		doc.getElementById("startmenu").style.display = "block";
		var Orb = doc.getElementById("startorb_inner");
		if (Orb.style.backgroundImage.indexOf("_on") != -1){
		close_startmenu(); return false;
		}
		var OrbP = doc.getElementById("startorb");
		OrbP.style.border = "#000 1px solid";
		Orb.style.backgroundImage = "url('data/img/theme/taskbar_logo_on.gif')";
		Orb.style.backgroundPosition = "2px 2px";
		Orb.style.borderBottom = "#fff 1px solid";
		Orb.style.borderRight = "#fff 1px solid";
		Orb.style.borderLeft = "#808080 1px solid";
		Orb.style.borderTop = "#808080 1px solid";
	}
	
	function close_startmenu(){
		var Orb = doc.getElementById("startorb_inner");
		var OrbP = doc.getElementById("startorb");
		OrbP.style.borderBottom = "#000 1px solid";
		OrbP.style.borderRight = "#000 1px solid";
		OrbP.style.borderLeft = "#fff 1px solid";
		OrbP.style.borderTop = "#fff 1px solid";
		Orb.style.backgroundImage = "url('data/img/theme/taskbar_logo.gif')";
		Orb.style.backgroundPosition = "3px 3px";
		Orb.style.borderLeft = "#fff 1px solid";
		Orb.style.borderTop = "#fff 1px solid";
		Orb.style.borderBottom = "#808080 1px solid";
		Orb.style.borderRight = "#808080 1px solid";
		doc.getElementById("startmenu").style.display = "none";
	}
	
	function disable_context(e){
		e = e|| window.event;
		e.cancelBubble = true;
		e.returnValue = false;
		if(e.stopPropagation) e.stopPropagation();
		if(e.preventDefault) e.preventDefault();
		return false;
	}
	
	function mouse_event(e){
		var evt = (e==null) ? event : e;
		var clickType = "LEFT";
		if (evt.type!="mouseup") 
			return true;
		if (evt.which){
			if (evt.which==3) 
				clickType="RIGHT";
		}
		else 
			if (evt.button){
				if (evt.button==2) 
					clickType="RIGHT";
			}  
		return clickType;
	}
	
	function clear_icon_selection(){
		for (var i = 0;i < desktop.childNodes.length; i++){
			desktop.childNodes[i].setAttribute("style",desktop.childNodes[i].getAttribute("style").replace("_on",""));
			desktop.childNodes[i].childNodes[0].className = null;
		}
	}
}
if (window.addEventListener) window.addEventListener("load",load_select);
else window.attachEvent("onload",load_select);