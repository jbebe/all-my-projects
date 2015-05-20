(function(){
	// define variables
	var doc = window.document;
	var issetEl,objHolder,i,element,parent;
	var disturb = true;
	var arrHolder,arrHolder2 = [];
	var miniLibBase=function(){};
	miniLibBase.prototype={
		elem:{},
	// ======================================== //
	//						 S  E  L  E  C  T  O  R  S						  //
	// ======================================== //
		// return element to manage simple args
		r:function(){ return this.elem; },
		doc:function(){ this.elem = doc; return this; }
		// document.getElementById
		i:function(string){
			this.elem = doc.getElementById(string);
			return this;
		},
		// document.getElementsByTagName
		t:function(string,parent){
			if(string=="body"){
				this.elem = doc.getElementsByTagName("body")[0]; return this;
			}
			if(string=="head"){
				this.elem = doc.getElementsByTagName("head")[0]; return this;
			}
			issetEl  = doc.getElementById(parent) || doc;
			objHolder = issetEl.getElementsByTagName(string);
			this.elem = (objHolder.length > 1) ? objHolder : objHolder[0];
			return this;
		},
		// document.getElementsByClassName
		c:function(string,parent){
			issetEl  = doc.getElementById(parent) || doc;
			if(!doc.getElementsByClassName){
				arrHolder = issetEl.getElementsByTagName("*");
				arrHolder2.length = 0;
				for(i = 0; i<arrHolder.length;i++){
					if(arrHolder[i].className == string || arrHolder[i].className.indexOf(" "+string)!=-1 || arrHolder[i].className.indexOf(string+" ")!=-1) 
						arrHolder2.push(arrHolder[i]);
				}
				this.elem = ((arrHolder2.length > 1) ? arrHolder2 : arrHolder2[0]);
				return this;
			}
			else{
				objHolder = issetEl.getElementsByClassName(string);
				this.elem = ((objHolder.length > 1) ? objHolder : objHolder[0]);
				return this;
			}
		},
	// ======================================== //
	//		W R I T E  /  R E A D				//
	// ======================================== //
		// html write, read
		h:function(string){
			objHolder = this.elem;
			if (string){
				if (objHolder[0]){
					for (i=0;i<objHolder.length;i++){
						if (objHolder[i].value)
							objHolder[i].value = (typeof string == "function") ? string() : string;
						else
							objHolder[i].innerHTML = (typeof string == "function") ? string() : string;
					}
				}
				else{
					if (objHolder.value)
						objHolder.value = (typeof string == "function") ? string() : string;
					else
						objHolder.innerHTML = (typeof string == "function") ? string() : string;
				}
			}
			else
				return this.elem.innerHTML;
			return this;
		},
		// attribute write, read
		a:function(attribute,option){
			// attribute write
			if(option)
			{
				// if array, set every element to that attribute
				if(this.elem[0]){
					for (i=0;i<this.elem.length;i++){
						if(!this.elem[i].getAttribute(attribute)) this.elem[i].setAttribute(attribute,"");
						if(this.elem[i].getAttribute(attribute).indexOf(option) != -1) continue;
						if (this.elem[i].getAttribute(attribute) == ""){
							this.elem[i].setAttribute(attribute,option);
						}
						else{
							// if style => ";"
							if (attribute == "style") this.elem[i].setAttribute(attribute,this.elem[i].getAttribute(attribute)+";"+option);
							// if not: " "
							else this.elem[i].setAttribute(attribute,this.elem[i].getAttribute(attribute)+" "+option);
						}
					}
				}
				// if not an array, set only one.
				else{
					if(!this.elem.getAttribute(attribute)) this.elem.setAttribute(attribute,"");
					if(this.elem.getAttribute(attribute).indexOf(option) != -1) return this;
					if (this.elem.getAttribute(attribute) == ""){
						this.elem.setAttribute(attribute,option);
					}
					else {
						// if style => ";"
						if (attribute == "style") this.elem.setAttribute(attribute,this.elem.getAttribute(attribute)+";"+option);
						// if not: " "
						else this.elem.setAttribute(attribute,this.elem.getAttribute(attribute)+" "+option);
					}
				}
				return this;
			}
			else {
				// if attribute is the only parameter, just read
				// if array, read every attribute to the array
				if (this.elem[0]) return this.elem[0].getAttribute(attribute);
				// just the one
				else return this.elem.getAttribute(attribute);
			}
		},
		// delete element(s)
		d:function(){
			objHolder = doc.createElement("div");
			objHolder.id = "objHolder";
			doc.getElementsByTagName("body")[0].appendChild(objHolder);
			if (this.elem[0]){
				i = this.elem.length;
				while(i--){
					objHolder.appendChild(this.elem[i]);
				}
			}
			else objHolder.appendChild(this.elem);
			doc.getElementsByTagName("body")[0].removeChild(objHolder);
		},
	// ======================================== //
	//										  A J A X											//
	// ======================================== //
		x:function(server,data,type){
			// get http var 
			var ajaxResponse = "";
			var http = false;
			if(typeof ActiveXObject != "undefined") {
				try {http = new ActiveXObject("Msxml2.XMLHTTP");}
				catch (e) {
					try {http = new ActiveXObject("Microsoft.XMLHTTP");}
					catch (E) {http = false;}
				}
			} else if (window.XMLHttpRequest) {
				try {http = new XMLHttpRequest();}
				catch (e) {http = false;}
			}
			if(!http||!server) return this;
			if (http.overrideMimeType) 
				http.overrideMimeType("text/xml");
			if (!type){
				setTimeout("return this",2000);
				http.open("GET", server+"?"+data, false);
				http.onreadystatechange = function() {
					if(http.readyState == 4 && http.status == 200)
						if (http.responseText)
							ajaxResponse = http.responseText;
				};
				http.send(null);
			}
			else{
				setTimeout("return this",2000);
				http.open("POST", server, false);
				http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
				http.setRequestHeader("Content-length", data.length);
				http.setRequestHeader("Connection", "close");
				http.onreadystatechange = function() {
					if(http.readyState == 4 && http.status == 200)
						if (http.responseText)
							ajaxResponse = http.responseText;
				};
				http.send(data);
			}
			return ajaxResponse;
		},
	// ======================================== //
	//								A  N  I  M  A  T  E								  //
	// ======================================== //
		m:function(target, procLength, type, sin,call)
		{
			if (disturb){
				element = this.elem;
				var elementStyle = this.elem.style;
				var fps = 25;
				var elapsedTime,start;
				switch (type){
					case "width":start = element.offsetWidth;break;
					case "height":start = element.offsetHeight;break;
					case "left":start = element.offsetLeft;break;
					case "top":start = element.offsetTop;break;
					default:start = 0;break;
				}
				var dispX = target;
				var startTime = new Date().getTime();
				disturb = false;
				if (sin == "sin"){
					var freq = Math.PI / (2 * procLength); // frequency
					var tmrXY = setInterval(
						function() {
							elapsedTime = new Date().getTime() - startTime;
							if (elapsedTime < procLength) {
							var f = Math.abs(Math.sin(elapsedTime * freq));
							elementStyle[type] = Math.round(f * dispX + start) +"px";
							}
							else {
							clearInterval(tmrXY);
							elementStyle[type] = dispX+start+"px";
							disturb = true;
							(typeof call == "function") ? call() : false;
							}
						}, fps
					);
				}
				else{
					var linX = Math.round(( dispX / ( procLength / fps ) ));
					var linXX = linX;
					var tmrXY = setInterval(
						function() {
							elapsedTime = new Date().getTime() - startTime;
							if (elapsedTime < procLength) {
								linX = linX+linXX;
								elementStyle[type] = linX + start +"px";
							}
							else {
								clearInterval(tmrXY);
								elementStyle[type] = dispX+start+"px";
								disturb  = true;
								(typeof call == "function") ? call() : false;
							}
							}, fps
					);
				}
			}
			return this;
		},
	// ======================================== //
	//								S		T		Y		L		E							  //
	// ======================================== //
		_mt:function(x){this.elem.style.marginTop = x;return this;},
		_mb:function(x){this.elem.style.marginBottom = x;return this;},
		_ml:function(x){this.elem.style.marginLeft = x;return this;},
		_mr:function(x){this.elem.style.marginRight = x;return this;},
		_m:function(x){this.elem.style.margin = x;return this;},
		_pt:function(x){this.elem.style.paddingTop = x;return this;},
		_pb:function(x){this.elem.style.paddingBottom = x;return this;},
		_pl:function(x){this.elem.style.paddingLeft = x;return this;},
		_pr:function(x){this.elem.style.paddingRight = x;return this;},
		_p:function(x){this.elem.style.padding = x;return this;},
		_w:function(x){this.elem.style.width = x;return this;},
		_h:function(x){this.elem.style.height = x;return this;},
		_d:function(x){this.elem.style.display = x;return this;},
		_bg:function(x){this.elem.style.background = x;return this;},
		_fl:function(x){this.elem.style.float = x;return this;},
		_b:function(x){this.elem.style.border = x;return this;},
		_bt:function(x){this.elem.style.borderTop = x;return this;},
		_bb:function(x){this.elem.style.borderBottom = x;return this;},
		_bl:function(x){this.elem.style.borderLeft = x;return this;},
		_br:function(x){this.elem.style.borderRight = x;return this;},
		_f:function(x){this.elem.style.font = x;return this;},
		_c:function(x){this.elem.style.color = x;return this;},
		_pos:function(x){this.elem.style.position = x;return this;},
		_bsh:function(x){this.elem.style.boxShadow = x;return this;},
		_bra:function(x){this.elem.style.borderRadius = x;return this;},
		_td:function(x){this.elem.style.textDecoration = x;return this;},
		_ts:function(x){this.elem.style.textShadow = x;return this;},
		_ta:function(x){this.elem.style.textAlign = x;return this;},
		// ======================================== //
		//							E		V		E	N		T		S							  //
		// ======================================== //
		on:function(string,call,loop){
			if (this.elem[0]){
				arrHolder = this.elem;
				objHolder = function(){	if (loop=="loop") setInterval(call,25);	else call(); };
				for (i=0;i<arrHolder.length;i++){
					eval("arrHolder["+i+"].on"+string+" = objHolder;");					
				}
			}
			else {
				objHolder = this.elem;
				var objFunc = function(){
					if (loop=="loop") setInterval(call,25);
					else { call();
					if (loop=="once") eval("objHolder.on"+string+" = null;"); }
				};
				eval("objHolder.on"+string+" = objFunc;");
			}
			return this;
		},
		// ======================================== //
		//							C		R		E		A		T		E						  //
		// ======================================== //
		e:function(string){
			if (string.indexOf("#") == -1 && string.indexOf(".") == -1){
				objHolder = doc.createElement(string);
				this.elem.appendChild(objHolder);
				this.elem = objHolder;
				return this;
			}
			else {
				if (string.match(/^[a-zA-Z0-9_]*[#][a-zA-Z0-9_]*/)){ // id
					arrHolder = string.split("#");
					objHolder = doc.createElement(arrHolder[0]);
					objHolder.id = arrHolder[1];
					this.elem.appendChild(objHolder);
					this.elem = objHolder;
					return this;
				}
				if (string.match(/^[a-zA-Z0-9_]*[.][a-zA-Z0-9_]*/)){ // class
					arrHolder = string.split(".");
					objHolder = doc.createElement(arrHolder[0]);
					objHolder.id = arrHolder[1];
					this.elem.appendChild(objHolder);
					this.elem = objHolder;
					return this;
				}
			}
			return this;
		},
		load:function(call){
			if (window.addEventListener) window.addEventListener("load",call);
			else window.attachEvent("onload",call);
			return this;
		},
		include:function(url){
			if(url.indexOf(".js") > 0){
				var script = doc.createElement("script");script.type = "text/javascript"; 
				script.src = url;doc.getElementsByTagName("head")[0].appendChild(script);
			}
			if(url.indexOf(".css") > 0){
				var css = doc.createElement("link");css.rel = "stylesheet";
				css.type = "text/css";css.href = url;doc.getElementsByTagName("head")[0].appendChild(css);
			}
			return this;
		}
	};
	window.d= new miniLibBase();
})();