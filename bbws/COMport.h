#pragma once
#include"hard.h"

class CCOMport
{
public:
	CCOMport(CString NCom, int baud);
	~CCOMport();
	BOOL WriteReg(BYTE device, WORD nreg, unsigned short value);
	BOOL WriteReg(BYTE device, WORD nreg, DWORD value);
	BOOL  ReadReg(BYTE device, WORD nreg, unsigned short& value);
	BOOL  ReadReg(BYTE device, WORD nreg, float& value);
	void OnInit(void);
	HANDLE ComHandle;
	OVERLAPPED mRSync;
	OVERLAPPED mWSync;
	OVERLAPPED mRd2;

	FrameIn In;
	FrameOut Out;

private:



	LARGE_INTEGER Freq, Counter;
	unsigned int Crc;
	__int64 Freq1, Counter1;

	void SetTimeValues(void);
	void MySleep(double mls);




};