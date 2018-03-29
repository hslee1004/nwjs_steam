// #account_mapping=open
//
nxsteam.shell = (function () {
	var
		configMap = {
			anchor_schema_map : {
				account_mapping : { open : true, clsoed : true },
				login : { open : true, clsoed : true },
				step : { status : "login"}
			}
		},
		stateMap = { 
			$container : null,
			anchor_map : {},
		},
		jqueryMap = {},
		setJqueryMap, setStep, toggleDialog, 
		onHashChange, onClickPlayGame, onClickLogin, onClickYesPlayGame,
		spin, initKonami, initKonami;
	//
	setJqueryMap = function() {
		var $container = stateMap.$container;
		setJqueryMap = { $container : $container};

	};
	setStep = function (step) {
		window.location.hash = "step=" + step;
	};
	toggleDialog = function ( status ) {
		//alert("toggle dialog : " + status);
		$('#nxl-loading').hide();
		$('#nxl-account-mapping').hide();
		$('#nxl-login').hide();
		$('#nxl-launch-game').hide();
		$('#nxl-account-confirmation').hide();
		$('#nxl-email-verification').hide();

		if (!status) {
			$('#nxl-loading').show();
			spin();
			setTimeout(function () {setStep("account_mapping");}, 1500);
		}

		if (status == "account_mapping") {
			//alert("show account mapping");
			$('#nxl-account-mapping').show();
		}

		if (status == "launch_game") 
			$('#nxl-launch-game').show();

		if (status == "login") 
			$('#nxl-login').show();

		if (status == "account_confirmation") 
			$('#nxl-account-confirmation').show();

		if (status == "email_verification") 
			$('#nxl-email-verification').show();

	};
	//
	onHashChange = function(event) {
		//alert("onHashChange");
		var
			anchor_map_proposed ;
		try {
			anchor_map_proposed = $.uriAnchor.makeAnchorMap();			
		}
		catch (error) {

		}
		stateMap.anchor_map = anchor_map_proposed;
		s_step = anchor_map_proposed.step;
		//alert("step : " + s_step);
		toggleDialog(s_step);
		return false;
	};
	spin = function (bShow) {
		var opts = {
		  lines: 13 // The number of lines to draw
		, length: 13 // The length of each line
		, width: 8 // The line thickness
		, radius: 23 // The radius of the inner circle
		, scale: 1 // Scales overall size of the spinner
		, corners: 1 // Corner roundness (0..1)
		, color: '#000' // #rgb or #rrggbb or array of colors
		, opacity: 0.25 // Opacity of the lines
		, rotate: 0 // The rotation offset
		, direction: 1 // 1: clockwise, -1: counterclockwise
		, speed: 1 // Rounds per second
		, trail: 60 // Afterglow percentage
		, fps: 20 // Frames per second when using setTimeout() as a fallback for CSS
		, zIndex: 2e9 // The z-index (defaults to 2000000000)
		, className: 'spinner' // The CSS class to assign to the spinner
		, top: '50%' // Top position relative to parent
		, left: '50%' // Left position relative to parent
		, shadow: false // Whether to render a shadow
		, hwaccel: false // Whether to use hardware acceleration
		, position: 'absolute' // Element positioning
		}
		var target = document.getElementById('nxl-loading')
		var spinner = new Spinner(opts).spin(target);
	};
	onClickPlayGame = function(event) {
		var l = Ladda.create(this);
		l.start();
		nxsteam.launcher.install_nxl();
		//l.stop();
	};
	onClickLogin = function(event) {
		//alert(event.pageX);
		// call api
		var l = Ladda.create(this);
		l.start();
		function callback(data) {
			alert("callback - login: " + data);
			l.stop();
			// {"token":"NX1_1000000974_cVBXYkE4T2kzV2pJak1IRW1GWUY4YlVuOFhNPQ2","result":"ok","user_no":"1000000974"}
			if (data.result == "ok") {
				setStep("account_confirmation");
				// set id
				$('#txt_registered_id').text(data.user_no);
			}
		};
		nxsteam.api.login($('#txt_id').val(), $('#txt_pw').val(), callback);
	};	
	onClickYesPlayGame = function(event) {
		var l = Ladda.create(this);
		l.start();
		nxsteam.launcher.install_nxl();
	};	
	initKonami = function () {
		$( window ).konami({
			cheat: function() {
				gui = require('nw.gui');
				gui.Window.get().showDevTools();
			} // end cheat
		});
	};
	initModule = function ( $container ) {
		//return;
		//alert("called - initModule");
		nxsteam.launcher.initModule($container);

		$.uriAnchor.configModule ({
			schema_map : configMap.anchor_schema_map
		});
		//alert("nxsteam.shell.initModule");
		$(window)
			.bind('hashchange', onHashChange)
			.trigger('hashchange');

		// test
		$('#btnPlayGame').bind("click", onClickPlayGame);
		$('#btnLogin').bind("click", onClickLogin);
		$('#btnYesPlayGame').bind("click", onClickYesPlayGame);
		$('#btnNoExit').bind("click", onClickYesPlayGame);

		// test
		post = { 
			id : "your-id",
			pw : "your-pwd"
		};		
		nxsteam.api.login(post.id, post.pw);
		initKonami();
	};
	return { initModule : initModule };
}());

// alert("nxsteam.shell");
