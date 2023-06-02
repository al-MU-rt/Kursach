
#include "WebServer.h"
#include "COMport.h"
#include<iostream>
#include"sqlite/sqlite3.h"
#include"Crc.h"
#include"data_geter.h"
#include<thread>


void main(){
	
	WebServer webServer("0.0.0.0", 8080);
	if (webServer.init() != 0)
		return;

	ShellExecute(NULL, "open", "http://127.0.0.1:8080",
		NULL, NULL, SW_SHOWNORMAL);

	webServer.run();
	system("pause");

}

