#pragma one
#include<string>
#include<iostream>
#define MAXMONHOC 100
#define MAXLOP 10000
#define MAXDSCTDT 1000

using namespace std;

struct MonHoc {//cây nhị phân
    string MAMH;        // C15
    string TENMH;
    struct DanhSachCauHoi *ds_cauhoi; // con trỏ đến danh sách câu hỏi
    MonHoc *pLeft;
    MonHoc *pRight;
};
typedef MonHoc* TreeMH;

typedef struct DanhSachMonHoc DSMH;

struct CauTrucDeThi
{
	string MASV;
	string MAMH;
	float DIEM;
	int sct;
	int tg;
	int *bode;
	int *dapan;
};
typedef struct CauTrucDeThi CTDT;

struct DanhSachDeThi{
	CTDT DS_CTDT[MAXDSCTDT];
	int SLDSDT = 0;
};
typedef struct DanhSachDeThi DSDT;

struct DiemThi{
	string MAMH;
	float DIEM;
	DiemThi *pNext;
};
typedef struct DiemThi NODEDIEMTHI;

struct DanhSachDiem{
	int SLDiem = 0;
	NODEDIEMTHI *pHead = NULL;
	NODEDIEMTHI *pLast = NULL;
};
typedef struct DanhSachDiem DSDIEM;

struct SinhVien{
	string MASV;
	string TEN;
	string HO;
	string PHAI;
	string PASSWORD;
	DSDIEM ds_Diem;
	SinhVien *pNext;
};
typedef struct SinhVien NODESV;

struct DanhSachSinhVien{
	int SLSV = 0;
	NODESV *pHead = NULL;
	NODESV *pLast = NULL;
};
typedef struct DanhSachSinhVien DSSV;

struct Lop{
	string MALOP;
	string TENLOP;
	DSSV ds_SV;
};
typedef struct Lop LOP;

struct DanhSachLop{
	int SLLOP = 0;
	LOP *DS_LOP[MAXLOP];
};
typedef struct DanhSachLop DSLOP;

struct CauHoi {//dslk đơn
    int ID;
    string NOIDUNG;
    string A, B, C, D;
    string DA;
    CauHoi *pNext;
};
typedef struct CauHoi *CauHoiNode;

struct DanhSachCauHoi {
    int SLCH = 0;
    CauHoiNode pHead = NULL;
};
typedef struct DanhSachCauHoi DSCH;


struct ThoiGian{
	int Gio;
	int Phut;
	int Giay;
};
typedef struct ThoiGian TG;
