#include <iostream>
#include "XuLy.h"
using namespace std;

int main(int argc, char** argv)
{
    DSLOP dsl;
    DSMH dsm;
    DSCH dsch;
    DSDT dsdt;
    DanhSachID dsID;
	 if (!NapDanhSachID(dsID, "ID.txt"))
    {
        TaoDayID(dsID, MAX_ID_POOL);
        LuuDanhSachID(dsID, "ID.txt");
    }

    MainProcess(dsl, dsm.root, dsch, dsdt, dsID);

    return 0;
}