#include "Select_device.h"
#include <iostream>

BOOL get_NUM(TranslTab&  get_all_dev, CString Ncom, int baud) {

	

	DataVal myvalue;
	CString tmp;
	CCOMport myport(Ncom, baud);
	get_all_dev.count = 0;
	for (int i = 0; i < 10; i++) {

		if (get_all_dev.count == 1) {

				return 1;

		}

		if (myport.ReadReg((BYTE)i, (WORD)0, myvalue.WordValue)==1){

			tmp = "";
			get_all_dev.TrlTab[get_all_dev.count].adres = i;
			tmp.Format("%d.%.2d", myvalue.ByteValue.lb, myvalue.ByteValue.hb);
			get_all_dev.TrlTab[get_all_dev.count].Version = tmp;
			get_all_dev.TrlTab[get_all_dev.count].number = myvalue.ByteValue.lb;
			get_all_dev.count++;
			
		}

	};

	 return TRUE;
}

