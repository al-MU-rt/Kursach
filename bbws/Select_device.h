#pragma once
#include <atlstr.h>
#include "COMport.h"
#include "WebServer.h"
#include <atlstr.h>

struct VersTrans
{
	CString Version;
	CString Transl;
	CString SoftVersion;
	CString sModel;
	int number;
	int adres;

};

struct TranslTab
{
	VersTrans TrlTab[100];
	int count;

};



BOOL get_NUM(TranslTab& get_all_dev,CString Ncom, int baud);