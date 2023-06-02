#include"hard.h"
#include <winbase.h>
#include <atlstr.h>
#include <windows.h> // Standard Windows include for system defines
#include <winbase.h>
#include<iostream>
#include <thread>

#pragma once
BOOL Get_Reg(byte Device, byte Function, word StartReg, word NumbReg,
	HANDLE DriverHandle, DWORD WNBytes, DWORD RNBytes, FrameOut* Trans, FrameIn* Receive,
	OVERLAPPED RSync, OVERLAPPED WSync, OVERLAPPED Rd2)
{
	DWORD BytesWritten;
	DWORD dwCommEvent;
	DWORD dwRead;
	byte TimeOut;




	byte tmp;
	Trans->Frame.Device = Device;
	Trans->Frame.Function = Function;
	Trans->Frame.StartReg = StartReg;
	Trans->Frame.NumbReg = NumbReg;

	tmp = Trans->Buf[2];
	Trans->Buf[2] = Trans->Buf[3];
	Trans->Buf[3] = tmp;

	tmp = Trans->Buf[4];
	Trans->Buf[4] = Trans->Buf[5];
	Trans->Buf[5] = tmp;

	Trans->Frame.Crc = CRCCalculation(Trans->Buf, 6);


	Receive->Frame.Crc = 255;
	::ResetEvent(RSync.hEvent);
	::ResetEvent(WSync.hEvent);
	::ResetEvent(Rd2.hEvent);



	if ((DriverHandle == 0) || (DriverHandle == INVALID_HANDLE_VALUE)){

		return FALSE;
	}
	else
	{

		::PurgeComm(DriverHandle, PURGE_TXCLEAR | PURGE_TXABORT | PURGE_RXABORT);
		::PurgeComm(DriverHandle, PURGE_RXCLEAR);
		WriteFile(DriverHandle, Trans->Buf, WNBytes, &BytesWritten, &WSync);

		COMMTIMEOUTS noblock;
		GetCommTimeouts(DriverHandle, &noblock);
		noblock.ReadIntervalTimeout = 20;
		noblock.ReadTotalTimeoutConstant = 20;
		noblock.ReadTotalTimeoutMultiplier = 20;
		noblock.WriteTotalTimeoutConstant = 20;
		noblock.WriteTotalTimeoutMultiplier = 20;


		SetCommTimeouts(DriverHandle, &noblock);

		ReadFile(DriverHandle, Receive->Buf, RNBytes, &dwRead, NULL);


		
		if (RNBytes == 7) {

			unsigned int Crc = ::CRCCalculation(Receive->Buf, 7);
			if (Crc != 0) {
				return 0;
			}

			Receive->Frame.Device = Receive->Buf[0];
			Receive->Frame.Function = Receive->Buf[1];
			Receive->Frame.NumByte = Receive->Buf[2];

			DataVal DataDW;
			DataDW.ByteValue.hb = Receive->Buf[3];
			DataDW.ByteValue.lb = Receive->Buf[4];

			DataVal Data;

			Data.ByteValue.hb = Receive->Buf[5];
			Data.ByteValue.lb = Receive->Buf[6];


			Receive->Frame.Value = DataDW.WordValue;
			Receive->Frame.Crc = Data.WordValue;
		}

		WaitForSingleObject(RSync.hEvent, timeoutrw);
		::PurgeComm(DriverHandle, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT);
		Sleep(timeout);
	}

	return TRUE;

}




