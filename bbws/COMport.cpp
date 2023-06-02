#include "COMport.h"
#include <iostream>

CCOMport::CCOMport(CString Ncom, int baud)
{
	ComHandle = ::Open_ComPort(Ncom, baud);
	if (ComHandle != INVALID_HANDLE_VALUE)
	{
		//Ncom.Format(Ncom +" открыт  на скорости %d",baud);
		//::AfxMessageBox ("Порт "+Ncom);
	}
	else {

	}


};
CCOMport::~CCOMport()
{
	Close_ComPort(ComHandle);
	//::AfxMessageBox ("Порт закрыт");


};

void CCOMport::SetTimeValues()
{
	::QueryPerformanceFrequency(&Freq);
	::QueryPerformanceCounter(&Counter);
	Freq1 = Freq.QuadPart;
	Counter1 = Counter.QuadPart;

}

void CCOMport::MySleep(double mls)
{
	LARGE_INTEGER tick;
	LARGE_INTEGER tack;
	__int64 tik, tak;
	::QueryPerformanceCounter(&tick);
	tik = tick.QuadPart;
	tak = 0;
	while (tak < Freq1 * mls / 1000 + tik)
	{
		::QueryPerformanceCounter(&tack);
		tak = tack.QuadPart;
	}
}

void CCOMport::OnInit(void)
{
	CCOMport::SetTimeValues();
	mRSync.hEvent = 0; mRSync.Internal = 0; mRSync.InternalHigh = 0; mRSync.Offset = 0; mRSync.OffsetHigh = 0;
	mWSync.hEvent = 0; mWSync.Internal = 0; mWSync.InternalHigh = 0; mWSync.Offset = 0; mWSync.OffsetHigh = 0;
	//mWSync=0;
	mRd2.hEvent = 0; mRd2.Internal = 0; mRd2.InternalHigh = 0; mRd2.Offset = 0; mRd2.OffsetHigh = 0;
	//mRd2=0;


	mRSync.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	mWSync.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	mRd2.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

}

BOOL CCOMport::WriteReg(BYTE device, WORD nreg, unsigned short value)
{
	//if(nreg==48) value=445;	
	::Get_Reg(device, 6, nreg, value, ComHandle, 8, 8, &Out, &In, mRSync, mWSync, mRd2);
	Crc = ::CRCCalculation(In.Buf, 8);

	if (Crc == 0)
	{
		return TRUE;
	}
	else
		return FALSE;
}
BOOL CCOMport::WriteReg(BYTE device, WORD nreg, DWORD value)
{
	//if(nreg==48) value=445;	
	::Get_Reg(device, 16, nreg, value, ComHandle, 13, 8, &Out, &In, mRSync, mWSync, mRd2);
	Crc = ::CRCCalculation(In.Buf, 8);

	if (Crc == 0)
	{
		return TRUE;
	}
	else
		return FALSE;
}


BOOL CCOMport::ReadReg(BYTE device, WORD nreg, unsigned short& value)
{
	BOOL a = Get_Reg(device, 3, nreg, (WORD)1, ComHandle, 8, 7, &Out, &In, mRSync, mWSync, mRd2);
	Crc = CRCCalculation(In.Buf, 7);


	if (a == 0) {
		return 0;
	}




	if (nreg == (WORD)0) {
		DataVal DataDW;
		DataDW.ByteValue.hb = In.Buf[3];
		DataDW.ByteValue.lb = In.Buf[4];

		value = DataDW.WordValue;
		return 1;

	}
	else {

		value = In.Frame.Value;
		return 1;
	}

}
BOOL CCOMport::ReadReg(BYTE device, WORD nreg, float& fValue)
{
	::Get_Reg(device, 3, nreg, (WORD)2, ComHandle, 8, 9, &Out, &In, mRSync, mWSync, mRd2);
	Crc = ::CRCCalculation(In.Buf, 9);

	if (Crc == 0)
	{
		//value=In.Frame.Value;
		DataVal Data;
		DataVal_DW DataDW;
		DataVal_F dF;
		DataDW.ByteValue.bb = In.Buf[3];
		DataDW.ByteValue.ab = In.Buf[4];
		DataDW.ByteValue.db = In.Buf[5];
		DataDW.ByteValue.cb = In.Buf[6];
		dF.DWValue = DataDW.DWValue;

		fValue = dF.FloatValue;


		return TRUE;
	}
	else
		return FALSE;

}
