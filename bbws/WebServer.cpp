#include <string>
#include <istream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <iterator>
#include "WebServer.h"
#include <Windows.h>
#include <atlstr.h>
#include "COMport.h" 
#include "Select_COM_port.h"
#include "Select_device.h"
#include "data_geter.h"
#include <locale> 
#include <codecvt> 
#include <stdint.h>
#include <cstdlib>
#include <ctime>



void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
	
	std::istringstream iss(msg);
	std::vector<std::string> parsed((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
	std::string content = "<h1>404 Not Found</h1>";
	std::string htmlFile = "/index.html";
	int errorCode = 404;

	if (parsed.size() >= 3 && parsed[0] == "GET" )
	{
		htmlFile = parsed[1];
		
		if (htmlFile.find("res")==1) {

			std::string rr;
			CString res;
			CString dot = ".";
			
			for (int i = 0; i < htmlFile.length()-5; i++) {
				
				res.AppendChar(htmlFile[5+i]);

			}
	
			rr = res;

			std::ostringstream oss;
			content = get_value_photo(rr,device.id);


			oss << "HTTP/1.1 " << 200 << " OK\r\n";
			oss << "Content-Type: image/jpeg\r\n";
			oss << "Content-Length: " << content.size() << "\r\n";
			oss << "\r\n";
			oss << content;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);
		
		}

		if (htmlFile == "/open_config") {

			htmlFile = "menu.html";
			CString a = "/";
			CString aa = htmlFile.c_str();

			if (aa.Find(a) != -1) {

				aa.Remove('/');

			}

			htmlFile = aa;

			std::string str = get_value_html(htmlFile, device.id);
			content = str;
			errorCode = 200;
			std::ostringstream oss;

			oss << "HTTP/1.1 " << errorCode << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << content.size() << "\r\n";
			oss << "\r\n";
			oss << content;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);
		}

		if (htmlFile == "/set_COM_port") {

			htmlFile = "/devices.html";
			std::ifstream f(".\\wwwroot" + htmlFile);

			std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
			content = str;
			errorCode = 200;

			f.close();
			std::ostringstream oss;

			oss << "HTTP/1.1 " << errorCode << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << content.size() << "\r\n";
			oss << "\r\n";
			oss << content;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);

		}

		if (htmlFile == "/" || htmlFile == "/?") {

			htmlFile = "/la.html";
			std::ifstream f(".\\wwwroot" + htmlFile);

			if (f.good()){

				std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
				content = str;
				errorCode = 200;

			}

			f.close();

			std::ostringstream oss;
			oss << "HTTP/1.1 " << errorCode << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << content.size() << "\r\n";
			oss << "\r\n";
			oss << content;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);


		}
		if (htmlFile == "/calibrovka" ) {

			htmlFile = "/main.html";
			std::ifstream f(".\\wwwroot" + htmlFile);

			if (f.good()){

				std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
				content = str;
				errorCode = 200;
			
			}

			f.close();

			std::ostringstream oss;
			oss << "HTTP/1.1 " << errorCode << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << content.size() << "\r\n";
			oss << "\r\n";
			oss << content;

			std::string output = oss.str();
			int size = output.size() + 1;
			sendToClient(clientSocket, output.c_str(), size);

		}

		if (htmlFile == "/COM-port_setting") {

			htmlFile = "/sett_of_com_port.html";
			std::ifstream f(".\\wwwroot" + htmlFile);

			if (f.good())
			{
				std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
				content = str;
				errorCode = 200;
			}

			f.close();

			std::ostringstream oss;
			oss << "HTTP/1.1 " << errorCode << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << content.size() << "\r\n";
			oss << "\r\n";
			oss << content;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);


		}

		if (htmlFile == "/change_device") {

			htmlFile = "/device_settings.html";
			std::ifstream f(".\\wwwroot" + htmlFile);

			if (f.good()){

				std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
				content = str;
				errorCode = 200;
			
			}

			f.close();

			std::ostringstream oss;
			oss << "HTTP/1.1 " << errorCode << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << content.size() << "\r\n";
			oss << "\r\n";
			oss << content;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);


		}

		CString a ="/";
		CString aa = htmlFile.c_str();

		if ( aa.Find(a) != -1 ){

			aa.Remove('/');

		}

		htmlFile = aa;
		std::string str= get_value_html(htmlFile, device.id);
		errorCode = 200;
		

		


		content = str;
		std::ostringstream oss;
		oss << "HTTP/1.1 " << errorCode << " OK\r\n";
		oss << "Cache-Control: no-cache, private\r\n";
		oss << "Content-Type: text/html\r\n";
		oss << "Content-Length: " << content.size() << "\r\n";
		oss << "\r\n";
		oss << content;
		std::string output = oss.str();
		sendToClient(clientSocket, output.c_str(), output.size() + 1 );
		


	}

	if (parsed[0] == "PUT") {

		std::ostringstream oss;
		oss << "HTTP/1.1 " << 200 << " OK\r\n";
		oss << "Cache-Control: no-cache, private\r\n";
		oss << "Content-Type: text/html\r\n";
		oss << "Content-Length: " << content.size() << "\r\n";
		oss << "\r\n";
		oss << content;
		std::string output = oss.str();
		int size = output.size() + 1;

		sendToClient(clientSocket, output.c_str(), size);

	}


	if (parsed[0] == "POST") {

		if (parsed[1] == "/get_seve_reg") {

			std::string b = parsed[parsed.size() - 1];

			unsigned short  add;
			int val;
			int type;

			CString c = b.c_str();
			std::string aaa = c;

			get_save_by_id(device.id, val);

			CString sasa = std::to_string(val).c_str();

			std::ostringstream oss;
			oss << "HTTP/1.1 " << 200 << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << sasa.GetLength() << "\r\n";
			oss << "\r\n";
			oss << sasa;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);
		}


		if (parsed[1] == "/get_defoult_set") {

			std::string b = parsed[parsed.size() - 1];
			unsigned short  add;
			int val;
			int type;

			CString c = b.c_str();

			std::string aaa = c;
			CString sasa = get_value_set(aaa).c_str();

			std::ostringstream oss;
			oss << "HTTP/1.1 " << 200 << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << sasa.GetLength() << "\r\n";
			oss << "\r\n";
			oss << sasa;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);

		}

		if (parsed[1] == "/get_all_castom_set") {

			CString sasa = get_all_sets(device.id).c_str();

			std::ostringstream oss;
			oss << "HTTP/1.1 " << 200 << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << sasa.GetLength() << "\r\n";
			oss << "\r\n";
			oss << sasa;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);
		
		}

		
		if (parsed[1] == "/get_devices") {

			TranslTab B;
			
			get_NUM(B,COM_port_name, Boud_rate);
			
			CString sasa;

			//int id=0;
			int id = 22;

			for (int i = 0; i < B.count; i++) {
				get_device_by_num(B.TrlTab[i].number, sasa);
				get_id_by_num(B.TrlTab[i].number, id);
			}

			device.adres = B.TrlTab->adres;
			device.name = sasa;
			device.id = id;

			std::ostringstream oss;
			oss << "HTTP/1.1 " << 200 << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " << sasa.GetLength() << "\r\n";
			oss << "\r\n";
			oss << sasa;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);

		}

		if (parsed[1] == "/get_COM") {

			CString a;

			SelectComPort(a);
			std::ostringstream oss;
			oss << "HTTP/1.1 " << 200 << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " <<a.GetLength() << "\r\n";
			oss << "\r\n";
			oss << a;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);

		}

		if (parsed[1] == "/set_COM_port") {
			
			std::string b = parsed[parsed.size() - 1];

			CString  add;
			int val;
			int type;

			CString c = b.c_str();

			c = c.Mid(c.Find("\"") + 1, c.GetLength() - 2);
			add =c.Mid(0, c.Find(","));
			COM_port_name =  add;

			c = c.Mid(c.Find(",") + 1, c.GetLength());
			add.Append(",");
			add.Append(c);
			Boud_rate=atoi(c);

			
			std::ostringstream oss;
			oss << "HTTP/1.1 " << 200 << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text/html\r\n";
			oss << "Content-Length: " <<add.GetLength()<< "\r\n";
			oss << "\r\n";
			oss << add;

			std::string output = oss.str();
			int size = output.size() + 1;

			CCOMport serial(COM_port_name, Boud_rate);
			unsigned short a=0;

			sendToClient(clientSocket, output.c_str(), size);
			
		}


		if (parsed[1] == "/get") {
			
			std::string b = parsed[parsed.size() - 1];

			unsigned short  add;
			int val;
			CString type;

			CString c = b.c_str();

			c = c.Mid(c.Find("\"") + 1, c.GetLength() - 2);
			add = atoi(c.Mid(0, c.Find(",")));
			c = c.Mid(c.Find(",") + 1, c.GetLength());
			type = c;

			CCOMport serial(COM_port_name, Boud_rate);

			

			if (type == "float") {

				float a = 0;

				serial.ReadReg((BYTE)1, (WORD)add, a);

				auto s = std::to_string(a);
				std::ostringstream oss;
				oss << "HTTP/1.1 " << 200 << " OK\r\n";
				oss << "Cache-Control: no-cache, private\r\n";
				oss << "Content-Type: text/html\r\n";
				oss << "Content-Length: " << s.size() << "\r\n";
				oss << "\r\n";
				oss << s;;

				std::string output = oss.str();
				int size = output.size() + 1;

				sendToClient(clientSocket, output.c_str(), size);

			}
			else {

				unsigned short a=0;

				serial.ReadReg((BYTE)device.adres, (WORD)add, a);
				auto s = std::to_string(a);

				std::ostringstream oss;
				oss << "HTTP/1.1 " << 200 << " OK\r\n";
				oss << "Cache-Control: no-cache, private\r\n";
				oss << "Content-Type: text/html\r\n";
				oss << "Content-Length: " << s.size() << "\r\n";
				oss << "\r\n";
				oss << s;;

				std::string output = oss.str();
				int size = output.size() + 1;

				sendToClient(clientSocket, output.c_str(), size);

			}
		}


	
		    
		if (parsed[1] == "/set") {

			std::string b = parsed[parsed.size() - 1];

			int add;
			
			CString type;

			CString c = b.c_str();			

			c = c.Mid(c.Find("\"") + 1,c.GetLength()-2);
			add=atoi(c.Mid(0, c.Find(",")));

			c = c.Mid(c.Find(",")+1,c.GetLength());
			type=c.Mid(0, c.Find(","));

			c = c.Mid(c.Find(",") + 1, c.GetLength());

			if (type == "int") {

				unsigned short val;

				val=atoi(c);
				CCOMport serial(COM_port_name, Boud_rate);

				serial.WriteReg((BYTE)device.adres, (WORD)add, (unsigned short)val);

			}
			else {

				float val;

				val = atoi(c);
				CCOMport serial(COM_port_name, Boud_rate);

				serial.WriteReg((BYTE)device.adres, (WORD)add, (DWORD)val);

			}

			CString sasa = "OK";
			std::ostringstream oss;
			oss << "HTTP/1.1 " << 200 << " OK\r\n";
			oss << "Cache-Control: no-cache, private\r\n";
			oss << "Content-Type: text\n";
			oss << "Content-Length: " << sasa.GetLength() << "\r\n";
			oss << "\r\n";
			oss << sasa;

			std::string output = oss.str();
			int size = output.size() + 1;

			sendToClient(clientSocket, output.c_str(), size);

		};






		std::ostringstream oss;
		oss << "HTTP/1.1 " << 200 << " OK\r\n";
		oss << "Cache-Control: no-cache, private\r\n";
		oss << "Content-Type: text/html\r\n";
		oss << "Content-Length: " << content.size() << "\r\n";
		oss << "\r\n";
		oss << content;

		std::string output = oss.str();
		int size = output.size() + 1;

		sendToClient(clientSocket, output.c_str(), size);

	};
	
}

// Handler for client connections
void WebServer::onClientConnected(int clientSocket)
{

}

// Handler for client disconnections
void WebServer::onClientDisconnected(int clientSocket)
{
	
	
}