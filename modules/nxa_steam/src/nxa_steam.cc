//
// https://github.com/joyent/node/tree/master/test/addons/hello-world
// https://github.com/nwjs/nw.js/wiki/Build-native-modules-with-nw-gyp
// https://nodejs.org/api/addons.html
//
// prerequisite:
// npm install -g nw-gyp
// nw-gyp configure --target=0.12.2
// nw-gyp build

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <node.h>
#include <v8.h>
#include ".\external\steam\steam_api.h"

using namespace v8;
using namespace std;

void GetAppsSettings(const FunctionCallbackInfo<Value>& args) 
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
  
	std::string line;
	std::string rs;

	// C:\\Users\\hslee\\AppData\\Roaming
	std::string app_data = getenv("APPDATA");
	std::string app_file_name = app_data + "\\NexonLauncher\\apps-settings.db";

	ifstream myfile(app_file_name);
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
			rs += line;
		}
		myfile.close();
	}

	// test
	//args.GetReturnValue().Set(String::NewFromUtf8(isolate, app_data.c_str()));
	
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, rs.c_str()));
}

// for test
void Add(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  double value = args[0]->NumberValue() + args[1]->NumberValue();
  Local<Number> num = Number::New(isolate, value);

  args.GetReturnValue().Set(num);
}

std::string getSteamAuthTicket() 
{
	//use the steam api to get an authenticated session ticket

	std::string ticket;			
	unsigned char buffer[4096];		//buffer to store ticket bytes
	unsigned int bufferSize;		//size of ticket buffer

	// get auth ticket using steam API
	HAuthTicket result = SteamUser()->GetAuthSessionTicket(buffer, sizeof(buffer), &bufferSize );

	if (!result) return "";	//could not authorize ticket, return empty string

	//format to hex string
	for( int i = 0 ; i < bufferSize; i++) {
		char tmp[3];
		sprintf(tmp,"%02x", buffer[i]);
		ticket += tmp;
	}

	return ticket;
}

void GetAuthSessionTicket(const FunctionCallbackInfo<Value>& args) 
{
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);
	bool bError = false;
	std::string ticket = "";

	try
	{
		if (SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid))
		{
			// if Steam is not running or the game wasn't started through Steam, SteamAPI_RestartAppIfNecessary starts the 
			// local Steam client and also launches this game again.
		
			// Once you get a public Steam AppID assigned for this game, you need to replace k_uAppIdInvalid with it and
			// removed steam_appid.txt from the game depot.
			bError = true;
		}

		if (!SteamAPI_Init())
		{
			//OutputDebugString( "SteamAPI_Init() failed\n" );
			//Alert( "Fatal Error", "Steam must be running to play this game (SteamAPI_Init() failed).\n" );
			//return EXIT_FAILURE;
			bError = true;
		}

		if (!bError)
		{
			ticket = getSteamAuthTicket();
		}
		else
		{
			ticket = "steam init failed";
		}

		SteamAPI_Shutdown();
	}
	catch(...)
	{
		ticket = "exception";
	}

	args.GetReturnValue().Set(String::NewFromUtf8(isolate, ticket.c_str()));
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "getAppsSettings", GetAppsSettings);
  NODE_SET_METHOD(target, "getAuthSessionTicket", GetAuthSessionTicket);
  NODE_SET_METHOD(target, "add", Add);
}

NODE_MODULE(nxa_steam, init);