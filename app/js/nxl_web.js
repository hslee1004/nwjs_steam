// http://mcavage.me/node-restify/
// https://gentlenode.com/journal/node-5-building-a-rest-api-with-restify-and-monk/46
// purpose : implement local rest api server
// Todo : need to improve this module
//
var restify = require('restify');

function respond(req, res, next) {
  res.send('action: ' + req.params.action);
  // ex : launch Nexon Launcher Installer
  install_nxl();
  next();
}

var server = restify.createServer();
server.get('/api/nxl/:action', respond);

server.listen(8080, function() {
  console.log('%s listening at %s', server.name, server.url);
});

function install_nxl() {
try {
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
}

