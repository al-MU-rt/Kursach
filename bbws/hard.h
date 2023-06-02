#include <windows.h> // Standard Windows include for system defines
#include <winbase.h> // Win32 Comm Library and structures DEFS
#include <stdlib.h>
#include"Crc.h"
#include<string>
#include <atlstr.h>
#pragma once

typedef unsigned char byte;
typedef unsigned short int word;


static int timeoutrw;
static int timeout;


class FrameToSend
{
public:
	byte Device;
	byte Function;
	word StartReg;
	signed short int NumbReg;
	word Crc;
};



union FrameOut
{
	FrameToSend Frame;
	byte Buf[13];
};


struct FrameToReceive
{

	byte Device;
	byte Function;
	byte NumByte;
	WORD Value;
	WORD Crc;
};


union FrameIn
{
	FrameToReceive Frame;
	byte Buf[13];
};


struct DataValue
{
	byte lb;
	byte hb;
};

union DataVal
{
	DataValue ByteValue;
	WORD	  WordValue;

};

struct DataValue_F
{
	byte ab;
	byte bb;
	byte cb;
	byte db;
};
union DataVal_F
{
	DataValue_F ByteValue;
	float	    FloatValue;
	DWORD       DWValue;
};
union DataVal_DW
{
	DataValue_F ByteValue;
	//	float	    FloatValue;	
	DWORD       DWValue;
};

HANDLE Open_ComPort(CString Com_Name, DWORD BoudRate);
int Close_ComPort(HANDLE DriverHandle);  // Close COM port 
// implemenation of defined function




BOOL Get_Reg(byte Device, byte Function, word StartReg, word NumbReg,
	HANDLE DriverHandle, DWORD WNBytes, DWORD RNBytes, FrameOut* Trans, FrameIn* Receive,
	OVERLAPPED RSync, OVERLAPPED WSync, OVERLAPPED Rd2);
BOOL Get_Reg(byte Device, byte Function, word StartReg, DWORD dwVal,
	HANDLE DriverHandle, DWORD WNBytes, DWORD RNBytes, FrameOut* Trans, FrameIn* Receive,
	OVERLAPPED RSync, OVERLAPPED WSync, OVERLAPPED Rd2);

