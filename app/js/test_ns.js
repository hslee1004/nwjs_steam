var Datastore, db, defaultMenu, gui, isDebug, path, pkg, preventDefault, spinner_cover_opts, spinner_opts, upd, updater, win;
var nexon_launcher;

gui = require('nw.gui');
path = require('path');
pkg = require('../package.json');
updater = require('node-webkit-updater');

upd = new updater(pkg);
win = gui.Window.get();
isDebug = true;
win.title = gui.App.manifest.name + ' ' + gui.App.manifest.version;
win.focus();
win.show();

//gui.Window.get().showDevTools();
gui.App.setCrashDumpDir(gui.App.dataPath);


// test
console.log('LOG-1');
console.log(gui.App.dataPath);                // C:\Users\hslee\AppData\Local\nn-Test
console.log(require('nw.gui').App.dataPath);  // C:\Users\hslee\AppData\Local\nn-Test
console.log(process.env.HOME);                // undefined

try {
  console.log('test-nxa-nxl');
  var nxa_nxl = require('nxa_nxl');
  //console.log('[nxa_nxl.getAppsSettings]', nxa_nxl.getAppsSettings());
  var app_str = nxa_nxl.getAppsSettings();
  console.log(app_str);
  var json = JSON.parse(app_str);
  console.log('defaultInstallPath : '+json['defaultInstallPath']);
}
catch(err) {
  console.log('exception on getAppsSettings'+err.message);
}

// try {
//   window.addEventListener("dragover", preventDefault, false);
//   window.addEventListener("drop", preventDefault, false);
//   window.addEventListener("dragstart", preventDefault, false);
// }
// catch(err) {
//   console.log( err.message);
// }
