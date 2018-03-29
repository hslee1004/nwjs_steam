nxsteam.api = (function () {
	var
		response, request, verifyAccount, login ;
		cbLogin = function (data) {
			// parse
			// send event - login
		};
		response = function (api, data) {
	    	try {
	    		console.log("in-callback :" + api);
		    	console.log(JSON.stringify(data));
				//var json = JSON.parse(data);
				//console.log('defaultInstallPath : '+json['defaultInstallPath']);
				//$('.greeting-id').append(data.id);
				//$('.greeting-content').append(data.content);
	    	}
			catch(err) {
			  console.log(err.message);
			}		    	
		};
		request = function (api, url, method, post_data, callback) {
		    $.ajax({
		        url: url,
				type: method,
				data : post_data,
				contentType: "application/json; charset=utf-8",
				dataType: "json",		        
		    }).then(function(data) {
		    	try {
			    	console.log(JSON.stringify(data));
			    	callback(data);
		    	}
				catch(err) {
				  console.log(err.message);
				}		    	
		    });
		};
		verifyAccount = function () {
			//alert("called - verified account");
			//request("test", "http://rest-service.guides.spring.io/greeting", "GET", "", callback);
			post = { 
				"id" : "mantistest3",
				"pw" : "1122qq"
			};
			request("login", "http://nss.nexon.net/auth/login", "POST", JSON.stringify(post), callback);
		};
		login = function (id, pw, callback) {
			console.log("id:%s, pw:%s", id, pw);
			post = { 
				"id" : id,
				"pw" : pw
			};
			request("login", "http://nss.nexon.net/auth/login", "POST", JSON.stringify(post), callback);
		};
	return {
		verifyAccount : verifyAccount,
		login : login	
	};
}());

//alert("nxsteam.api");