BOOL Get_Reg(byte Device, byte Function, word StartReg, DWORD dwVal,
	HANDLE DriverHandle, DWORD WNBytes, DWORD RNBytes, FrameOut * Trans, FrameIn * Receive,
	OVERLAPPED RSync, OVERLAPPED WSync, OVERLAPPED Rd2)
{
	DWORD BytesWritten;
	DWORD dwCommEvent;
	DWORD dwRead;
	byte TimeOut;


	byte tmp;
	Trans->Frame.Device = Device;
	Trans->Frame.Function = Function;
	Trans->Frame.StartReg = StartReg;

	tmp = Trans->Buf[2];
	Trans->Buf[2] = Trans->Buf[3];
	Trans->Buf[3] = tmp;

	tmp = Trans->Buf[4];
	Trans->Buf[4] = Trans->Buf[5];
	Trans->Buf[5] = tmp;

	Trans->Frame.Crc = CRCCalculation(Trans->Buf, 6);
	if (Function == 16){

		DataVal_DW DataDW;

		DataDW.DWValue = dwVal;
		Trans->Buf[4] = 0;
		Trans->Buf[5] = 2;
		Trans->Buf[6] = 4;

		Trans->Buf[7] = DataDW.ByteValue.bb;
		Trans->Buf[8] = DataDW.ByteValue.ab;
		Trans->Buf[9] = DataDW.ByteValue.db;
		Trans->Buf[10] = DataDW.ByteValue.cb;
		WORD Crc = CRCCalculation(Trans->Buf, 11);
		Trans->Buf[12] = (Crc >> 8) & 0xff;
		Trans->Buf[11] = Crc & 0xff;

	}

	Receive->Frame.Crc = 255;
	::ResetEvent(RSync.hEvent);
	::ResetEvent(WSync.hEvent);
	::ResetEvent(Rd2.hEvent);

	

	if ((DriverHandle == 0) || (DriverHandle == INVALID_HANDLE_VALUE)){

		return FALSE;

	}

	else{

		::PurgeComm(DriverHandle, PURGE_TXCLEAR | PURGE_TXABORT | PURGE_RXABORT);
		::PurgeComm(DriverHandle, PURGE_RXCLEAR);
		WriteFile(DriverHandle, Trans->Buf, WNBytes, &BytesWritten, &WSync);
		ReadFile(DriverHandle, Receive->Buf, RNBytes, &dwRead, &RSync);
		WaitForSingleObject(RSync.hEvent, timeoutrw); //timeoutrw
		::PurgeComm(DriverHandle, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT);
		Sleep(1);	//timeout

	}

	return TRUE;

}


HANDLE Open_ComPort(CString Com_Name, DWORD BaudRate){

	timeoutrw = 30;
	timeout = 30;

	DCB Our_DCB;
	DWORD DCB_Baud_Rate;
	HANDLE DriverHandle;

	// Convert the Baud Rate to the Com library define for the DCB
	switch (BaudRate)
	{

	case 2400:
		DCB_Baud_Rate = CBR_2400;
		break;
	case 4800:
		DCB_Baud_Rate = CBR_4800;
		break;
	case 9600:
		DCB_Baud_Rate = CBR_9600;
		break;
	case 14400:
		DCB_Baud_Rate = CBR_14400;
		break;
	case 19200:
		DCB_Baud_Rate = CBR_19200;
		break;
	case 38400:
		DCB_Baud_Rate = CBR_38400;
		break;
	case 57600:
		DCB_Baud_Rate = CBR_57600;
		break;
	case 115200:
		DCB_Baud_Rate = CBR_115200;
		break;
	case 230400:
		DCB_Baud_Rate = 230400;
		break;
	case 460800:
		DCB_Baud_Rate = 460800;
		break;
	case 921600:
		DCB_Baud_Rate = 921600;
		break;
	default:
		return INVALID_HANDLE_VALUE;
	}

	DriverHandle = CreateFile(Com_Name,
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);

	if (DriverHandle == INVALID_HANDLE_VALUE)

		return(DriverHandle);

	else{

		SetupComm(DriverHandle, 1024, 1024);
		GetCommState(DriverHandle, &Our_DCB);

		Our_DCB.BaudRate = DCB_Baud_Rate;
		Our_DCB.fParity = 0;
		Our_DCB.fOutxCtsFlow = 0;
		Our_DCB.fOutxDsrFlow = 0;
		Our_DCB.fDtrControl = DTR_CONTROL_ENABLE;
		Our_DCB.fDsrSensitivity = FALSE;
		Our_DCB.fTXContinueOnXoff = 0;
		Our_DCB.fOutX = 0;
		Our_DCB.fInX = 0;
		Our_DCB.fErrorChar = 0;
		Our_DCB.fNull = 0;
		Our_DCB.fRtsControl = RTS_CONTROL_ENABLE;
		Our_DCB.fAbortOnError = 0;
		Our_DCB.ByteSize = 8;
		Our_DCB.Parity = NOPARITY;
		Our_DCB.StopBits = ONESTOPBIT;

		SetCommState(DriverHandle, &Our_DCB);

	}

	return DriverHandle;

}


int Close_ComPort(HANDLE DriverHandle)
{
	// Sanity check on the Handle
	if ((DriverHandle == 0) || (DriverHandle == INVALID_HANDLE_VALUE))
		return FALSE;

	// Close the communications port
	CloseHandle(DriverHandle);

	return TRUE;
}