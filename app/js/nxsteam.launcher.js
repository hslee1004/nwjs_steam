nxsteam.launcher = (function () {
	var 
		restify, server, callback, initModule, install_nxl, test_steam ;

	callback = function (req, res, next) {
		res.send('action: ' + req.params.action);
		test_steam();
		// install_nxl();
		//next();
	};
	test_steam = function () {
		try {
		  console.log('test-nxa-steam');
		  var nxa_steam = require('nxa_steam');
		  //console.log('[nxa_nxl.getAppsSettings]', nxa_nxl.getAppsSettings());
		  //var app_str = nxa_steam.getAppsSettings();
		  //var json = JSON.parse(app_str);
		  //console.log('defaultInstallPath : '+json['defaultInstallPath']);
		  var steam_ticket = nxa_steam.getAuthSessionTicket();
		  alert("steam_ticket:"+steam_ticket);
		  console.log(steam_ticket);
		}
		catch(err) {
		  console.log('exception on test_steam'+err.message);
		}
	};
	install_nxl = function () {
		try {
			test_steam();
			var path = require('path');
			var execPath = path.dirname(process.execPath);
			console.log('execPath : '+execPath);
			var execFile = require('child_process').exec, child;
			child = execFile(execPath+'/NexonLauncherSetup.exe',
					function(error,stdout,stderr) { 
						if (error) {
						  console.log(error.stack); 
						  console.log('Error code: '+ error.code); 
						  console.log('Signal received: '+error.signal);
						} 
						console.log('Child Process stdout: '+stdout);
						console.log('Child Process stderr: '+stderr);
					});
		}
		catch(err) {
		  console.log(err.message);
		}
	};
	initModule = function () {
		try {
			//alert("nxsteam.launcher.initModule");
			restify = require('restify');
			server = restify.createServer();
			server.get('/api/nxl/:action', callback);
			server.listen(8080, function() {
			  console.log('%s listening at %s', server.name, server.url);
			});
			//alert("nxsteam.launcher.initModule - done");
		}
		catch(err) {
			alert(err);
		}
	};
	return {
		initModule : initModule,
		install_nxl : install_nxl
	};
}());

//alert("nxsteam.launcher");
