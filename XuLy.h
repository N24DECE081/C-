#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <thread>
#include <sstream>
#include <random>  
#include <iomanip> // setprecision  mới thêm
// ⚠️ Fix xung đột giữa std::byte và byte trong Windows SDK
#define byte win_byte
#include "Struct.h"
#include "DoHoa.h"
#undef byte

using namespace std;

bool stop = 1;

//=============================== Ham Xu Ly Chinh =================================//
int DangNhap(DSLOP &dsl, string &masv);
int MainMenuGV();
void MainProcess(DSLOP &dsl, NodeMon* &root, DSCH &dsch, DSDT &dsdt, DanhSachID &dsID);


//=============================== Ham Lop ===================================//
void FunctionLop(DSLOP &dsl);

void ThemLop(DSLOP &dsl, int page);
void NhapLop(DSLOP &dsl, int page);

void XoaLop (DSLOP &dsl, int &page);
void NhapLopXoa(DSLOP &dsl,int &page);

void SuaLop(DSLOP &dsl, int state, int page);
void ChinhLop(DSLOP &dsl, int &page);
void NhapLopChinh(DSLOP &dsl , int &page);

//========================== Ham Sinh Vien ==================================//
void FunctionSV(DSLOP &dsl);

void NhapMaLop(DSLOP &dsl , int page);
void SeLectFunctionSV(Lop *&l ,int page);

void NhapSinhVien(LOP *&l);
void ThemSVVaoDS(DSSV &ds_SV, NODESV *p);

void XoaSinhVien(LOP *&l ,int page);
void DeleteINFO_SV(DSSV &ds_SV, string mssv);

//========================= Ham Mon Hoc =================================//
void FunctionMon(TreeMH &root, DSLOP dsl, DSCH &dsch);
void InDSMon(TreeMH root, int page); // hàm in danh sách môn (phân trang)
void NhapMonHoc(TreeMH &root, int page);
void ThemMonHoc(TreeMH &root, int page);
void NhapMonXoa(TreeMH &root, int &page, DSLOP dsl, DSCH &dsch);     //ĐÃ SỬA
void XoaMonHoc(TreeMH &root, DSLOP dsl, DSCH &dsch);
void SuaMon(TreeMH &root, int state, int page);
void NhapMonChinh(TreeMH &root , int &page, DSCH dsch, DSLOP dsl);
void ChinhMon(TreeMH &root, int &page, DSCH dsch, DSLOP dsl);


//===============================  Cau Hoi ====================================//
void FunctionCH(DSCH &dsch, TreeMH root, DSDT dsdt, DanhSachID &dsID);//đã sửa, xem lại

void Them1CauHoi(DSCH &dsch, DanhSachID &dsID, CauHoi *a); //đã sửa
void NhapCHThem(DSCH &dsch, NodeMon *mh, DanhSachID &dsID);//đã sửa
void ThemCH(DSCH &dsch, TreeMH root, DanhSachID &dsID); //đã sửa

void NhapCauHoiXoa(DSCH &dsch, int &page, int arr[], DSDT dsdt); //đã sửa
void XoaCauHoi(DSCH &dsch, int arr[], DSDT dsdt); //đã sửa
void RemoveCH(DSCH &dsch, int id);//đã sửa

void XemCH(DSCH &dsch, int &page, int arr[]); //đã sửa
void XemCauHoi (DSCH &dsch, int arr[]);//đã sửa

void XemCHTheoMon( NodeMon* root, DSCH dsch);

//============================== DIEM ========================================//
void FunctionDiem(DSLOP dsl,  NodeMon* root, DSCH dsch, DSDT dsdt);

void NhapLopXemDiem(DSLOP dsl,  NodeMon* root, DSCH dsch, DSDT dsdt);
void NhapMonXemDiem(LOP *l,  NodeMon* root, DSCH dsch, DSDT dsdt);
void XemDiem1Lop(LOP *l, MONHOC m, DSCH dsch, DSDT dsdt);
void InChiTiet1LanThi(NODEDIEMTHI *p, DSCH dsch, NODESV *k, DSDT dsdt);

//============================== THI ========================================//
void FunctionThi(DSCH dsch, int tg, int sct,string monthi,float &diem , CTDT &ctdt);
void NhapMonThi( NodeMon* root, int &tg, int &sct, string &monthi, bool &check);
int* LayDeThi(DSCH &dsch, int sct, const string &mamon); //đã sửa, xem lại B2
void ThemDiemThiVaoDS(DSDIEM &dsd, NODEDIEMTHI *p);

//=========================== Doc ghi file ===============================//
void DocFileDSLop(DSLOP &dsl);// đã sửa môn học
void GhiFileDSLop(DSLOP dsl);

void DocFileDSDiem(DSDT &dsdt);
void GhiFileDSDiem(DSDT dsdt);

void DocFileDSMH(NodeMon* &root);
void GhiFileDSMH(NodeMon* &root);

void DocFileCauHoi(DSCH &dsch);
void GhiFileCauHoi(DSCH dsch);
//=================================================================================//
int LayIDKeTiep(DanhSachID &dsID);
CauHoi* KhoiTaoCauHoi() //đã sửa
{
    CauHoi* p = new CauHoi;
    p->ID = LayIDKeTiep(dsID);
    p->daThi = false;
    p->pNext = NULL;
    return p;
}



bool Exit (char &s, bool &check)
{
	AnConTro();
	gotoxy(130,26);
	vekhungTB(10,36);
	string tb = "Ban co chac chan muon thoat ? (Y/N)";
	InTB(tb,132,30);
	batphim(s,check);
	while(s != ESC)
	{
		AnConTro();
		if((s == 'y' || s == 'Y')&& check == true)
		{
			XoaTB(130,26);
			return true;
		}
		else if((s == 'n' || s == 'N') && check == true)
		{
			XoaTB(130,26);
			return false;
		}
		batphim(s,check);
	}
	XoaTB(130,26);
	return true;
}

// Kiểm tra mã hoặc tên môn có trùng hay không
// Trả về true nếu KHÔNG trùng (tức là có thể thêm), false nếu trùng
bool CheckMonNhap(NodeMon* root, const string &mamon, const string &tenmon) {          //ĐÃ SỬA
    if (!root) return true;
    // Duyệt inorder hoặc BST search theo mã; nhưng vì cần kiểm tra cả mã và tên,
    // ta duyệt toàn cây (đệ quy)
    if (root->data.MAMH == mamon) return false;
    if (root->data.TENMH == tenmon) return false;
    if (!CheckMonNhap(root->left, mamon, tenmon)) return false;
    if (!CheckMonNhap(root->right, mamon, tenmon)) return false;
    return true;
}// TỪ TRÊN TỚI ĐÂY
void ChuanHoaTen (string &text)
{
	if(text[0] == 32)
	{
		text.erase(0,1);
		ChuanHoaTen(text);
	}
	if(text[text.length()-1] == 32)
	{
		text.erase(text.length()-1,1);
		ChuanHoaTen(text);
	}
} 

char doichar (int n)
{
	return (char)(n+48);
}

string IntToString(int s)
{
	int x;
	string p;
	while(s>=10)
	{
		x = s%10;
		p.insert(0,1,doichar(x));
		s = s/10;
	}
	p.insert(0,1,doichar(s));
	return p;
}

bool CheckNhapLop(DSLOP dsl, string malop, string tenlop)
{
	for(int i = 0; i < dsl.SLLOP; i++)
	{
		if(malop.compare(dsl.DS_LOP[i]->MALOP) == 0 || tenlop.compare(dsl.DS_LOP[i]->TENLOP)==0)
			return false;
	}
	return true;
}

string TachHoSV(string hoten)
{
	string ho;
	for(int i = hoten.length() - 1; i >= 0; i--)
	{
		if(hoten[i] == 32)
		{
			for(int j = i - 1; j >= 0; j--)	ho+= hoten[j];
			ho = DaoChuoi(ho);
			return ho;
		}
	}
}

string TachTenSV(string hoten)
{
	string ten ;
	for(int i = hoten.length() -1; i >= 0; i--)
	{
		if(hoten[i] == 32)
		{
			ten = DaoChuoi(ten);
			return ten;
		}
		ten+=hoten[i];
	}
}

int TachMSSV (string maSV) 
{
	maSV.erase(0,maSV.length()-3);
	return StringToInt(maSV);
}

bool CheckFormMaSv (string masv)
{
	if (masv.length() != 10 || masv[0] != 'N')	return false;
	if (masv[1] < '0' || masv[1] > '9' || masv[2] < '0' || masv[2] > '9')	return false;
	for(int i = 7; i < 10; i++)
	{
		if(masv[i] < '0' || masv[i] > '9')	return false;
	}
	for(int i = 3; i < 7; i++)
	{
		if(masv[i] < 'A' || masv[i] > 'Z')	return false;
	}	
	return true;
}

bool CheckMaLop (DSLOP dsl, string malop)
{
	for(int i = 0; i < dsl.SLLOP; i++)
	{
		if(malop.compare(dsl.DS_LOP[i]->MALOP) == 0 )
		{
			return false;
		}
	}
	return true;
}

int SoSanhMa(string mA, string mB)
{
	int x = mA.length();
	int y = mB.length();
	int z;
	if(x < y)
	{
		z = x;
	}
	else z = y;
	for(int i = 0; i < z; i++)
	{
		if(mA[i] < mB[i])
		{
			return 1;
		}
		else if(mA[i] >  mB[i])
		{
			return -1;
		}
	}
	return 0;
}

void InsertMon(TreeMH &root, MonHoc mh) {// đã sửa
    root = insertMon(root, mh);
}


void InsertLop(DSLOP &dsl, LOP *l)  //cần sửa
{
	if(dsl.SLLOP == 0)
	{
		dsl.DS_LOP[dsl.SLLOP] = l;
		dsl.SLLOP++;
	}
	else
	{
		int j;
		for(j = dsl.SLLOP-1; j >=0 ; j--)
		{
			if(SoSanhMa(l->MALOP,dsl.DS_LOP[j]->MALOP) == -1)	break;
		}
		if(j == dsl.SLLOP - 1)
		{
			dsl.DS_LOP[dsl.SLLOP] = l;
			dsl.SLLOP++;
		}
		else
		{
			
			for(int i = dsl.SLLOP; i > j + 1; i--)
				dsl.DS_LOP[i] = dsl.DS_LOP[i-1];
			dsl.DS_LOP[j+1] = l;
			dsl.SLLOP++;
		}
	}
}
   
void InsertDSDiemThi(DSDT &dsdt, CTDT ctdt)
{
	if(dsdt.SLDSDT == 0)
	{
		dsdt.DS_CTDT[dsdt.SLDSDT] = ctdt;
		dsdt.SLDSDT++;
	}
	else
	{
		int j;
		for(j = dsdt.SLDSDT-1; j >=0 ; j--)
		{
			if(SoSanhMa(ctdt.MASV,dsdt.DS_CTDT[j].MASV) == -1)	break;
		}
		if(j == dsdt.SLDSDT - 1)
		{
			dsdt.DS_CTDT[dsdt.SLDSDT] = ctdt;
			dsdt.SLDSDT++;
		}
		else
		{
			
			for(int i = dsdt.SLDSDT; i > j + 1; i--)
				dsdt.DS_CTDT[i] = dsdt.DS_CTDT[i-1];
			dsdt.DS_CTDT[j+1] = ctdt;
			dsdt.SLDSDT++;
		}
	}
}

void ThemSVVaoDS(DSSV &ds_SV, NODESV *p)
{
	if(ds_SV.pHead == NULL)
	{
		ds_SV.pHead = ds_SV.pLast = p;
		ds_SV.SLSV++;
	}
	if(TachMSSV(p->MASV) < TachMSSV(ds_SV.pHead->MASV))
	{
		p->pNext = ds_SV.pHead;
		ds_SV.pHead = p;
		ds_SV.SLSV++;
	}
	else
	{
		NODESV *r = ds_SV.pHead;
		while(r->pNext != NULL && TachMSSV(r->pNext->MASV) < TachMSSV(p->MASV))
			r = r->pNext;
		p->pNext = r->pNext;
		r->pNext = p;
		ds_SV.SLSV++;
	}
}

void ThemVaoDauDSSV(DSSV &ds_SV, NODESV *p)
{
	if(ds_SV.pHead == NULL)	
	{
		ds_SV.pHead = ds_SV.pLast = p;
		ds_SV.SLSV++;
	}
	else
	{
		p->pNext = ds_SV.pHead;
		ds_SV.pHead = p;
		ds_SV.SLSV++;
	}
}

void DeleteFrist_SV(DSSV &ds_SV)
{
	if(ds_SV.pHead == NULL)	return;
	NODESV *p = ds_SV.pHead;
	ds_SV.pHead = ds_SV.pHead->pNext;
	delete p;
	ds_SV.SLSV--;	
}

void DeleteLast_SV(DSSV &ds_SV)
{
	if(ds_SV.pHead == NULL)	return;
	if(ds_SV.pHead->pNext == NULL)
	{
		DeleteFrist_SV(ds_SV);
		return;
	}	
	for(NODESV *k = ds_SV.pHead; k != NULL; k->pNext)
	{
		if(k->pNext == ds_SV.pLast)
		{
			delete ds_SV.pLast;
			k->pNext = NULL;
			ds_SV.pLast = k;
			ds_SV.SLSV--;
			return;
		}
	}
}

//đã xóa hàm Nodethaythe
//tuyen
// ======== TẠO DANH SÁCH ID NGẪU NHIÊN ========
void TaoDayID(DanhSachID &ds, int N) 
{
    ds.n = MAX_ID_POOL ;
    ds.index = 0; // vị trí hiện tại

    for (int i = 0; i < ds.n; i++)
        ds.nodes[i] = i + 10001;

    srand((unsigned)time(NULL));
    for (int i = 0; i < ds.n - 1; i++) {
        int j = i + rand() % (N - i);
        swap(ds.nodes[i], ds.nodes[j]);
    }
}

// ======== LƯU DANH SÁCH ID VÀO FILE ========
void LuuDanhSachID(const DanhSachID &ds, const char* filename) 
{
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Loi: Khong the mo file de luu ID!\n";
        return;
    }

    // lưu cả chỉ số hiện tại để biết đã dùng tới đâu
    fout << ds.n << " " << ds.index << "\n";
    for (int i = 0; i < ds.n; i++) {
        fout << ds.nodes[i] << " ";
    }
    fout.close();
}

// ======== NẠP DANH SÁCH ID TỪ FILE ========
bool NapDanhSachID(DanhSachID &ds, const char* filename) 
{
    ifstream fin(filename);
    if (!fin.is_open()) return false;

    fin >> ds.n >> ds.index;
    for (int i = 0; i < ds.n; i++) {
        fin >> ds.nodes[i];
    }

    fin.close();
    return true;
}

// ======== LẤY ID KẾ TIẾP (THEO THỨ TỰ TRONG DANH SÁCH) ========
int LayIDKeTiep(DanhSachID &dsID) 
{
    if (ds.index >= ds.n) {
        cout << "Het ID trong danh sach! Sinh ngau nhien fallback.\n";
        return rand() % 900000 + 10000;
    }

    int id = ds.nodes[ds.index];  // lấy ID hiện tại
    ds.index++;                   // tiến đến ID tiếp theo
    return id;
}
//Tuyen
void RemoveCH(DSCH &dsch, int id)//đã sửa
{
    // ======= B1: Kiểm tra danh sách rỗng =======
    if (dsch.pHead == NULL)
    {
        string tb = "Danh sach cau hoi rong, khong co cau hoi de xoa!";
        XoaTB(130, 26);
        InTB(tb, 132, 30);
        AnConTro();
        Sleep(750);
        XoaTB(130, 26);
        return;
    }

    // ======= B2: Tìm câu hỏi cần xoá =======
    CauHoiNode p = dsch.pHead;
    CauHoiNode prev = NULL;

    while (p != NULL && p->ID != id) {
        prev = p;
        p = p->pNext;
    }

    // Không tìm thấy ID
    if (p == NULL) {
        string tb = "Khong tim thay cau hoi can xoa!";
        XoaTB(130, 26);
        InTB(tb, 132, 30);
        AnConTro();
        Sleep(750);
        XoaTB(130, 26);
        return;
    }

    // ======= B3: Kiểm tra nếu câu hỏi đã thi =======
    if (p->daThi == true) {
        string tb = "Cau hoi nay da duoc su dung trong bai thi, khong the xoa!";
        XoaTB(130, 26);
        InTB(tb, 132, 30);
        AnConTro();
        Sleep(1000);
        XoaTB(130, 26);
        return;
    }

    // ======= B4: Xoá node khỏi danh sách =======
     if (p == dsch.pHead)
    {
        dsch.pHead = p->pNext;
        if (dsch.pHead == NULL) dsch.pLast = NULL; 
    }
    else
    {
        prev->pNext = p->pNext;
        if (p == dsch.pLast) dsch.pLast = prev;   
    }

    delete p;
    dsch.SLCH--;

    // ======= B5: Thông báo xoá thành công =======
    string tb = "Xoa cau hoi thanh cong!";
    XoaTB(130, 26);
    InTB(tb, 132, 30);
    AnConTro();
    Sleep(750);
    XoaTB(130, 26);
}


void ThemDiemThiVaoDS(DSDIEM &dsd, NODEDIEMTHI *p)
{
	if(dsd.pHead == NULL)
	{
		dsd.pHead = dsd.pLast = p;
		dsd.SLDiem++;
	}
	else
	{
		dsd.pLast->pNext = p;
		dsd.pLast = p;
		dsd.SLDiem++;
	}
}
void ThemDiemThiVaoDS(DSDIEM &dsd, NODEDIEMTHI *p)
{
	if(dsd.pHead == NULL)
	{
		dsd.pHead = dsd.pLast = p;
		dsd.SLDiem++;
	}
	else
	{
		dsd.pLast->pNext = p;
		dsd.pLast = p;
		dsd.SLDiem++;
	}
}

// ==================== KIEM TRA SL THI ==========================
bool CheckSLThi (DSDIEM dsd, string mamon)
{
	for(NODEDIEMTHI *k = dsd.pHead; k != NULL; k = k->pNext)
	{
		if(k->MAMH.compare(mamon) == 0)
		{
			return true;
		}
	}
	return false;
}

void DeleteINFO_SV(DSSV &ds_SV, string mssv)
{
	if(ds_SV.pHead == NULL)	return;
	if(ds_SV.pHead->MASV.compare(mssv) == 0)
	{
		DeleteFrist_SV(ds_SV);
		return;
	}	
	if(ds_SV.pLast->MASV.compare(mssv) == 0)
	{
		DeleteLast_SV(ds_SV);
		return;
	}
	NODESV *s = new NODESV; 	
	for(NODESV *k = ds_SV.pHead; k!= NULL; k->pNext)
	{
		if(k->MASV.compare(mssv) == 0)
		{
			s->pNext = k->pNext;
			delete k;
			ds_SV.SLSV--;
			return;
		}
		s = k;
	}
}

//============================ Tim Kiem Cau Hoi =====================//

CauHoiNode TimKiemCauHoi(DSCH dsch, int id)//đã sửa
{
    if (dsch.pHead == NULL) 
        return NULL;

    for (CauHoiNode p = dsch.pHead; p != NULL; p = p->pNext) {
        if (p->ID == id) {
            return p; // tìm thấy
        }
    }

    return NULL; // không tìm thấy
}


bool CheckLopNhap (DSLOP dsl, string malop, string tenlop)
{
	for(int i = 0; i < dsl.SLLOP; i++)
	{
		if(malop.compare(dsl.DS_LOP[i]->MALOP) == 0 || tenlop.compare(dsl.DS_LOP[i]->TENLOP) == 0)
		{
			return false;
		}
	}
	return true;
}

bool CheckFormMaLop (string malop)
{
	if (malop.length() != 9 || malop[0] != 'D')
	{
		return false;
	}
	if (malop[1] < '0' || malop[1] > '9' || malop[2] < '0' || malop[2] > '9')				//1,2,7,8,9
	{
		return false;
	}
	for(int i = 7; i < 9; i++)
	{
		if(malop[i] < '0' || malop[i] > '9')
		{
			return false;
		}
	}
	for(int i = 3; i < 7; i++)
	{
		if(malop[i] < 'A' || malop[i] > 'Z')
		{
			return false;
		}
	}	
	return true;
}

bool CheckMaSV (LOP *l, string masv)
{
	for(NODESV *k = l->ds_SV.pHead; k != NULL; k = k->pNext)
	{
		if(masv.compare(k->MASV) == 0 )
		{
			return false;
		}
	}
	return true;
}

void InDSLop (DSLOP dsl, int &page)
{
	if (dsl.SLLOP == 0)
	{
		return;
	}
	int k = 2;
	int maxpage;
	if (dsl.SLLOP % 10 == 0)	maxpage = dsl.SLLOP/10;
	else maxpage = dsl.SLLOP/10 +1;
	for(int i = page*10; i < (page+1)*10; i++)
	{
		if(dsl.DS_LOP[i] == NULL)
		{
			break;
		}
		gotoxy(5+6+5,4+k);
		cout << dsl.DS_LOP[i]->TENLOP;
		gotoxy(5+6+80,4+k);
		cout << dsl.DS_LOP[i]->MALOP;
		k += 3;
	}
	gotoxy(125/2,36);
	cout << "Trang " << page + 1 << "/" << maxpage;	
}

void NhapLop(DSLOP &dsl, int page)
{	
	gotoxy(5,40);
	veKhung(5,120);
	gotoxy(7,42);
	cout << "Ma lop :";
	gotoxy(15,41);
	veKhung(3,30);
	gotoxy(80,42);
	cout << "Ten lop :";
	gotoxy(88,41);
	veKhung(3,35);
	int maxpage;
	string tenlop;
	string malop;
	char s;
	bool state = true;
	bool check;
	string tb = "Ma Lop co dang DXXCQYYXX X la so nguyen Y la chu cai";
	InTB(tb, 132, 30);
	gotoxy(17,42);
	HienConTro();
	batphim(s,check);
	while (1)
	{
		if(s == ESC)
		{
			if(Exit(s,check) == true)
			{
				break;
			}
			else
			{
				if(state == true)	gotoxy(17+malop.length(),42);
				else				gotoxy(90+tenlop.length(),42);
				HienConTro();
				batphim(s,check);
				
			}
		}
		if(dsl.SLLOP <= 10)	maxpage = 0;
		else if(dsl.SLLOP % 10 == 0) 	maxpage = dsl.SLLOP/10 -1;
		else maxpage = dsl.SLLOP/10;
		if (s == LEFT && check == false)
		{
			if (state == false)
			{
				gotoxy(17+malop.length(),42);
				state = true;
			}
		}
		if (s == RIGHT && check == false)
		{
			if (state == true)
			{
				gotoxy(90+tenlop.length(),42);
				state = false;
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && check == true)
		{
			HienConTro();
			if (state == false )
			{
				if (tenlop.length() < MAXTENLOP)
				{
					cout << inhoa(s);
					tenlop += inhoa(s);
				}
			}
			else 
			{
				if (malop.length() < MAXMALOP)
				{
					cout << inhoa(s);
					malop += inhoa(s);
				}
			}
		}
		if(s == ' ')
		{
			if(state == false)
				{
					if(tenlop.length() == 0)
					{
						gotoxy(90+tenlop.length(),42);
					}
					else if(tenlop[tenlop.length()-1]!= ' ')
					{
						cout << inhoa(s);
						tenlop += inhoa(s);	
					}
				}
		}
		if (s == BACKSPACE)
		{
			if (state == false)
			{
				if (tenlop.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					tenlop.erase(tenlop.length()-1);
				}
			}
			else
			{
				if (malop.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					malop.erase(malop.length()-1);
				}
			}
		}
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				
					for(int i = 0; i < 29;i++)
					{
						gotoxy(6,6+i);
						cout << "                                        ";
						gotoxy(66,6+i);
						cout << "                                        ";
					}
				page ++;
				InDSLop(dsl,page);
				
			}
			if(state == true)
			{
				gotoxy(17+malop.length(),42);
			}
			else
			{
				gotoxy(90+tenlop.length(),42);	
			}
			HienConTro();
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 29;i++)
				{
						gotoxy(6,6+i);
						cout << "                                        ";
						gotoxy(66,6+i);
						cout << "                                        ";
				}
				page--;
				InDSLop(dsl,page);
			}
			if(state == true)
			{
				gotoxy(17+malop.length(),42);
			}
			else
			{
				gotoxy(90+tenlop.length(),42);	
			}
			HienConTro();
		}
		if (s == ENTER)
		{
			AnConTro();
			ChuanHoaTen(tenlop);
			if(tenlop.length() == 0 || malop.length() == 0)
			{
				tb = "Ban chua nhap ten lop hoac ma lop, vui long dien day du thong tin";
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);
				gotoxy(17+malop.length(),42);
			}
			else
			{
				if(CheckFormMaLop(malop) == false)
				{
					XoaTB(130,26);
					tb = "Ban nhap sai dinh dang ma lop, vui long nhap lai";
					InTB(tb,132,30);
					AnConTro();
					Sleep(750);
					XoaTB(130,26);
					gotoxy(17+malop.length(),42);
				}
				else
				{
					if(CheckLopNhap(dsl,malop,tenlop) == false)
					{
						XoaTB(130,26);
						tb = "Ma lop hoac ten lop da bi trung, vui long nhap lai";
						InTB(tb,132,30);
						AnConTro();
						Sleep(750);
						XoaTB(130,26);
						gotoxy(17+malop.length(),42);
					}
					else
					{
						LOP *l = new LOP;
						l->MALOP = malop;
						l->TENLOP = tenlop;
						InsertLop(dsl,l);
						AnConTro();
						XoaTB(130,26);
						gotoxy(132,30);
						tb = "Them lop vao danh sach thanh cong";
						InTB(tb,132,30);
						AnConTro();
						Sleep(750);
						XoaTB(130,26);
						HienConTro();
					}
				}
			}
			for(int i = 0; i < 29;i++)
			{
				gotoxy(6,6+i);
				cout << "                                        ";
				gotoxy(66,6+i);
				cout << "                                        ";
			}
			InDSLop(dsl,page);
			malop = "";
			tenlop = "";
			gotoxy(17,42);
			cout << "                           ";
			gotoxy(90,42);
			cout << "                           ";
			gotoxy(17+malop.length(),42);
			HienConTro();
			state = true;
		}
		batphim(s,check);
	}
	AnConTro();
	for(int i = 0; i < 5; i++)
	{
		gotoxy(5,40+i);
		cout << "                                                                                                                        ";
	}
}

void ThemLop(DSLOP &dsl, int page)
{
	ChangeColor(15);
//	int n = dsl.SLLOP;
	if(dsl.SLLOP == MAXLOP)
	{
		gotoxy(130,26);
		string tb = "Khong the them lop, danh sach lop da day";
		InTB(tb,132,30);
		AnConTro();
		Sleep(750);
		XoaTB(130,26);
	}
	else
	{
		NhapLop(dsl,page);
	}
}

void NhapLopXoa(DSLOP &dsl,int &page)
{
	string tb;
	int maxpage;
	InDSLop(dsl,page);
	string malop;
	char s;
	int state = 0;
	bool check;
	gotoxy(7,6);
	cout << muiten;
	batphim(s, check);
	while (s != ESC)
	{
		if(dsl.SLLOP <= 10)	maxpage = 0;
		else if(dsl.SLLOP % 10 == 0) 	maxpage = dsl.SLLOP/10 -1;
		else maxpage = dsl.SLLOP/10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if((state > 0) )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 29;i++)
					{
						gotoxy(6,6+i);
						cout << "                                        ";
						gotoxy(66,6+i);
						cout << "                                        ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSLop(dsl,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
					
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				if(dsl.SLLOP > state + page*10 + 1)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					if(page < dsl.SLLOP/10)
					{
					
						for(int i = 0; i < 29;i++)
						{
							gotoxy(6,6+i);
							cout << "                                        ";
							gotoxy(66,6+i);
							cout << "                                        ";
						}
					}
					page++;
					InDSLop(dsl,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if(dsl.SLLOP > state + page*10 + 1 )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if(dsl.SLLOP == state + page*10 + 1  ) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                        ";
					gotoxy(66,6+i);
					cout << "                                        ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				int hd = wherex();
				int td = wherey();
				InDSLop(dsl,page);
				gotoxy(hd,td);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                        ";
					gotoxy(66,6+i);
					cout << "                                        ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				int hd = wherex();
				int td = wherey();
				InDSLop(dsl,page);
				gotoxy(hd,td);
			}
		}
		if (s == ENTER)
		{
			if(dsl.DS_LOP[state + page*10]->ds_SV.SLSV > 0)
			{
				tb = "Lop ton tai sinh vien, khong the xoa!" ;
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);
			}
			else
			{
				tb = "Ban co chac chan muon xoa lop nay ? (Y/N)";
				InTB(tb,132,30);
				batphim(s,check);
				while(s != ESC)
				{
					AnConTro();
					if((s == 'y' || s == 'Y')&& check == true)
					{
						for(int i = state + page*10; i < dsl.SLLOP; i++)
						{
							dsl.DS_LOP[i] = dsl.DS_LOP[i+1];
						}
						dsl.SLLOP--;
						XoaTB(130,26);
						gotoxy(132,30);
						tb = "Xoa lop thanh cong";
						InTB(tb,132,30);
						AnConTro();
						Sleep(750);
						XoaTB(130,26);
						break;
					}
					else if((s == 'n' || s == 'N') && check == true)
					{
						XoaTB(130,26);
						break;
					}
					batphim(s,check);
				}
			}
			for(int i = 0; i < 28;i++)
			{
				gotoxy(6,6+i);
				cout << "                                        ";
				gotoxy(66,6+i);
				cout << "                                        ";
			}	
			page = 0;
			int hd = wherex();
			int td = wherey();
			InDSLop(dsl,page);
			gotoxy(hd,td);
			cout << " ";
			state = 0;
			gotoxy(7,6);
			cout << muiten;	
		}
	batphim(s,check);
	}
}

void XoaLop (DSLOP &dsl, int &page)
{
	string tb;
	if(dsl.SLLOP  == 0)
	{
		tb = "Danh sach lop hien tai dang trong";
		InTB(tb,132,30);
		AnConTro();
		Sleep(750);
		XoaTB(130,26);
	}
	else
	{
		NhapLopXoa(dsl, page);
	}
}

void SuaLop(DSLOP &dsl, int state, int page)
{
	gotoxy(5,40);
	veKhung(5,120);
	gotoxy(7,42);
	cout << "Ma lop :";
	gotoxy(15,41);
	veKhung(3,30);
	gotoxy(80,42);
	cout << "Ten lop :";
	gotoxy(88,41);
	veKhung(3,35);
	bool sState = true;
	char s;
	bool check;
	string tenlop = dsl.DS_LOP[state + page*10]->TENLOP;
	string malop = dsl.DS_LOP[state + page*10]->MALOP;
	string tb = "Ma Lop co dang DXXCQYYXX X la so nguyen Y la chu cai";
	InTB(tb, 132,30);
	gotoxy(17,42);
	cout << malop;
	gotoxy(90,42);
	cout << tenlop;
	gotoxy(17+malop.length(),42);
	HienConTro();
	batphim(s,check);
	while(1)
	{
		if(s == ESC)
		{
			if(Exit(s,check) == true)
			{
				break;
			}
			else
			{
				if(sState == true)
				{
					gotoxy(17+malop.length(),42);
				}
				else
				{
					gotoxy(90+tenlop.length(),42);	
				}
				HienConTro();
				batphim(s,check);	
			}
		}
		if (s == LEFT && check == false)
		{
			if (sState == false)
			{
				gotoxy(17+malop.length(),42);
				sState = true;
			}
		}
		if (s == RIGHT && check == false)
		{
			if (sState == true)
			{
				gotoxy(90+tenlop.length(),42);
				sState = false;
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && check == true)
		{
			HienConTro();
			if (sState == true)
			{
				if (malop.length() < MAXMALOP)
				{
					cout << inhoa(s);
					malop += inhoa(s);
				}
			}
			else
			{
				if (tenlop.length() < MAXTENLOP)
				{
					cout << inhoa(s);
					tenlop += inhoa(s);
				}
			}
		}
		if(s == ' ')
		{
			if(sState == false)
				{
					if(tenlop.length() == 0)
					{
						gotoxy(90+tenlop.length()-1,42);
					}
					if(tenlop[tenlop.length()-1] != ' ')
					{
						cout << inhoa(s);
						tenlop += inhoa(s);	
					}
				}
		}
		if (s == BACKSPACE)
		{
			if (sState == false)
			{
				if (tenlop.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					tenlop.erase(tenlop.length()-1);
				}
			}
			else
			{
				if (malop.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					malop.erase(malop.length()-1);
				}
			}
		}
		if(s == ENTER)
		{
			if(malop.length() == 0 || tenlop.length() == 0)
			{
				XoaTB(130,26);
				tb = "Khong duoc de thieu thong tin";
				InTB(tb,132,30);
				Sleep(750);
				XoaTB(130,26);
			}
			else
			{
				if(CheckFormMaLop(malop) == false)
				{
					XoaTB(130,26);
					tb = "Sai Dinh Dang Ma Lop";
					InTB(tb,132,30);
					Sleep(750);
					XoaTB(130,26);
				}
				else if(CheckMaLop(dsl, malop) == false)
				{
					XoaTB(130,26);
					tb = "MA LOP BI TRUNG, VUI LONG NHAP LAI";
					InTB(tb,132,30);
					Sleep(750);
					XoaTB(130,26);
				}
				else
				{
					ChuanHoaTen(tenlop);
					dsl.DS_LOP[state + page*10]->TENLOP = tenlop;
					dsl.DS_LOP[state + page*10]->MALOP = malop;
					break;
				}
			}
			malop = "";
			tenlop = "";
			gotoxy(17,42);
			cout << "                           ";
			gotoxy(90,42);
			cout << "                           ";
			gotoxy(17,42);
			sState = true;
		}
		batphim(s,check);
	}
	AnConTro();
	for(int i = 0; i < 5; i++)
	{
		gotoxy(5,40+i);
		cout << "                                                                                                                        ";
	}
}

void NhapLopChinh(DSLOP &dsl , int &page)
{
	int maxpage;
	InDSLop(dsl,page);
	string malop;
	char s;
	int state = 0;
	bool check;
	gotoxy(7,6);
	cout << muiten;
	batphim(s,check);
	while (s != ESC)
	{
		if(dsl.SLLOP <= 10)	maxpage = 0;
		else if(dsl.SLLOP % 10 == 0)	maxpage = dsl.SLLOP/10 -1;
		else maxpage = dsl.SLLOP/10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if((state > 0) )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 29;i++)
					{
						gotoxy(6,6+i);
						cout << "                                        ";
						gotoxy(66,6+i);
						cout << "                                        ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSLop(dsl,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				if(dsl.SLLOP > state + page*10 + 1)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 29;i++)
					{
						gotoxy(6,6+i);
						cout << "                                        ";
						gotoxy(66,6+i);
						cout << "                                        ";
					}
					page++;
					InDSLop(dsl,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if(dsl.SLLOP > state + page*10 + 1)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if(dsl.SLLOP == state + page*10 + 1) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                        ";
					gotoxy(66,6+i);
					cout << "                                        ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSLop(dsl,page);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                        ";
					gotoxy(66,6+i);
					cout << "                                        ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSLop(dsl,page);
				gotoxy(8,6);
			}
		}
		if (s == ENTER)
		{
			if( dsl.DS_LOP[state + page*10]->ds_SV.SLSV > 0)
			{
				string tb = "Lop ton tai sinh vien, khong the chinh sua";
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);
			}
			else
			{
				// ham nhap thong tin de sua
				SuaLop(dsl, state, page);
			}
			for(int i = 0; i < 28;i++)
			{
				gotoxy(6,6+i);
				cout << "                                        ";
				gotoxy(66,6+i);
				cout << "                                        ";
			}
			page = 0;
			int hd = wherex();
			int td = wherey();
			InDSLop(dsl,page);
			gotoxy(hd,td);
			cout << " ";
			state = 0;
			gotoxy(7,6);
			cout << muiten;
		}
	batphim(s,check);
	}
}

void ChinhLop(DSLOP &dsl, int &page)
{
	if(dsl.SLLOP  == 0)
	{
		string tb = "Danh sach lop hien tai dang trong";
		InTB(tb,132,30);
		AnConTro();
		Sleep(750);
		XoaTB(130,26);
	}
	else
	{
		NhapLopChinh(dsl, page);
	}
}

void FunctionLop(DSLOP &dsl)
{
	// ve bang + chuc nang trai phai de qua trang;
	// 3 nut them xoa sua lop + len xuong
	// thong bao
	// bang nhap thong tin
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat	PGUP: Qua trang	  PGDOWN: Lui trang	UP: Len	  DOWN: Xuong";
	int maxpage;
	gotoxy(130,26);
	vekhungTB(10,36);
	int page = 0;
	char s;
	bool check;
	gotoxy(5,2);
	int state = 0;
	vekhungDS(34,120,2);	
	veNut(3,15,150,10,"Them lop",240);
	veNut(3,15,150,15,"Xoa lop",20);
	veNut(3,15,150,20,"Sua lop",20);
	gotoxy(32,3);
	cout << "TEN LOP";
	gotoxy(93,3);
	cout << "MA LOP";
	if (dsl.SLLOP != 0) 
	{
		InDSLop(dsl,page);
	}
	batphim(s,check);
	while(s != ESC)
	{
		if(dsl.SLLOP <= 10)		maxpage = 0;
		else if(dsl.SLLOP % 10 == 0)	maxpage = dsl.SLLOP/10 - 1;
		else maxpage = dsl.SLLOP/10;
		if (s == UP && check == false)
		{
			switch(state)
			{
			case 0:
				{
					break;
				}
			case 1:
				{
					state--;
					veNut(3,15,150,15,"Xoa lop",20);
					veNut(3,15,150,10,"Them lop",240);
					break;
				}
			case 2:
				{
					state--;
					veNut(3,15,150,20,"Sua lop",20);
					veNut(3,15,150,15,"Xoa lop",240);
					break;
				}
			}
		}
		if (s == DOWN && check == false)
		{
			switch(state)
			{
			case 0:
				{
					state++;
					veNut(3,15,150,10,"Them lop",20);
					veNut(3,15,150,15,"Xoa lop",240);
					break;
				}
			case 1:
				{
					state++;
					veNut(3,15,150,15,"Xoa lop",20);
					veNut(3,15,150,20,"Sua lop",240);
					break;
				}
			case 2:
				{
					break;
				}
			}
		}
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                              ";
						gotoxy(66,6+i);
						cout << "                                              ";
					}
				page ++;
				InDSLop(dsl,page);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                        ";
					gotoxy(66,6+i);
					cout << "                                        ";
				}
				page--;
				InDSLop(dsl,page);
			}
		}
		if(s == ENTER)
		{
			switch(state)
			{
				case 0:
					{
						ThemLop(dsl,page);
						AnConTro();
						break;
					}
				case 1:
					{
						XoaLop(dsl,page);
						for(int i = 0; i < 28;i++)
						{
							gotoxy(6,6+i);
							cout << "                                        ";
							gotoxy(66,6+i);
							cout << "                                        ";
						}
						InDSLop(dsl,page);
						AnConTro();
						break;
					}
				case 2:
					{
						ChinhLop(dsl,page);
						for(int i = 0; i < 28;i++)
						{
							gotoxy(6,6+i);
							cout << "                                        ";
							gotoxy(66,6+i);
							cout << "                                        ";
						}
						InDSLop(dsl,page);
						AnConTro();
						break;
					}	
			}
		}
	batphim(s,check);	
	}
}

void InDSSV (DSSV ds_SV, int page)
{
	if (ds_SV.pHead == NULL)
	{
		return;
	}
	int k = 2;
	int sl = ds_SV.SLSV;
	int maxpage;
	if(sl <= 10)	maxpage = 1;
	else if (sl % 10 == 0)	maxpage = sl/10;
	else maxpage = sl/10 + 1;
	NODESV *j = ds_SV.pHead;;
	if(page > 0)
	{
		for (int i = 0; i < page*10; i++)
			if (j->pNext != NULL)	j = j->pNext;	
	}
	for(int i = 0; i < 10; i++)
	{
		if (j->pNext != NULL) 
		{ 
			gotoxy(12,4+k);
			cout << j->MASV;
			gotoxy(40,4+k);
			cout << j->HO << " " << j->TEN;
			gotoxy(80+(25-j->PHAI.length())/2,4+k);
			cout << j->PHAI;
			k += 3;
			j = j->pNext;
		}
		else 
		{
			gotoxy(12,4+k);
			cout << j->MASV;
			gotoxy(40,4+k);
			cout << j->HO << " " << j->TEN;
			gotoxy(80+(25-j->PHAI.length())/2,4+k);
			cout << j->PHAI;
			k += 3;
			break;
		}
	}
	gotoxy(125/2,36);
	cout << "Trang " << page + 1 << "/" << maxpage;
}
#include <conio.h>

// Hàm nhập mật khẩu và ẩn ký tự
string NhapMatKhau(int x, int y, int maxlen) {
    string pw = "";
    char ch;
    gotoxy(x, y);
    while (true) {
        ch = getch();
        if (ch == 13) break; // ENTER -> kết thúc
        else if (ch == 8) { // BACKSPACE
            if (!pw.empty()) {
                pw.pop_back();
                cout << "\b \b"; // xóa 1 dấu '*'
            }
        }
        else if (pw.length() < maxlen && ch >= 32 && ch <= 126) {
            pw += ch;
            cout << "*";
        }
    }
    return pw;
}

void NhapSinhVien(LOP *&l)
{
	AnConTro();
	int maxpage;
	gotoxy(130,26);
	vekhungTB(10,36);
	gotoxy(15,3);
	cout << "MA SV";
	gotoxy(50,3);
	cout << "HO VA TEN";
	gotoxy(88,3);
	cout << "GIOI TINH";
	gotoxy(140-20,22);
	cout << "NHAP SINH VIEN";
	gotoxy(110,2);
	veKhung(20,44);
	gotoxy(112,2+3);
	cout << "Ma SV:";
	gotoxy(122,2+2);
	veKhung(3,30);
	gotoxy(112,2+7);
	cout << "Ho va Ten:";
	gotoxy(122,2+6);
	veKhung(3,30);
	gotoxy(112,2+11);
	cout << "Gioi Tinh:";
	veNut(3,9,123,12,"NAM",240);
	veNut(3,9,142,12,"NU",15);
	gotoxy(112,2+15);
	cout << "Mat khau:";
	gotoxy(122,2+14);
	veKhung(3,30);
	int hd , td;
	int page = 0;
	string mk;
	string masv;
	string hoten;
	string gt = "NAM";
	string tb ="MSSV co dang NXXDCYYXXX voi X la so nguyen Y la chu cai!";
	InTB(tb,132,30);
	AnConTro();
	char s;
	int state = 0;
	bool check;
	gotoxy(124,2+3);
	HienConTro();
	batphim(s,check);
	while (1)
	{
		if(s == ESC)
		{
			if(Exit(s,check) == true)
			{
				break;
			}
			else
			{
				tb = "MSSV co dang NXXDCYYXXX voi X la so nguyen Y la chu cai!";
				InTB(tb,132,30);
				switch(state)
				{
					case 0:
						{
							gotoxy(124+masv.length(),3+2);
							break;
						}
					case 1:	
						{
							gotoxy(124+hoten.length(),3+6);
							break;
						}
					case 2:
						{
							gotoxy(124+mk.length(),3+14);
							break;
						}	
				}
				HienConTro();
				batphim(s,check);		
			}
		}
		if(l->ds_SV.SLSV < 10)	maxpage = 0;
		else if(l->ds_SV.SLSV % 10 == 0)	maxpage = l->ds_SV.SLSV/10 - 1;
		else maxpage = l->ds_SV.SLSV/10;
		HienConTro();
		if(s == LEFT && check == false)
		{
			hd = wherex();
			td = wherey();
			veNut(3,9,123,12,"NAM",240);
			veNut(3,9,142,12,"NU",15);
			gotoxy(hd,td);
			gt = "NAM";
			
		}
		if(s == RIGHT && check == false)
		{
			hd = wherex();
			td = wherey();
			veNut(3,9,123,12,"NAM",15);
			veNut(3,9,142,12,"NU",240);
			gotoxy(hd,td);
			gt = "NU";
		}
		if (s == UP && check == false)
		{
			HienConTro();
			switch(state)
			{
				case 1:
					{
						gotoxy(124+masv.length(),3+2);
						state --;
						break;
					}
				case 2:	
					{
						gotoxy(124+hoten.length(),3+6);
						state --;
						break;
					}
			}
		}
		if (s == DOWN && check == false)
		{
			HienConTro();
			switch(state)
			{
				case 0:
					{
						gotoxy(124+hoten.length(),3+6);
						state ++;
						break;
					}
				case 1:	
					{
						gotoxy(124+mk.length(),3+14);
						state ++;
						break;
					}
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9'))  && check == true)
		{
			HienConTro();
			switch(state)
			{
				case 0:
{
    if (masv.length() < MAXMASV)
    {
        s = toupper(s);  // luôn in hoa
        bool hopLe = false;
        int pos = masv.length();

        // Quy tắc định dạng từng vị trí
        if (pos == 0 && s == 'N') hopLe = true;
        else if ((pos == 1 || pos == 2 || pos >= 7) && isdigit(s)) hopLe = true;
        else if ((pos == 3 || pos == 4 || pos == 5 || pos == 6) && isalpha(s)) hopLe = true;

        if (hopLe)
        {
            masv += s;
            cout << s;
        }
        else
        {
            string tb = "Sai dinh dang MSSV!";
            XoaTB(130,26);
            InTB(tb,132,30);
            Sleep(500);
            tb = "MSSV co dang NXXDCYYXXX voi X la so nguyen Y la chu cai!";
            InTB(tb,132,30);
            gotoxy(124 + masv.length(), 3 + 2);
        }
    }
    break;
}

				case 1:
{
    if (isalpha(s) && check == true)
    {
        s = toupper(s);
        if (hoten.length() < MAXHO + MAXTEN)
        {
            cout << s;
            hoten += s;
        }
    }
    else if (s == ' ')
    {
        // Không cho phép dấu cách đầu hoặc 2 dấu cách liên tiếp
        if (!hoten.empty() && hoten.back() != ' ')
        {
            cout << ' ';
            hoten += ' ';
        }
    }
    break;
}

				case 2:
					{
						if (state == 2)
{
    gotoxy(124, 16); // Tọa độ ô nhập mật khẩu (thay số nếu bạn vẽ khung khác)
    mk = NhapMatKhau(124, 16, MAXPW);
}

						break;
					}	
			}
		}
		if(s == ' ')
		{
			if(state == 1)
				{
					if(hoten.length() == 0)	gotoxy(124+hoten.length()-1,3+6);
					if(hoten[hoten.length()-1]!= ' ')
					{
						cout << inhoa(s);
						hoten += inhoa(s);	
					}
				}
		}
		if (s == BACKSPACE)
		{
			switch(state)
			{
				case 0:
					{
						if (masv.length() > 0)
						{
							AnConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							gotoxy(wherex()-1,wherey());
							HienConTro();
							masv.erase(masv.length()-1);
						}
						break;
					}
				case 1:
					{
						if (hoten.length() > 0)
						{
							AnConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							gotoxy(wherex()-1,wherey());
							HienConTro();
							hoten.erase(hoten.length()-1);
						}
						break;
					}
				case 2:
					{
						if (mk.length() > 0)
						{
							AnConTro();
							gotoxy(wherex()-1,wherey());
							cout << " ";
							gotoxy(wherex()-1,wherey());
							HienConTro();
							mk.erase(mk.length()-1);
						}
						break;
					}	
			}	
		}
		if (s == PAGEDOWN && check == false)
		{
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page ++;
				InDSSV(l->ds_SV,page);
				gotoxy(124+masv.length(),3+2);
				HienConTro();
			}
		}
		if(s == PAGEUP && check == false)
		{
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page--;
				InDSSV(l->ds_SV,page);
				gotoxy(124+masv.length(),3+2);
				HienConTro();
			}
		}
		if (s == ENTER)
		{
			for(int i = 0; i < 28;i++)
			{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
			}
			bool ktten = false;
			ChuanHoaTen(hoten);	
			if (masv.length() == 0 || hoten.length() == 0 || mk.length() == 0)
			{
				tb = "Vui long dien day du thong tin sinh vien";
				XoaTB(130,26);
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);
			}
			else
			{
				if(CheckFormMaSv(masv) == true)
				{
						if(CheckMaSV(l,masv) == false)
						{
							tb = "Ma sinh vien da co trong danh sach";
							XoaTB(130,26);
							InTB(tb,132,30);
							AnConTro();
							Sleep(750);
							XoaTB(130,26);
						}
						else
						{
							NODESV *p = new NODESV;
							p->MASV = masv;
							p->HO = TachHoSV(hoten);
							gotoxy(1,1);
							p->TEN = TachTenSV(hoten);
							p->PASSWORD = mk;
							p->PHAI = gt;
							p->pNext = NULL;
							for(int i = 0; i < hoten.length(); i ++)// can it nhat 1 dau cach de phan biet ho va ten
							{
								if (hoten[i] == ' ')
								{
									ktten = true;
									break;
								}
							}
							if(ktten == true)
							{
								ThemSVVaoDS(l->ds_SV, p);
								tb = "Them sinh vien vao danh sach thanh cong";
								XoaTB(130,26);
								InTB(tb,132,30);
								AnConTro();
								Sleep(750);
								XoaTB(130,26);
							}
							else
							{
								tb = "Ho ten khong dung dinh dang, vui long nhap lai";
								XoaTB(130,26);
								InTB(tb,132,30);
								AnConTro();
								Sleep(750);
								XoaTB(130,26);
							}
						} 
				}
				else
				{
					tb = "Ma sinh vien khong dung dinh dang, vui long nhap lai";
					XoaTB(130,26);
					InTB(tb,132,30);
					AnConTro();
					Sleep(750);
					XoaTB(130,26);
				}
			}
			tb = "MSSV co dang NXXDCYYXXX voi X la so nguyen Y la chu cai!";
			InTB(tb,132,30);			
			InDSSV(l->ds_SV,page);
			masv = "";
			hoten = "";
			mk = "";
			gotoxy(124+masv.length(),3+2);
			cout << "                           ";
			gotoxy(124+masv.length(),7+2);
			cout << "                           ";
			gotoxy(124+masv.length(),15+2);
			cout << "                           ";
			gotoxy(124+masv.length(),3+2);
			HienConTro();
			state = 0;
		}
	batphim(s,check);
	}
	for (int i=2; i<23; i++)
	{
		gotoxy(110,i);
		cout << "                                             ";
	}
	AnConTro();
}

void NhapMaLop(DSLOP &dsl , int page)
{
	string malop;
	int hd;
	int td;
	gotoxy(130,26);
	vekhungTB(10,36);
	string tb = "Nhap ma lop co dang DXXCQYYXX voi X la so nguyen con Y la chu cai!";
	InTB(tb,132,30);
	gotoxy(5,37);
	veKhung(8,40);
	gotoxy(5+3,40);
	cout << "Nhap ma lop :";
	gotoxy(5+17,39);
	veKhung(3,20);
	gotoxy(5+18,40);
	HienConTro();
	char s;
	bool check;
	batphim(s,check);
	while(s != ESC)
	{
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && check == true)
		{
			HienConTro();
			if (malop.length() < MAXMALOP)
			{
				cout << inhoa(s);
				malop += inhoa(s);
			}
		}
		if (s == BACKSPACE)
		{
			if (malop.length() > 0)
			{
				AnConTro();
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(wherex()-1,wherey());
				HienConTro();
				malop.erase(malop.length()-1);
			}	
		}
		if(s == ENTER)
		{
			if(CheckFormMaLop(malop) == true)
			{
				if(CheckMaLop(dsl,malop) == true)
				{
					XoaTB(130,26);
					tb = "Ma lop khong ton tai";
					InTB(tb,132,30);
					AnConTro();
					Sleep(750);
					XoaTB(130,26);
				}
				else
				{
					for(int i = 0; i < dsl.SLLOP; i++)
					{
						if(dsl.DS_LOP[i]->MALOP.compare(malop) == 0)
						{
							hd = wherex();
							td = wherey();
							system("cls");
							gotoxy(5,2);
							VeKhungDSLop(34,100,4);
							gotoxy(15,3);
							cout << "MA SV";
							gotoxy(50,3);
							cout << "HO VA TEN";
							gotoxy(88,3);
							cout << "GIOI TINH";
							InDSSV(dsl.DS_LOP[i]->ds_SV,page);
							NhapSinhVien(dsl.DS_LOP[i]);
							gotoxy(hd,td);
						}
					}
					system("cls");
					gotoxy(5,37);
					veKhung(8,40);
					gotoxy(130,26);
					vekhungTB(10,36);
					tb = "Nhap ma lop co dang DXXCQYYXX voi X la so nguyen con Y la chu cai!";
					InTB(tb,132,30);
					gotoxy(5+3,40);
					cout << "Nhap ma lop :";
					gotoxy(5+17,39);
					veKhung(3,20);
					gotoxy(22,3);
					cout << "TEN LOP";
					gotoxy(63,3);
					cout << "MA LOP";
					gotoxy(5,2);
					vekhungDS(34,120,2);
				}
			}
			else
			{
				XoaTB(130, 26);
				tb = "Ban nhap sai dinh dang ma lop, vui long nhap lai";
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);
			}
			for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                        ";
						gotoxy(66,6+i);
						cout << "                                        ";
					}
			malop = "";
			gotoxy(5+18,40);
			cout << "          ";
			gotoxy(5+18,40);
		}
		hd = wherex();
		td = wherey();
		InDSLop(dsl,page);
		gotoxy(hd,td);
		HienConTro();
		batphim(s,check);
	}
	for(int i = 0; i < 8; i++)
	{
		gotoxy(5,37+i);
		cout << "                                        ";
	}
}

void XoaSinhVien(DSSV &ds_SV ,int page)
{
	for (int i=2; i<23; i++)
	{
		gotoxy(110,i);
		cout << "                                             ";
	}
	gotoxy(50,46);
	cout << "           	          	               	                 	                    	                         ";
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat	PGUP: Qua trang	PGDOWN: Lui trang	UP,DOWN: Len Xuong";
	AnConTro();
	gotoxy(15,3);
	cout << "MA SV";
	gotoxy(50,3);
	cout << "HO VA TEN";
	gotoxy(88,3);
	cout << "GIOI TINH";
	gotoxy(110,2);
	gotoxy(7,6);
	cout << muiten;
	int maxpage;
	int state = 0;
	char s;
	bool check;
	batphim(s,check);
	while(s != ESC)
	{
		if(ds_SV.SLSV < 10) maxpage = 0;
		else if(ds_SV.SLSV % 10 == 0) maxpage = ds_SV.SLSV/10 - 1;
		else maxpage = ds_SV.SLSV/10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if(state > 0 )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(81,6+i);
						cout << "                      ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSSV(ds_SV,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;					
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				NODESV *k = ds_SV.pHead;
				for(int i =0; i < state + page*10; i++)
					if(k->pNext != NULL)	k = k->pNext;
				if(k->pNext != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(81,6+i);
						cout << "                      ";
					}
					page++;
					InDSSV(ds_SV,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				NODESV *k = ds_SV.pHead;
				for(int i=0; i< state + page*10; i++)
					if (k->pNext != NULL)	k = k->pNext;
				if(k->pNext != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				else 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSSV(ds_SV,page);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSSV(ds_SV,page);
				gotoxy(8,6);
			}
		}
		if (s == ENTER)
		{
			string tb = "Ban co chac chan muon sinh vien nay ? (Y/N)";
			InTB(tb,132,30);
			NODESV *k = ds_SV.pHead;
			for (int i = 0; i < state + page*10; i++)
				if (k->pNext != NULL)	k = k->pNext;
			batphim(s,check);
			while(s != ESC)
			{
				AnConTro();
				if((s == 'y' || s == 'Y')&& check == true)
				{
					DeleteINFO_SV(ds_SV, k->MASV);
					XoaTB(130,26);
					gotoxy(132,30);
					tb = "Xoa sinh vien thanh cong";
					InTB(tb,132,30);
					AnConTro();
					Sleep(750);
					XoaTB(130,26);
					break;	
				}
				else if((s == 'n' || s == 'N') && check == true)
				{
					XoaTB(130,26);
					break;
				}
				batphim(s,check);
			}
			for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(81,6+i);
						cout << "                      ";
					}	
			page = 0;
			int hd = wherex();
			int td = wherey();
			if (ds_SV.pHead != NULL)
			{
				InDSSV(ds_SV,page);
				gotoxy(hd,td);
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;	
			}
			else 
			{
				break;
			}	
		}
	batphim(s,check);
	}	
}

void SeLectFunctionSV(Lop *&l ,int page)
{
	system("cls");
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat	  PGUP: Qua trang	  PGDOWN: Lui trang	   UP,DOWN: Len Xuong	  LEFT,RIGHT: Chon gioi tinh";
	gotoxy(130,26);
	vekhungTB(10,36);
	char s;
	bool check;
	gotoxy(5,2);
	int state = 0;
	gotoxy(5,2);
	VeKhungDSLop(34,100,4);
	gotoxy(15,3);
	cout << "MA SV";
	gotoxy(50,3);
	cout << "HO VA TEN";
	gotoxy(88,3);
	cout << "GIOI TINH";
	InDSSV(l->ds_SV,page);	
	veNut(3,15,120,10,"Them SV",240);
	veNut(3,15,120,15,"Xoa SV",20);
	int maxpage;
	batphim(s,check);
	while(s != ESC)
	{
		if(l->ds_SV.SLSV < 10)	maxpage = 0;
		else if(l->ds_SV.SLSV % 10 == 0)	maxpage = l->ds_SV.SLSV/10 - 1;
		else maxpage = l->ds_SV.SLSV/10;
		if (s == UP && check == false)
		{
			switch(state)
			{
			
			case 0:
				{
					break;
				}
			case 1:
				{
					state--;
					veNut(3,15,120,15,"Xoa SV",20);
					veNut(3,15,120,10,"Them SV",240);
					break;
				}
			}
		}
		if (s == DOWN && check == false)
		{
			switch(state)
			{
			case 0:
				{
					state++;
					veNut(3,15,120,10,"Them SV",20);
					veNut(3,15,120,15,"Xoa SV",240);
					break;
				}
			case 1:
				{
					break;
				}
			}
		}
		if (s == PAGEDOWN && check == false)
		{
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page ++;
				InDSSV(l->ds_SV,page);
				AnConTro();
			}
		}
		if(s == PAGEUP && check == false)
		{
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                      ";
					gotoxy(31,6+i);
					cout << "                                             ";
					gotoxy(81,6+i);
					cout << "                      ";
				}
				page--;
				InDSSV(l->ds_SV,page);
				AnConTro();
			}
		}
		if(s == ENTER)
		{
			switch(state)
			{
				case 0:
					{
						NhapSinhVien(l);
						gotoxy(15,3);
						cout << "MA SV";
						gotoxy(50,3);
						cout << "HO VA TEN";
						gotoxy(88,3);
						cout << "GIOI TINH";
						InDSSV(l->ds_SV,page);	
						veNut(3,15,120,10,"Them SV",240);
						veNut(3,15,120,15,"Xoa SV",20);	
						break;
					}
				case 1:
					{
						if (l->ds_SV.pHead == NULL)
						{
							string tb = "Danh sach SV hien dang trong! Khong the xoa!";
							InTB(tb,132,30);
							AnConTro();
							Sleep(750);
							XoaTB(130,26);
							break;
						}
						else 
						{
							XoaSinhVien(l->ds_SV,page);	
							gotoxy(15,3);
							cout << "MA SV";
							gotoxy(50,3);
							cout << "HO VA TEN";
							gotoxy(88,3);
							cout << "GIOI TINH";
							if (l->ds_SV.pHead == NULL)
							{
								string tb = "Danh sach SV hien dang trong! Khong the tiep tuc xoa!";
								InTB(tb,132,30);
								AnConTro();
								Sleep(750);
								XoaTB(130,26);
								gotoxy(7,6);
								cout << " ";
								veNut(3,15,120,10,"Them SV",20);
								veNut(3,15,120,15,"Xoa SV",240);
								break;
							}
							else 
							{
								InDSSV(l->ds_SV,page);	
								gotoxy(7,6);
								cout << " ";
								veNut(3,15,120,10,"Them SV",20);
								veNut(3,15,120,15,"Xoa SV",240);	
								break;	
							}							
						}
					}
			}
		}
	batphim(s,check);	
	}
}

void FunctionSV(DSLOP &dsl)
{
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat	 F1: Tim Lop	  PGUP: Qua trang	PGDOWN: Lui trang    UP: Len	DOWN: Xuong";
	gotoxy(130,26);
	vekhungTB(10,36);
	int page = 0;
	int maxpage;
	int hd;
	int td;	
	gotoxy(5,2);
	vekhungDS(34,120,2);
	gotoxy(32,3);
	cout << "TEN LOP";
	gotoxy(93,3);
	cout << "MA LOP";
	InDSLop(dsl,page);
	gotoxy(7,6);
	cout << muiten;
	int state = 0;
	char s;
	bool check;
	batphim(s,check);
	while(s != ESC)
	{
		if(dsl.SLLOP <= 10)	maxpage = 0;
		else if(dsl.SLLOP % 10 == 0)	maxpage = dsl.SLLOP/10 -1;
		else maxpage = dsl.SLLOP/10;
		ChangeColor(15);
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                        ";
						gotoxy(66,6+i);
						cout << "                                        ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSLop(dsl,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;	
				}
				
			}
			
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				if(dsl.SLLOP > state + page*10 + 1)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                        ";
						gotoxy(66,6+i);
						cout << "                                        ";
					}
					page++;
					InDSLop(dsl,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if(dsl.SLLOP > state + page*10 + 1)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if(dsl.SLLOP == state + page*10 + 1) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
			
		}
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                        ";
					gotoxy(66,6+i);
					cout << "                                        ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSLop(dsl,page);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                        ";
					gotoxy(66,6+i);
					cout << "                                        ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSLop(dsl,page);
				gotoxy(8,6);
			}
		}
		if (s == F1 && check == false)
		{
			hd = wherex();
			td = wherey();
			NhapMaLop(dsl,page);
			for(int i = 0; i < 28;i++)
			{
				gotoxy(6,6+i);
				cout << "                                       ";
				gotoxy(66,6+i);
				cout << "                                       ";
			}
			InDSLop(dsl,page);	
			gotoxy(hd-1,td);
			cout << muiten;
			AnConTro();	
		}
		if (s == ENTER)
		{
			SeLectFunctionSV(dsl.DS_LOP[state + page*10],page);
			system("cls");
			gotoxy(50,46);
			cout << "ENTER: Chon	ESC: Thoat	 F1: Tim Lop	  PGUP: Qua trang	PGDOWN: Lui trang    UP: Len	DOWN: Xuong"; 
			gotoxy(5,2);
			vekhungDS(34,120,2);
			gotoxy(32,3);
			cout << "TEN LOP";
			gotoxy(93,3);
			cout << "MA LOP";
			InDSLop(dsl,page);
			state = 0;
			AnConTro();
			gotoxy(7,6);
			cout << muiten;	
		}
		batphim(s,check);
	}
}
// ====================== ĐẾM SỐ NODE KHÔNG ĐỆ QUY ======================   đã sửa 31/10
int countMon(NodeMon* root) {
    if (!root) return 0;

    StackMon S;
    initStack(S);
    int count = 0;

    push(S, root, 0);
    NodeMon* node;
    int kieu;
    while (!isEmpty(S)) {
        pop(S, node, kieu);
        if (node == nullptr) continue;
        count++;
        if (node->pRight) push(S, node->pRight, 0);
        if (node->pLeft)  push(S, node->pLeft, 0);
    }
    return count;
}

// ====================== INORDER KHÔNG ĐỆ QUY CÓ PHÂN TRANG ======================
void inorderPrint(NodeMon* root, int &index, int start, int end, int &y) {
    if (!root) return;

    StackMon S;
    initStack(S);

    NodeMon* current = root;
    NodeMon* tmp;
    int kieu;

    while (current != nullptr || !isEmpty(S)) {
        while (current != nullptr) {
            push(S, current, 0);
            current = current->pLeft;
        }

        pop(S, tmp, kieu);
        if (tmp == nullptr) continue;

        if (index >= start && index < end) {
            gotoxy(5, y);
            cout << setw(15) << left << tmp->MAMH;
            gotoxy(40, y);
            cout << setw(40) << left << tmp->TENMH;
            y += 2;
        }
        index++;

        current = tmp->pRight;
    }
}


// In 1 trang (10 dòng)
void InDSMon(NodeMon* root, int page) {//đã sửa
    const int perPage = 10;
    int total = countMon(root);
    int maxpage = (total == 0) ? 0 : ((total - 1) / perPage);
    if (page < 0) page = 0;
    if (page > maxpage) page = maxpage;

    int start = page * perPage;
    int end = min(total, start + perPage);

    // In header
    gotoxy(30, 3); cout << "MA MON HOC";
    gotoxy(90, 3); cout << "TEN MON HOC";

    int index = 0;
    int y = 5;
    inorderPrint(root, index, start, end, y);

    gotoxy(5, 46);
    cout << "Trang " << page + 1 << "/" << maxpage + 1;
}
// sửa từ trên tới đây

void NhapMonHoc(NodeMon* &root, int page)// đã sửa
{
	
    gotoxy(5,40);
    veKhung(5,120);
    gotoxy(7,42);
    cout << "Ma mon :";getline(cin, mh.MAMH);
    gotoxy(15,41);
    veKhung(3,30);
    gotoxy(80,42);
    cout << "Ten mon :";getline(cin, mh.TENMH);
    gotoxy(88,41);
    veKhung(3,35);
	dsm = insertMon(root, mh);
++;
    int maxpage;
    string tenmon;
    string mamon;
    char s;
    bool state = true;
    bool check;
    string tb;
    //int hd; int td; // nếu không dùng thì xóa
    gotoxy(17,42);
    HienConTro();
    batphim(s,check);

    while (1)
    {
        if (s == ESC)
        {
            if (Exit(s,check) == true)
            {
                break;
            }
            else
            {
                if (state == true) gotoxy(17 + mamon.length(), 42);
                else gotoxy(90 + tenmon.length(), 42);
                HienConTro();
                batphim(s,check);
                continue;
            }
        }

        // Tính maxpage dựa trên số phần tử trong cây
        int total = countMon(root);
        if (total <= 10) maxpage = 0;
        else if (total % 10 == 0) maxpage = total / 10 - 1;
        else maxpage = total / 10;

        if (s == LEFT && check == false)
        {
            if (state == false)
            {
                gotoxy(17 + mamon.length(), 42);
                state = true;
            }
        }
        if (s == RIGHT && check == false)
        {
            if (state == true)
            {
                gotoxy(90 + tenmon.length(), 42);
                state = false;
            }
        }
        if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && check == true)
        {
            HienConTro();
            if (state == false )
            {
                if (tenmon.length() < 30)
                {
                    cout << inhoa(s);
                    tenmon += inhoa(s);
                }
            }
            else
            {
                if (mamon.length() < 20)
                {
                    cout << inhoa(s);
                    mamon += inhoa(s);
                }
            }
        }

        if (s == BACKSPACE)
        {
            if (state == false)
            {
                if (tenmon.length() > 0)
                {
                    AnConTro();
                    gotoxy(wherex()-1, wherey());
                    cout << " ";
                    gotoxy(wherex()-1, wherey());
                    HienConTro();
                    tenmon.erase(tenmon.length()-1);
                }
            }
            else
            {
                if (mamon.length() > 0)
                {
                    AnConTro();
                    gotoxy(wherex()-1, wherey());
                    cout << " ";
                    gotoxy(wherex()-1, wherey());
                    HienConTro();
                    mamon.erase(mamon.length()-1);
                }
            }
        }

        if (s == PAGEDOWN && check == false)
        {
            AnConTro();
            if (page < maxpage)
            {
                for (int i = 0; i < 28; i++)
                {
                    gotoxy(6,6+i);
                    cout << "                                                          ";
                    gotoxy(66,6+i);
                    cout << "                                                            ";
                }
                page++;
                InDSMon(root, page);
            }
            if (state == true) gotoxy(17 + mamon.length(), 42);
            else gotoxy(90 + tenmon.length(), 42);
            HienConTro();
        }

        if (s == PAGEUP && check == false)
        {
            AnConTro();
            if (page > 0)
            {
                for (int i = 0; i < 28; i++)
                {
                    gotoxy(6,6+i);
                    cout << "                                                          ";
                    gotoxy(66,6+i);
                    cout << "                                                          ";
                }
                page--;
                InDSMon(root, page);
            }
            if (state == true) gotoxy(17 + mamon.length(), 42);
            else gotoxy(90 + tenmon.length(), 42);
            HienConTro();
        }

        if (s == ENTER)
        {
            AnConTro();
            ChuanHoaTen(tenmon);
            if (tenmon.length() == 0 || mamon.length() == 0)
            {
                tb = "Ban chua nhap ten mon hoac ma mon, vui long dien day du thong tin";
                InTB(tb,132,30);
                AnConTro();
                Sleep(750);
                XoaTB(130,26);
                gotoxy(17 + mamon.length(), 42);
            }
            else
            {
                // Kiểm tra trùng: dùng CheckMonNhap(root,...)
                if (CheckMonNhap(root, mamon, tenmon) == false)
                {
                    XoaTB(130,26);
                    tb = "Ma mon hoac ten mon da bi trung, vui long nhap lai";
                    InTB(tb,132,30);
                    AnConTro();
                    Sleep(750);
                    XoaTB(130,26);
                    gotoxy(17 + mamon.length(), 42);
                }
                else
                {
                  

                    AnConTro();
                    XoaTB(130,26);
                    gotoxy(132,30);
                    tb = "Them mon vao danh sach thanh cong";
                    InTB(tb,132,30);
                    AnConTro();
                    Sleep(750);
                    XoaTB(130,26);
                    HienConTro();
                }
            }
            MonHoc mh; 
            mh.MAMH = mamon;
            mh.TENMH = tenmon;
            ChuanHoaTen(mh.TENMH);
            root = InsertMon(root, mh);
        
            // Làm mới vùng hiển thị danh sách (xóa cũ rồi in lại)
            for (int i = 0; i < 28; i++)
            {
                gotoxy(6,6+i);
                cout << "                                                          ";
                gotoxy(66,6+i);
                cout << "                                                          ";
            }
            InDSMon(root, page);

            mamon.clear();
            tenmon.clear();
            gotoxy(17,42);
            cout << "                           ";
            gotoxy(90,42);
            cout << "                 	        ";
            gotoxy(17,0 + 42); // đưa con trỏ về ô MAMH
            HienConTro();
            state = true;
        }

        batphim(s,check);
    } // end while

    AnConTro();
    for (int i = 0; i < 5; i++)
    {
        gotoxy(5,40+i);
        cout << "                                                                                                                        ";
    }
}
// từ trên tới đây
void ThemMonHoc(NodeMon* &root, int page)//ĐÃ SỬA
{
    ChangeColor(15);
    int total = countMon(root);
    if (total == MAXMONHOC)
    {
        gotoxy(130,26);
        string tb = "Khong the them mon hoc, danh sach mon hoc da day";
        InTB(tb,132,30);
        AnConTro();
        Sleep(750);
        XoaTB(130,26);
    }
    else
    {
        NhapMonHoc(root, page);
    }
}
// TỪ TRÊN TỚI ĐÂY

bool CheckDaThi (string mamon, DSLOP dsl)
{
	for(int i = 0; i < dsl.SLLOP; i++)
	{
		for(NODESV *k = dsl.DS_LOP[i]->ds_SV.pHead; k != NULL ; k=k->pNext)
		{
			for(NODEDIEMTHI *p = k->ds_Diem.pHead; p != NULL; p=p->pNext)
			{
				if(p->MAMH.compare(mamon) == 0)
				{
					return true;// co thi roi
				}
			}
		}
	}
	return false;
}

//đã xóa hàm bool CheckCHdathi ở đây

bool CheckCH_mon(DSCH dsch, string mamon) //đã sửa, hàm này áp dụng cho hàm xóa môn học, mh chỉ xóa được nếu k còn câu hỏi nào thuộc mh đó
{
    CauHoiNode p = dsch.pHead;
    while (p != NULL)
    {
        if (p->MAMH == mamon)
            return false; // tìm thấy câu hỏi thuộc môn đó
        p = p->pNext;
    }
    return true; // không có câu hỏi nào thuộc môn này
}

void NhapMonXoa(NodeMon* &root,int &page, DSLOP dsl, DSCH &dsch)  //cần sửa 
{
	string tb;
	int maxpage;
	InDSMon(root,page);
	string mamon;
	char s;
	int state = 0;
	bool check;
	gotoxy(7,6);
	cout << muiten;
	batphim(s,check);
	while (s != ESC)
	{
		if( <= 10)	maxpage = 0;
		else if( % 10 == 0)	maxpage = /10 -1;
		else maxpage = /10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSMon(root,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				if((state + page*10 + 1) < )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					page++;
					InDSMon(root,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if((state + page*10 + 1) < )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if((state + page*10 + 1) >= ) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if (s == ENTER)
		{
			//neu mon da co thi, khong duoc xoa
			int idx = 0;
NodeMon* mon = getMonTheoThuTu(root, idx, state + page * 10); // da sua
if (mon != NULL && CheckDaThi(mon->MAMH, dsl) == true)
			{
				tb = "Mon hoc da thi, khong the xoa!";
				InTB(tb,132,30);
				Sleep(750);
				XoaTB(132,30);
			}
			//mon chua thi nhung co cau hoi trong dsch
			else {
    int idx = 0;
    NodeMon* mon = getMonTheoThuTu(root, idx, state + page * 10);// da sua
    if (mon != NULL && CheckCH_mon(dsch.pHead, mon->MAMH) == false) {
        
			{
				tb = "Mon hoc da co cau hoi,ban co chac chan muon xoa mon nay ? (Y/N)";
				InTB(tb,132,30);
				batphim(s,check);
				XoaTB(130,26);
				while(s != ESC)
				{
					AnConTro();
					if((s == 'y' || s == 'Y')&& check == true)
					{
						     // Xóa tất cả câu hỏi thuộc môn
                        CauHoiNode prev = NULL, curr = dsch.pHead;//đã bỏ 
                        while (curr != NULL)
                        {
                            if (curr->MAMH == mamon)
                            {
                                if (prev == NULL)
                                    dsch.pHead = curr->pNext;
                                else
                                    prev->pNext = curr->pNext;
                                CauHoiNode tmp = curr;
                                curr = curr->pNext;
                                delete tmp;
                                dsch.SLCH--;
                            }
                            else
                            {
                                prev = curr;
                                curr = curr->pNext;
                            }
                        }
                        // Xóa môn trong cây AVL
                        root = XoaMonAVL(root, mamon);

                        tb = "Da xoa mon hoc va cac cau hoi lien quan!";
                        InTB(tb, 132, 30);
                        Sleep(900);
                        XoaTB(130, 26);
                    }
                    else
                    {
                        XoaTB(130, 26);

						break;
					}
					batphim(s,check);
				}
			}
			else
			{
				tb = "Ban co chac chan muon xoa mon nay ? (Y/N)";
				InTB(tb,132,30);
				batphim(s,check);
				while(s != ESC)
				{
					AnConTro();
					if((s == 'y' || s == 'Y')&& check == true)
					{
					 root = XoaMonAVL(root, mamon);
                        tb = "Xoa mon hoc thanh cong!";   // đã sửa 
                        InTB(tb, 132, 30);
                        Sleep(900);
                        XoaTB(130, 26);
						break;
					}
					else if((s == 'n' || s == 'N') && check == true)
					{
						XoaTB(130,26);
						break;
					}
					batphim(s,check);
				}
			}
			for(int i = 0; i < 28;i++)
			{
				gotoxy(6,6+i);
				cout << "                                                          ";
				gotoxy(66,6+i);
				cout << "                                                          ";
			}	
			page = 0;
			int hd = wherex();
			int td = wherey();
			InDSMon(root,page);
			state = 0;
			gotoxy(7,6);
			cout << muiten;	
		}
		batphim(s,check);
	}
	for(int i = 0; i < 10; i++)
	{
		gotoxy(7,6+i*3);
		cout << " ";
	}
}

void XoaMonHoc (NodeMon* &root, DSLOP dsl, DSCH &dsch)// cần sửa
{
	string tb;
	int page = 0;
	if( == 0)
	{
		tb = "Danh sach mon hien tai dang trong";
		InTB(tb,132,30);
		AnConTro();
		Sleep(750);
		XoaTB(130,26);
	}
	else
	{
		NhapMonXoa(root,page,dsl,dsch);
	}
}
NodeMon* getMonTheoThuTu(NodeMon* root, int targetIndex, int &currentIndex) {
    if (!root) return nullptr;
    NodeMon* left = getMonTheoThuTu(root->pLeft, targetIndex, currentIndex);
    if (left) return left;
    if (currentIndex == targetIndex) return root;
    currentIndex++;
    return getMonTheoThuTu(root->pRight, targetIndex, currentIndex);
}

void SuaMon(NodeMon* &root, int state, int page)// cần sửa
{
	gotoxy(5,40);
	veKhung(5,120);
	gotoxy(7,42);
	cout << "Ma mon :";
	gotoxy(15,41);
	veKhung(3,30);
	gotoxy(80,42);
	cout << "Ten mon :";
	gotoxy(88,41);
	veKhung(3,35);
	bool sState = true;
	char s;
	bool check;
	 int target = state + page * 10;
    int current = 0;
    MonHoc* p = getMonTheoThuTu(root, target, current);
    if (!p) return;

    string mamon = p->MAMH;
    string tenmon = p->TENMH;

	gotoxy(17,42);
	cout << mamon;
	gotoxy(90,42);
	cout << tenmon;
	gotoxy(17+mamon.length(),42);
	HienConTro();
	batphim(s,check);
	while(1)
	{
		if(s == ESC)
		{
			if(Exit(s,check) == true)
			{
				break;
			}
			else
			{
				if (sState == true)
				{
					gotoxy(17+mamon.length(),42);
				}
				else gotoxy(90+tenmon.length(),42);
				HienConTro();
				batphim(s,check);
			}
		}
		if (s == LEFT && check == false)
		{
			if (sState == false)
			{
				gotoxy(17+mamon.length(),42);
				sState = true;
			}
		}
		if (s == RIGHT && check == false)
		{
			if (sState == true)
			{
				gotoxy(90+tenmon.length(),42);
				sState = false;
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && check == true)
		{
			HienConTro();
			if (sState == true)
			{
				if (mamon.length() < 10)
				{
					cout << inhoa(s);
					mamon += inhoa(s);
				}
			}
			else
			{
				if (tenmon.length() < 30)
				{
					cout << inhoa(s);
					tenmon += inhoa(s);
				}
			}
		}
		if(s == ' ')
		{
			if(sState == false)
				{
					if(tenmon.length() == 0)
					{
						gotoxy(90+tenmon.length()-1,42);
					}
					if(tenmon[tenmon.length()-1] != ' ')
					{
						cout << inhoa(s);
						tenmon += inhoa(s);	
					}
				}
		}
		if (s == BACKSPACE)
		{
			if (sState == false)
			{
				if (tenmon.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					tenmon.erase(tenmon.length()-1);
				}
			}
			else
			{
				if (mamon.length() > 0)
				{
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					mamon.erase(mamon.length()-1);
				}
			}
		}
		if(s == ENTER)
		{
			if(mamon.length() == 0 || tenmon.length() == 0)
			{
				string tb = "Vui long nhap day du thong tin";
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);
			}
			else if (CheckMonNhap(root, mamon, tenmon) == false)
			{
				string tb = "Ma mon hoac ten mon bi trung!";
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);
			}
			else
			{
				ChuanHoaTen(tenmon);
				TreeMH root[state+page*10].TENMH= tenmon;
				TreeMH root[state+page*10].MAMH = mamon;
				break;
			}
		}
		batphim(s,check);
	}
	AnConTro();
	for(int i = 0; i < 5; i++)
	{
		gotoxy(5,40+i);
		cout << "                                                                                                                        ";
	}
}

void NhapMonChinh(TreeMH &root , int &page, DSCH dsch, DSLOP dsl)
{
	int maxpage;
	InDSMon(root,page);
	char s;
	int state = 0;
	bool check;
	gotoxy(7,6);
	cout << muiten;
	batphim(s,check);
	while (s != ESC)
	{
		if( <= 10)	maxpage = 0;
		else if( % 10 == 0)	maxpage = /10 -1;
		else maxpage = /10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if((state > 0) )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSMon(root,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				if((state + page*10 + 1) < )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					page++;
					InDSMon(root,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if((state + page*10 + 1) < )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if((state + page*10 + 1) >= ) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if (s == ENTER)
		{
			string tb;
			int idx = 0;
NodeMon* mon = getMonTheoThuTu(root, idx, state + page * 10);
if (mon != NULL && CheckDaThi(mon->MAMH, dsl) == true)  // đã sửa dsm
{
    tb = "Mon hoc da thi, khong the xoa!";
    InTB(tb,132,30);
    Sleep(750);
    XoaTB(132,30);
}

			{
				tb = "Mon hoc da co thi, khong the sua!";
				InTB(tb,132,30);
				Sleep(750);
				XoaTB(130,26);
				gotoxy(7,6+(state*3));
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			//mon chua thi nhung co cau hoi trong dsch
			else {
    int idx = 0;
    NodeMon* mon = getMonTheoThuTu(root, idx, state + page * 10);   //đã sửa 
    if (mon != NULL && CheckCH_mon(dsch.pHead, mon->MAMH) == false) {
    }
}

			{
				tb = "Mon hoc da co cau hoi,khong the sua!";
				InTB(tb,132,30);
				Sleep(750);
				XoaTB(130,26);
				gotoxy(7,6+(state*3));
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			else
			{
				SuaMon(root,state,page);
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				page = 0;
				int hd = wherex();
				int td = wherey();
				InDSMon(root,page);
				gotoxy(hd,td);
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			
		}
		batphim(s,check);
	}
	for(int i = 0; i < 10; i++)
	{
		gotoxy(7,6+i*3);
		cout << " ";
	}
}
// ====================== STACK TỰ CÀI ĐẶT ======================     // mới thêm 31/10
const int STACKSIZE = 1000;

struct StackItem {
    NodeMon* diachi;
    int kieu; // 0 = cha, 1 = con phải
};

struct StackMon {
    StackItem data[STACKSIZE];
    int top;
};

void initStack(StackMon &S) { S.top = -1; }
bool isEmpty(const StackMon &S) { return S.top == -1; }
bool isFull(const StackMon &S) { return S.top == STACKSIZE - 1; }

bool push(StackMon &S, NodeMon* node, int kieu) {
    if (isFull(S)) return false;
    S.data[++S.top].diachi = node;
    S.data[S.top].kieu = kieu;
    return true;
}

bool pop(StackMon &S, NodeMon* &node, int &kieu) {
    if (isEmpty(S)) return false;
    node = S.data[S.top].diachi;
    kieu = S.data[S.top--].kieu;
    return true;
}

// xử lý cây avl       hok có được xóa mấy cái chú thích nha 
//======================= CÁC HÀM TIỆN ÍCH AVL =======================      // đã sửa 31/10
int heightMH(NodeMon* n) {
    return n ? n->height : 0;
}

int max_int(int a, int b) {
    return (a > b) ? a : b;
}

NodeMon* rightRotate(NodeMon* y) {
    NodeMon* x = y->pLeft;
    NodeMon* T2 = x->pRight;

    x->pRight = y;
    y->pLeft = T2;

    y->height = max_int(heightMH(y->pLeft), heightMH(y->pRight)) + 1;
    x->height = max_int(heightMH(x->pLeft), heightMH(x->pRight)) + 1;

    return x;
}

NodeMon* leftRotate(NodeMon* x) {
    NodeMon* y = x->pRight;
    NodeMon* T2 = y->pLeft;

    y->pLeft = x;
    x->pRight = T2;

    x->height = max_int(heightMH(x->pLeft), heightMH(x->pRight)) + 1;
    y->height = max_int(heightMH(y->pLeft), heightMH(y->pRight)) + 1;

    return y;
}

int getBalance(NodeMon* n) {
    return n ? heightMH(n->pLeft) - heightMH(n->pRight) : 0;
}

int cmpMamh(const string &a, const string &b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

//======================= CHÈN NODE (AVL) =======================
NodeMon* InsertMon(NodeMon* node, const string &mamh, const string &tenmh) {
    if (!node) {
        NodeMon* p = new NodeMon(mamh, tenmh);
        p->ds_cauhoi = new DSCH();
        return p;
    }

    int cmp = cmpMamh(mamh, node->MAMH);
    if (cmp < 0)
        node->pLeft = InsertMon(node->pLeft, mamh, tenmh);
    else if (cmp > 0)
        node->pRight = InsertMon(node->pRight, mamh, tenmh);
    else {
        node->TENMH = tenmh;
        return node;
    }

    node->height = 1 + max_int(heightMH(node->pLeft), heightMH(node->pRight));
    int balance = getBalance(node);

    // Cân bằng
    if (balance > 1 && cmpMamh(mamh, node->pLeft->MAMH) < 0)
        return rightRotate(node);

    if (balance < -1 && cmpMamh(mamh, node->pRight->MAMH) > 0)
        return leftRotate(node);

    if (balance > 1 && cmpMamh(mamh, node->pLeft->MAMH) > 0) {
        node->pLeft = leftRotate(node->pLeft);
        return rightRotate(node);
    }

    if (balance < -1 && cmpMamh(mamh, node->pRight->MAMH) < 0) {
        node->pRight = rightRotate(node->pRight);
        return leftRotate(node);
    }

    return node;
}

//======================= HỖ TRỢ XÓA =======================
NodeMon* minValueNode(NodeMon* node) {
    NodeMon* cur = node;
    while (cur->pLeft)
        cur = cur->pLeft;
    return cur;
}

//======================= XÓA NODE (AVL) =======================
NodeMon* deleteMon(NodeMon* root, const string &mamh) {
    if (!root) return root;

    int cmp = cmpMamh(mamh, root->MAMH);

    if (cmp < 0)
        root->pLeft = deleteMon(root->pLeft, mamh);
    else if (cmp > 0)
        root->pRight = deleteMon(root->pRight, mamh);
    else {
        if (!root->pLeft || !root->pRight) {
            NodeMon* temp = root->pLeft ? root->pLeft : root->pRight;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            if (temp) {
                if (temp->ds_cauhoi) {
                    delete temp->ds_cauhoi;
                    temp->ds_cauhoi = nullptr;
                }
                delete temp;
            }
        } else {
            NodeMon* temp = minValueNode(root->pRight);
            root->MAMH = temp->MAMH;
            root->TENMH = temp->TENMH;

            DSCH* tmpDS = root->ds_cauhoi;
            root->ds_cauhoi = temp->ds_cauhoi;
            temp->ds_cauhoi = tmpDS;

            root->pRight = deleteMon(root->pRight, temp->MAMH);
        }
    }

    if (!root) return root;

    root->height = 1 + max_int(heightMH(root->pLeft), heightMH(root->pRight));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->pLeft) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->pLeft) < 0) {
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->pRight) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->pRight) > 0) {
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }

    return root;
}

//======================= TÌM KIẾM NODE =======================
NodeMon* searchMon(NodeMon* root, const string &mamh) {
    if (!root) return nullptr;
    int cmp = cmpMamh(mamh, root->MAMH);
    if (cmp == 0) return root;
    if (cmp < 0) return searchMon(root->pLeft, mamh);
    return searchMon(root->pRight, mamh);
}

//======================= DUYỆT CÂY PHI ĐỆ QUY =======================

//--- TIỀN TỰ (NLR) trái- gốc-phải khóa mh tăng dần 
void PretravMon(NodeMon* root) {       
    const int STACKSIZE = 1000;
    NodeMon* Stack[STACKSIZE];
    int sp = 0;
    NodeMon* p = root;

    while (true) {
        while (p != NULL) {
            cout << p->MAMH << " - " << p->TENMH << endl;   //in ds dc sx
            Stack[++sp] = p->pRight;
            p = p->pLeft;
        }
        if (sp == 0) break;
        p = Stack[sp--];
    }
}

//--- TRUNG TỰ (LNR) gốc- trái-phải sao chép cây lưu file
void IntravMon(NodeMon* root) {
    const int STACKSIZE = 1000;
    NodeMon* Stack[STACKSIZE];
    int sp = 0;
    NodeMon* p = root;

    while (true) {
        while (p != NULL) {
            Stack[++sp] = p;
            p = p->pLeft;
        }
        if (sp == 0) break;

        p = Stack[sp--];
        cout << p->MAMH << " - " << p->TENMH << endl;
        p = p->pRight;
    }
}

//--- HẬU TỰ (LRN) - trái phải gốc , duyệt cha trước con nên dùng để xóa cây 
void PostravMon(NodeMon* root) {
    const int STACKSIZE = 1000;
    struct phantu {
        NodeMon* diachi;
        int kieu; // TRUE: nút con phải, FALSE: nút cha
    };

    phantu Stack[STACKSIZE];
    int typ, sp;
    NodeMon* p = root;
    sp = 0;
    typ = TRUE;
    Stack[0].diachi = NULL;

    do {
        while (p != NULL && typ) {
            Stack[++sp].diachi = p;
            Stack[sp].kieu = FALSE;
            if (p->pRight != NULL) {
                Stack[++sp].diachi = p->pRight;
                Stack[sp].kieu = TRUE;
            }
            p = p->pLeft;
        }
        if (p != NULL) {
            cout << p->MAMH << " - " << p->TENMH << endl;
        }
        p = Stack[sp].diachi;
        typ = Stack[sp--].kieu;
    } while (p != NULL);
}
// TỪ TRÊN TỚI ĐÂY
void ChinhMon(TreeMH &root, int &page, DSCH dsch, DSLOP dsl)
{
	int n = countMon(root);
	if(n  == 0)
	{
		string tb = "Danh sach mon hien tai dang trong";
		InTB(tb,132,30);
		AnConTro();
		Sleep(750);
		XoaTB(130,26);
	}
	else
	{
		NhapMonChinh(root, page, dsch, dsl);
	}
}

// ==================== QUẢN LÝ MÔN HỌC ====================

void FunctionMon(TreeMH &root, DSLOP &dsl, DSCH &dsch)
{
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat		PGUP: Lui trang		PGDOWN: Qua trang	UP: Len	DOWN: Xuong";
	gotoxy(130,26);
	vekhungTB(10,36);

	int page = 0;
	char s;
	bool check;
	int state = 0;
	int total = countMon(root);

	vekhungDS(34,120,2);
	veNut(3,15,150,10,"Them mon",240);
	veNut(3,15,150,15,"Xoa mon",20);
	veNut(3,15,150,20,"Sua mon",20);

	gotoxy(30,3);  cout << "MA MON HOC";
	gotoxy(90,3);  cout << "TEN MON HOC";

	// In danh sách ban đầu
	if (root != NULL)
		InDSMon(root, page);

	int maxpage;
	batphim(s, check);

	while (s != ESC)
	{
		total = countMon(root);
		if (total <= 10) maxpage = 0;
		else if (total % 10 == 0) maxpage = total / 10 - 1;
		else maxpage = total / 10;

		// --------------------- DI CHUYỂN PHÍM LÊN XUỐNG ---------------------
		if (s == UP && check == false)
		{
			switch (state)
			{
				case 1:
					state = 0;
					veNut(3,15,150,15,"Xoa mon",20);
					veNut(3,15,150,10,"Them mon",240);
					break;
				case 2:
					state = 1;
					veNut(3,15,150,20,"Sua mon",20);
					veNut(3,15,150,15,"Xoa mon",240);
					break;
				default: break;
			}
		}

		if (s == DOWN && check == false)
		{
			switch (state)
			{
				case 0:
					state = 1;
					veNut(3,15,150,10,"Them mon",20);
					veNut(3,15,150,15,"Xoa mon",240);
					break;
				case 1:
					state = 2;
					veNut(3,15,150,15,"Xoa mon",20);
					veNut(3,15,150,20,"Sua mon",240);
					break;
				default: break;
			}
		}

		// --------------------- LẬT TRANG DANH SÁCH ---------------------
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if (page < maxpage)
			{
				XoaNoiDungDS();
				page++;
				InDSMon(root, page);
			}
		}
		if (s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0)
			{
				XoaNoiDungDS();
				page--;
				InDSMon(root, page);
			}
		}

		// --------------------- NHẤN ENTER THỰC HIỆN CHỨC NĂNG ---------------------
		if (s == ENTER)
		{
			switch (state)
			{
				case 0:
					ThemMonHoc(root, page);
					break;
				case 1:
					XoaMonHoc(root, dsl, dsch);
					break;
				case 2:
					ChinhMon(root, page, dsch, dsl);
					break;
			}
			XoaNoiDungDS();
			InDSMon(root, page);
			AnConTro();
		}

		batphim(s, check);
	}
}

//đã xóa TaoMangRD(). Random(), RandomMang() ở đây



void Them1CauHoi(DSCH &dsch, DanhSachID &dsID, CauHoi *a) //đã sửa
{
    // Gán ID ngẫu nhiên
    a->ID = LayIDKeTiep(dsID);
    a->daThi = false;
    a->pNext = NULL;

    // Nếu danh sách rỗng
    if (dsch.pHead == NULL)
    {
        dsch.pHead = dsch.pLast = a;
    }
    else
    {
        dsch.pLast->pNext = a;
        dsch.pLast = a;
    }

    dsch.SLCH++;

    // Cập nhật file ID sau khi dùng
    LuuDanhSachID(dsID, "IDLIST.txt");
}

void In1CauHoi(CauHoi* ch, int k)//đã sửa
{
    if (ch == NULL) return;

    gotoxy(16, 4 + k);
    cout << ch->ID;

    gotoxy(40, 4 + k);
    cout << ch->MAMH;

    gotoxy(55, 4 + k);
    if (ch->NOIDUNG.length() < 63)
        cout << ch->NOIDUNG;
    else
        cout << ch->NOIDUNG.substr(0, 63) << "...";
}


void InDSCH(DSCH dsch, int page, int arr[])//đã sửa
{
    int k = 2;
    int sl = dsch.SLCH;
    int maxpage = (sl <= 10) ? 0 : ((sl % 10 == 0) ? sl / 10 - 1 : sl / 10);

    int start = page * 10;
    int end = min((page + 1) * 10, sl);

    for (int i = start; i < end; i++)
    {
        CauHoiNode temp = TimKiemCauHoi(dsch, arr[i]);
        if (temp != NULL)
        {
            In1CauHoi(temp, k);
            k += 3;
        }
    }

    gotoxy(125 / 2, 36);
    cout << "Trang " << page + 1 << "/" << maxpage + 1;
}

// ==================== XEM CAU HOI ==========================
void XemCH(DSCH &dsch, int &page, int arr[]) //đã sửa
{
    string tb;
    int maxpage = (dsch.SLCH <= 10) ? 0 : ((dsch.SLCH % 10 == 0) ? dsch.SLCH / 10 - 1 : dsch.SLCH / 10);

    InDSCH(dsch, page, arr);
    char s;
    int state = 0;
    bool check;
    gotoxy(7, 6);
    cout << muiten;
    batphim(s, check);

    while (s != ESC)
    {
        if (dsch.SLCH == 0)
        {
            tb = "Danh sach cau hoi hien tai dang trong";
            InTB(tb, 132, 30);
            AnConTro();
            Sleep(750);
            XoaTB(130, 26);
            break;
        }

        // Xử lý phím di chuyển (UP, DOWN, PAGEUP, PAGEDOWN) như code cũ của bạn
        // --> chỉ giữ nguyên, không cần đổi gì.

        if (s == ENTER)
        {
            system("cls");
            int i = state + page * 10;

            CauHoiNode ch = TimKiemCauHoi(dsch, arr[i]);
            if (ch != NULL)
            {
                // Vẽ giao diện xem chi tiết
                gotoxy(132, 2);
                veKhung(9, 33);
                gotoxy(135, 4); cout << "MA MON HOC: " << ch->MAMH;
                gotoxy(135, 7); cout << "ID CAU HOI: " << ch->ID;

                gotoxy(5, 2);
                veKhung(36, 125);
                gotoxy(6, 5); cout << "NOI DUNG CH: ";
                gotoxy(6, 8); cout << "DAP AN A: " << ch->A;
                gotoxy(6, 11); cout << "DAP AN B: " << ch->B;
                gotoxy(6, 14); cout << "DAP AN C: " << ch->C;
                gotoxy(6, 17); cout << "DAP AN D: " << ch->D;
                gotoxy(6, 20); cout << "DAP AN DUNG: " << ch->DA;
            }
            else
            {
                tb = "Khong tim thay cau hoi!";
                InTB(tb, 132, 30);
                Sleep(1000);
                XoaTB(130, 26);
            }

            batphim(s, check);
            system("cls");
            gotoxy(50, 46);
            cout << "ENTER: Chon	ESC: Thoat   PGUP: Qua trang	PGDOWN: Lui trang    UP: Len	DOWN: Xuong";
            gotoxy(130, 26);
            vekhungTB(10, 36);
            veNut(3, 15, 150, 5, "Them CH", 20);
            veNut(3, 15, 150, 10, "Xoa CH", 20);
            veNut(3, 15, 150, 15, "Xem CH", 240);
            veNut(3, 15, 150, 20, "Xem CH theo mon", 20);
            gotoxy(5, 2);
            vekhungDSCH(34, 120, 5);
            InDSCH(dsch, page, arr);
            gotoxy(7, 6);
            cout << muiten;
            state = 0;
        }

        batphim(s, check);
    }

    for (int i = 0; i < 10; i++)
    {
        gotoxy(7, 6 + i * 3);
        cout << " ";
    }
}

// ==================== XEM CAU HOI ==========================
void XemCauHoi(DSCH &dsch, int arr[]) //đã sửa
{
    string tb;
    int page = 0;
    if (dsch.SLCH == 0)
    {
        tb = "Danh sach cau hoi hien tai dang trong";
        InTB(tb, 132, 30);
        AnConTro();
        Sleep(750);
        XoaTB(130, 26);
    }
    else
    {
        XemCH(dsch, page, arr);
    }
}



MONHOC NhapMaMHThem (TreeMH root)
{
	system("cls");
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat	PGUP: Qua trang		PGDOWN: Lui trang	   UP: Len 	   DOWN: Xuong";
	gotoxy(5,2);
	vekhungDS(34,120,2);
	gotoxy(30,3);
	cout << "MA MON HOC";
	gotoxy(90,3);
	cout << "TEN MON HOC";
	string tb;
	int page = 0;
	int maxpage;
	InDSMon(root,page);
	char s;
	int state = 0;
	bool check;
	gotoxy(7,6);
	cout << muiten;
	batphim(s,check);
	while (s != ESC)
	{
		if( <= 10)	maxpage = 0;	
		else if( % 10 == 0) maxpage = /10 -1;
		else maxpage = /10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSMon(root,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				if((state + page*10 + 1) < )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					page++;
					InDSMon(root,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if((state + page*10 + 1) < )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if((state + page*10 + 1) >= ) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if (s == ENTER)
		{
			// chon ma mon, in menu nhap cau hoi them
			return getMonTheoThuTu(root, state + page*10);// da sua
		}
		batphim(s,check);
	}
	 NodeMon *mh;
	mh.MAMH = "";
	mh.TENMH = "";
	return mh;
}	

void NhapCHThem(DSCH &dsch, NodeMon *mh, DanhSachID &dsID)//đã sửa
{
	gotoxy(5+(125 - mh->TENMH.length())/2,1);
	cout << mh->TENMH;
	vekhungThemCH();
	gotoxy(130,26);
	vekhungTB(10,36);
	CauHoi *ch = KhoiTaoCauHoi();
	int state = 0;
	int n;
	int dem;
	string nd;
	string a;
	string b;
	string c;
	string d;
	string temp;
	char s;
	bool check;
	gotoxy(20,5);
	int hdnd,tdnd,hda,tda,hdb,tdb,hdc,tdc,hdd,tdd;
	hdnd = 20;
	tdnd = 5;
	hda = 20;
	tda = 14;
	hdb = 20;
	tdb = 20;
	hdc = 20;
	tdc = 26;
	hdd = 20;
	tdd = 32;
	HienConTro();
	batphim(s,check);
	while(1)
	{
		if(s == ESC)
		{
			if(Exit(s,check) == true)
			{
				break;
			}
			else
			{
				switch(state)
				{
					case 0:
						{
							HienConTro();
							gotoxy(hdnd,tdnd);
							break;
						}
					case 1:
						{
							HienConTro();
							gotoxy(hda,tda);
							break;
						}
					case 2:
						{
							HienConTro();
							gotoxy(hdb,tdb);
							break;
						}
					case 3:
						{
							HienConTro();
							gotoxy(hdc,tdc);
							break;
						}
					case 4:
						{
							HienConTro();
							gotoxy(hdd,tdd);
							break;
						}
					case 5:
						{
							veNut(3,11,59,38,"LUU",30);
							HienConTro();
							gotoxy(hdd,tdd);
							state = 4;
							break;	
						}	
				}
				HienConTro();
				batphim(s,check);
			}
		}
		if(s == UP && check == false)
		{
			if(state > 0)
			{
				switch(state)
				{
					case 1:
						{
							HienConTro();
							gotoxy(hdnd,tdnd);
							state--;
							break;
						}
					case 2:
						{
							HienConTro();
							gotoxy(hda,tda);
							state--;
							break;
						}
					case 3:
						{
							HienConTro();
							gotoxy(hdb,tdb);
							state--;
							break;
						}
					case 4:
						{
							HienConTro();
							gotoxy(hdc,tdc);
							state--;
							break;
						}
					case 5:
						{
							veNut(3,11,59,38,"LUU",30);
							HienConTro();
							gotoxy(hdd,tdd);
							state--;
							break;
						}	
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state < 5)
			{
				switch(state)
				{
					case 0:
						{
							HienConTro();
							gotoxy(hda,tda);
							state ++;
							break;
						}
					case 1:
						{
							HienConTro();
							gotoxy(hdb,tdb);
							state ++;
							break;
						}
					case 2:
						{
							HienConTro();
							gotoxy(hdc,tdc);
							state ++;
							break;
						}
					case 3:
						{
							HienConTro();
							gotoxy(hdd,tdd);
							state ++;
							break;
						}
					case 4:
						{
							AnConTro();
							veNut(3,11,59,38,"LUU",240);
							state ++;
							break;
						}	
				}
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9') || (s == '?') || (s == ',') || (s == '.') ||(s == '(') || (s == ')'))  && check == true)
		{
			HienConTro();
			switch(state)
			{
				case 0:
					{
						if(nd.length() < MAXNOIDUNG)
						{
							if(wherex() == 115 && wherey() == 5 )
							{
								n = nd.length()-1;
								temp = "";
								if(nd[n] == ' ')
								{
									gotoxy(20,7);
									cout << inhoa(s);
									nd += inhoa(s);
								}
								else
								{
									while(nd[n] != ' ')
									{
										temp += nd[n];
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(wherex()-1,wherey());
										n--;
										dem = n;
									}
									dem++;
									temp = DaoChuoi(temp);
									gotoxy(20,7);
									cout << temp;
									cout << inhoa(s);
									nd += inhoa(s);
								}
							}
							else if (wherex() == 115 && wherey() == 7)
							{
								n = nd.length()-1;
								temp = "";
								if(nd[n] == ' ')
								{
									gotoxy(20,9);
									cout << inhoa(s);
									nd += inhoa(s);
								}
								else
								{
									while(nd[n] != ' ')
									{
										temp += nd[n];
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(wherex()-1,wherey());
										n--;
									}
									temp = DaoChuoi(temp);
									gotoxy(20,9);
									cout << temp;
									cout << inhoa(s);
									nd += inhoa(s);
								}
							}
							else
							{
								cout << inhoa(s);
								nd += inhoa(s);
							}
						}
						hdnd = wherex();
						tdnd = wherey();
						break;
					}
				case 1:	
					{
						if(a.length() < MAXA)
						{
							if(wherex() == 115)
							{
								n = a.length()-1;
								temp = "";
								if(a[n] == ' ')
								{
									gotoxy(20,16);
									cout << inhoa(s);
									a += inhoa(s);
								}
								else
								{
									while(a[n] != ' ')
									{
										temp += a[n];
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(wherex()-1,wherey());
										n--;
									}
									temp = DaoChuoi(temp);
									gotoxy(20,16);
									cout << temp;
									cout << inhoa(s);
									a += inhoa(s);
								}
							}
							else
							{
								cout << inhoa(s);
								a += inhoa(s);
							}
						}
						hda = wherex();
						tda = wherey();
						break;
					}
				case 2:
					{
						if(b.length() < MAXB)
						{
							if(wherex() == 115)
							{
								n = b.length()-1;
								temp = "";
								if(b[n] == ' ')
								{
									gotoxy(20,22);
									cout << inhoa(s);
									b += inhoa(s);
								}
								else
								{
									while(b[n] != ' ')
									{
										temp += b[n];
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(wherex()-1,wherey());
										n--;
									}
									temp = DaoChuoi(temp);
									gotoxy(20,22);
									cout << temp;
									cout << inhoa(s);
									b += inhoa(s);
								}
							}
							else
							{
								cout << inhoa(s);
								b += inhoa(s);
							}	
						}
						hdb = wherex();
						tdb = wherey();
						break;
					}
				case 3:
					{
						if(c.length() < MAXC)
						{
							if(wherex() == 115)
							{
								n = c.length()-1;
								temp = "";
								if(c[n] == ' ')
								{
									gotoxy(20,28);
									cout << inhoa(s);
									c += inhoa(s);
								}
								else
								{
									while(c[n] != ' ')
									{
										temp += c[n];
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(wherex()-1,wherey());
										n--;
									}
									temp = DaoChuoi(temp);
									gotoxy(20,28);
									cout << temp;
									cout << inhoa(s);
									c += inhoa(s);
								}
							}
							else
							{
								cout << inhoa(s);
								c += inhoa(s);
							}	
						}
						hdc = wherex();
						tdc = wherey();
						break;
					}
				case 4:
					{
						if(d.length() < 180)
						{
							if(wherex() == 115)
							{
								n = d.length()-1;
								temp = "";
								if(d[n] == ' ')
								{
									gotoxy(20,34);
									cout << inhoa(s);
									d += inhoa(s);
								}
								else
								{
									while(d[n] != ' ')
									{
										temp += d[n];
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(wherex()-1,wherey());
										n--;
									}
									temp = DaoChuoi(temp);
									gotoxy(20,34);
									cout << temp;
									cout << inhoa(s);
									d += inhoa(s);
								}
							}
							else
							{
								cout << inhoa(s);
								d += inhoa(s);
							}	
						}
						hdd = wherex();
						tdd = wherey();
						break;
					}
								
			}
		}
		if(s == ' ')
		{
			switch(state)
				{
					case 0:
						{
							if(nd.length() == 0)
							{
								gotoxy(20+nd.length()-1,5);
							}
							if(nd[nd.length()-1]!= ' ')
							{
								cout << inhoa(s);
								nd += inhoa(s);	
							}
							if(wherex() == 115 || wherex() == 116 || wherex() == 117)
							{
								if(wherey() == 5)
								{
									dem = wherex() - 20;
									gotoxy(20,7);
									cout << inhoa(s);
									nd += inhoa(s);
								}
								else if(wherey() == 7)
								{
									gotoxy(20,9);
									cout << inhoa(s);
									nd += inhoa(s);
								}									
							}
							hdnd = wherex();
							tdnd = wherey();
							break;	
						}
					case 1:
						{
							if(a.length() == 0)
							{
								gotoxy(20+a.length()-1,14);
							}
							if(a[a.length()-1]!= ' ')
							{
								cout << inhoa(s);
								a += inhoa(s);	
							}
							if(wherex() == 115 || wherex() == 116 || wherex() == 117)
							{
								gotoxy(20,16);
								cout << inhoa(s);
								a += inhoa(s);
							}
							hda = wherex();
							tda = wherey();
							break;	
						}
					case 2:
						{
							if(b.length() == 0)
							{
								gotoxy(20+b.length()-1,20);
							}
							if(b[b.length()-1]!= ' ')
							{
								cout << inhoa(s);
								b += inhoa(s);	
							}
							if(wherex() == 115 || wherex() == 116 || wherex() == 117)
							{
								gotoxy(20,22);
								cout << inhoa(s);
								b += inhoa(s);
							}
							hdb = wherex();
							tdb = wherey();
							break;	
						}
					case 3:
						{
							if(c.length() == 0)
							{
								gotoxy(20+c.length()-1,26);
							}
							if(c[c.length()-1]!= ' ')
							{
								cout << inhoa(s);
								c += inhoa(s);	
							}
							if(wherex() == 115 || wherex() == 116 || wherex() == 117)
							{
								gotoxy(20,28);
								cout << inhoa(s);
								c += inhoa(s);
							}
							hdc = wherex();
							tdc = wherey();
							break;	
						}
					case 4:
						{
							if(d.length() == 0)
							{
								gotoxy(20+ch->D.length()-1,32);
							}
							if(d[d.length()-1]!= ' ')
							{
								cout << inhoa(s);
								d += inhoa(s);	
							}
							if(wherex() == 115 || wherex() == 116 || wherex() == 117)
							{
								gotoxy(20,34);
								cout << inhoa(s);
								d += inhoa(s);
							}
							hdd = wherex();
							tdd = wherey();
							break;	
						}				
				}
		}
		if (s == BACKSPACE)
		{
			switch(state)
			{
				case 0:
					{
						if (nd.length() > 0)
						{
							if(wherex() == 20 && wherey() == 7)
							{
								gotoxy(20 + nd.length(),5);
								hdnd = wherex();
								tdnd = wherey();
							}
							else if(wherex() == 20 && wherey() == 9)
							{
								gotoxy(20 + nd.length() - dem,7);
								hdnd = wherex();
								tdnd = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								nd.erase(nd.length()-1);
								hdnd = wherex();
								tdnd = wherey();
							}
						}
						break;
					}
				case 1:
					{
						if (a.length() > 0)
						{
							if(wherex() == 20)
							{
								gotoxy(20 + a.length(),14);
								hda = wherex();
								tda = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								a.erase(a.length()-1);
								hda = wherex();
								tda = wherey();
							}
						}
						break;
					}
				case 2:
					{
						if (b.length() > 0)
						{
							if(wherex() == 20)
							{
								gotoxy(20 + b.length(),20);
								hdb = wherex();
								tdb = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								b.erase(b.length()-1);
								hdb = wherex();
								tdb = wherey();
							}
						}
						break;
					}
				case 3:
					{
						if (c.length() > 0)
						{
							if(wherex() == 20)
							{
								gotoxy(20 + c.length(),26);
								hdc = wherex();
								tdc = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								c.erase(c.length()-1);
								hdc = wherex();
								tdc = wherey();
							}
						}
						break;					
					}
				case 4:
					{
						
						if (d.length() > 0)
						{
							if(wherex() == 20)
							{
								gotoxy(20 + d.length(),32);
								hdd = wherex();
								tdd = wherey();
							}
							else
							{
								AnConTro();
								gotoxy(wherex()-1,wherey());
								cout << " ";
								gotoxy(wherex()-1,wherey());
								HienConTro();
								d.erase(d.length()-1);
								hdd = wherex();
								tdd = wherey();
							}
						}
						break;
					}		
			}
		}
		if ( s == ENTER)
		{
			if(state == 5)
			{
				if(nd.length() == 0 || a.length() == 0 || b.length() == 0 || c.length() == 0 || d.length() == 0)
				{
					string tb = "Vui long nhap day du thong tin";
					InTB(tb,132,30);
					AnConTro();
					Sleep(750);
					XoaTB(130,26);
				}
				else
				{
					int state1 = 0;
					string da = "A";
					gotoxy(4,14);
					cout << muiten;
					batphim(s,check);
					while(1)
					{
						if(s == UP && check == false)
						{
							switch(state1)
							{
								case 1:
									{
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(4,14);
										cout << muiten;
										state1--;
										da = "A";
										break;
									}
								case 2:
									{
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(4,20);
										cout << muiten;
										state1--;
										da = "B";
										break;
									}
								case 3:
									{
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(4,26);
										cout << muiten;
										state1--;
										da = "C";
										break;
									}
							}	
						}
						if(s == DOWN && check == false)
						{
							switch(state1)
							{
								case 0:
									{
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(4,20);
										cout << muiten;
										state1++;
										da = "B";
										break;
									}
								case 1:
									{
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(4,26);
										cout << muiten;
										state1++;
										da = "C";
										break;
									}
								case 2:
									{
										gotoxy(wherex()-1,wherey());
										cout << " ";
										gotoxy(4,32);
										cout << muiten;
										state1++;
										da = "D";
										break;
									}
							}
						}
						if(s == ENTER)
						{
							ch->ID = mh->MAMH;
							ch->DA = da;
							ch->NOIDUNG = nd;
							ch->A = a;
							ch->B = b;
							ch->C = c;
							ch->D = d;    
    						Them1CauHoi(dsch, dsID, ch);         
							string tb = "Them cau hoi thanh cong!";
							InTB(tb,132,30);
							AnConTro();
							Sleep(750);
							XoaTB(130,26);
							return;
						}
						batphim(s,check);
					}
					for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}
				}
				for(int i = 0; i < 30;i++)
				{
					gotoxy(20,5+i);
					if(i == 4) i = 8;
					if (i == 11) i = 14;
					if (i == 17) i = 20;
					if (i == 23) i = 26;
					cout << "                                                                                                  ";
				}
				veNut(3,11,59,38,"LUU",30);
				nd = "";
				a = "";
				a = "";
				b = "";
				c = "";
				d = "";
				state = 0;
				gotoxy(20+nd.length(),5);
				HienConTro();
//				break;
			}
		}
		batphim(s,check);
	}
}

// ==================== THEM CAU HOI ==========================
void ThemCH(DSCH &dsch, TreeMH root, DanhSachID &dsID)//đã sửa
{
    ChangeColor(15);
    if (dsch.SLCH == MAXCH) {
        gotoxy(130, 26);
        string tb = "Khong the them cau hoi, danh sach cau hoi da day";
        InTB(tb, 132, 30);
        AnConTro();
        Sleep(750);
        XoaTB(130, 26);
        return;
    }

    NodeMon *mh = NhapMaMHThem(root);
    if (mh == nullptr || mh->MAMH == "" || mh->TENMH == "")
        return;

    NhapCHThem(dsch, mh, dsID);
}



void NhapCauHoiXoa(DSCH &dsch, int &page, int arr[], DSDT dsdt) //đã sửa
{
    string tb;
    int maxpage;
    InDSCH(dsch, page, arr);
    char s;
    int state = 0;
    bool check;

    gotoxy(7,6);
    cout << muiten;
    batphim(s,check);

    while (s != ESC)
    {
        if (dsch.SLCH == 0)
        {
            tb = "Danh sach cau hoi hien tai dang trong";
            InTB(tb,132,30);
            AnConTro();
            Sleep(750);
            XoaTB(130,26);
            break;
        }

        if (dsch.SLCH <= 10) maxpage = 0;
        else if (dsch.SLCH % 10 == 0) maxpage = dsch.SLCH / 10 - 1;
        else maxpage = dsch.SLCH / 10;

        // ==================== PHÍM LÊN ====================
        if (s == UP && !check)
        {
            if (state > 0)
            {
                gotoxy(wherex()-1, wherey()); cout << " ";
                state--;
                gotoxy(7, wherey()-3); cout << muiten;
            }
            else if (page > 0)
            {
                // Xoá trang cũ
                for (int i = 0; i < 28; i++)
                {
                    gotoxy(6,6+i);  cout << "                      ";
                    gotoxy(31,6+i); cout << "                      ";
                    gotoxy(54,6+i); cout << "                                                                    ";
                }
                page--;
                InDSCH(dsch, page, arr);
                gotoxy(7,33); cout << muiten;
                state = 9;
            }
        }

        // ==================== PHÍM XUỐNG ====================
        if (s == DOWN && !check)
        {
            if (state == 9)
            {
                if ((page + 1) * 10 < dsch.SLCH)
                {
                    gotoxy(wherex()-1,wherey()); cout << " ";
                    for (int i = 0; i < 28; i++)
                    {
                        gotoxy(6,6+i);  cout << "                      ";
                        gotoxy(31,6+i); cout << "                      ";
                        gotoxy(54,6+i); cout << "                                                                    ";
                    }
                    page++;
                    InDSCH(dsch,page,arr);
                    state = 0;
                    gotoxy(7,6); cout << muiten;
                }
            }
            else 
            {
                if (state + 1 + page * 10 < dsch.SLCH)
                {
                    gotoxy(wherex()-1,wherey()); cout << " ";
                    state++;
                    gotoxy(7,wherey()+3); cout << muiten;	
                }
            }
        }

        // ==================== PHÍM PAGE DOWN ====================
        if (s == PAGEDOWN && !check)
        {
            AnConTro();
            if (page < maxpage)
            {
                for (int i = 0; i < 28; i++)
                {
                    gotoxy(6,6+i);  cout << "                      ";
                    gotoxy(31,6+i); cout << "                      ";
                    gotoxy(54,6+i); cout << "                                                                    ";
                }
                page++;
                InDSCH(dsch,page,arr);
                state = 0;
                gotoxy(7,6); cout << muiten;
            }
        }

        // ==================== PHÍM PAGE UP ====================
        if (s == PAGEUP && !check)
        {
            AnConTro();
            if (page > 0)
            {
                for (int i = 0; i < 28; i++)
                {
                    gotoxy(6,6+i);  cout << "                      ";
                    gotoxy(31,6+i); cout << "                      ";
                    gotoxy(54,6+i); cout << "                                                                    ";
                }
                page--;
                InDSCH(dsch,page,arr);
                state = 0;
                gotoxy(7,6); cout << muiten;
            }
        }

        // ==================== ENTER: XOÁ CÂU HỎI ====================
        if (s == ENTER)
        {
            int id = arr[state + page * 10];

            tb = "Ban co chac chan muon xoa cau hoi nay ? (Y/N)";
            InTB(tb,132,30);
            batphim(s,check);

            while (s != ESC)
            {
                AnConTro();
                if ((s == 'y' || s == 'Y') && check)
                {
                    RemoveCH(dsch, id);  // Hàm này tự kiểm tra daThi + in TB

                    // cập nhật danh sách ID
                    for (int i = state + page * 10; i < dsch.SLCH; i++)
                        arr[i] = arr[i + 1];

                    if (page > 0 && dsch.SLCH % 10 == 0) page--;

                    if (dsch.SLCH == 0)
                    {
                        tb = "Danh sach cau hoi hien tai dang trong";
                        InTB(tb,132,30);
                        AnConTro();
                        Sleep(750);
                        XoaTB(130,26);
                        return;
                    }

                    // in lại danh sách
                    for (int i = 0; i < 28; i++)
                    {
                        gotoxy(6,6+i);  cout << "                      ";
                        gotoxy(31,6+i); cout << "                      ";
                        gotoxy(54,6+i); cout << "                                                                    ";
                    }
                    InDSCH(dsch, page, arr);
                    state = 0;
                    gotoxy(7,6); cout << muiten;
                    break;
                }
                else if ((s == 'n' || s == 'N') && check)
                {
                    XoaTB(130,26);
                    break;
                }
                batphim(s,check);
            }
        }

        batphim(s,check);
    }

    // Xóa con trỏ mũi tên
    for (int i = 0; i < 10; i++)
    {
        gotoxy(7,6 + i*3);
        cout << " ";
    }
}

// ==================== XOA CÂU HỎI ==========================
void XoaCauHoi(DSCH &dsch, int arr[], DSDT dsdt) //đã sửa
{
    string tb;
    int page = 0;

    if (dsch.SLCH == 0)
    {
        tb = "Danh sach cau hoi hien tai dang trong";
        InTB(tb,132,30);
        AnConTro();
        Sleep(750);
        XoaTB(130,26);
    }
    else
    {
        NhapCauHoiXoa(dsch, page, arr, dsdt);
    }
}

void XemCHTheoMon (NodeMon* root , DSCH dsch)    // đã đổi biến, thêm cây 31/10
{
	system("cls");
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat	PGUP: Qua trang	PGDOWN: Lui trang  UP/DOWN: Len Xuong";
	gotoxy(130,26);
	vekhungTB(10,36);
	int page = 0;
	char s;
	bool check;
	gotoxy(5,2);
	int state = 0;
	vekhungDS(34,120,2);	
	gotoxy(30,3);
	cout << "MA MON HOC";
	gotoxy(90,3);
	cout << "TEN MON HOC";
	if (countMon(root) != 0) InDSMon(root, page);

int maxpage;
gotoxy(7,6);
cout << muiten;
batphim(s, check);

while (s != ESC)
{
    // recompute total và maxpage mỗi vòng (phòng trường hợp dữ liệu thay đổi)
    int totalMon = countMon(root);
    if (totalMon <= 10) maxpage = 0;
    else if (totalMon % 10 == 0) maxpage = totalMon / 10 - 1;
    else maxpage = totalMon / 10;

    if (s == UP && check == false)
    {
        if (page == 0)
        {
            if (state > 0)
            {
                gotoxy(wherex()-1,wherey());
                cout << " ";
                state--;
                gotoxy(7,wherey() - 3);
                cout << muiten;
            }
        }
        if (page > 0)
        {
            if (state > 0)
            {
                gotoxy(wherex()-1,wherey());
                cout << " ";
                state--;
                gotoxy(7,wherey()-3);
                cout << muiten;
            }
            else if (state == 0)
            {
                for(int i = 0; i < 28; i++)
                {
                    gotoxy(6,6+i);
                    cout << "                                                          ";
                    gotoxy(66,6+i);
                    cout << "                                                          ";
                }
                gotoxy(wherex()-1,wherey());
                cout << " ";
                page--;
                InDSMon(root, page);           // dùng cây (root)
                gotoxy(7,33);
                cout << muiten;
                state = 9;
            }
        }
    }

    if (s == DOWN && check == false)
    {
        if (state == 9)
        {
            if ((state + page*10 + 1) < totalMon)
            {
                gotoxy(wherex()-1,wherey());
                cout << " ";
                for(int i = 0; i < 28;i++)
                {
                    gotoxy(6,6+i);
                    cout << "                                                          ";
                    gotoxy(66,6+i);
                    cout << "                                                          ";
                }
                page++;
                InDSMon(root, page);
                state = 0;
                gotoxy(7,6);
                cout << muiten;
            }
        }
        else
        {
            if ((state + page*10 + 1) < totalMon)
            {
                gotoxy(wherex()-1,wherey());
                cout << " ";
                state++;
                gotoxy(7,wherey() + 3);
                cout << muiten;    
            }
            if ((state + page*10 + 1) >= totalMon) 
            {
                gotoxy(wherex()-1,wherey());
                cout << " ";
                gotoxy(7,wherey());
                cout << muiten;
            }
        }
    }   

    if (s == PAGEDOWN && check == false)
    {
        AnConTro();
        if (page < maxpage)
        {
            for(int i = 0; i < 28;i++)
            {
                gotoxy(6,6+i);
                cout << "                                                          ";
                gotoxy(66,6+i);
                cout << "                                                          ";
            }
            gotoxy(wherex()-1,wherey());
            cout << " ";
            gotoxy(7,6);
            cout << muiten;
            state = 0;
            page++;
            InDSMon(root, page);
            gotoxy(8,6);
        }
    }

    if (s == PAGEUP && check == false)
    {
        AnConTro();
        if (page > 0)
        {
            for(int i = 0; i < 28;i++)
            {
                gotoxy(6,6+i);
                cout << "                                                          ";
                gotoxy(66,6+i);
                cout << "                                                          ";
            }
            gotoxy(wherex()-1,wherey());
            cout << " ";
            gotoxy(7,6);
            cout << muiten;
            state = 0;
            page--;
            InDSMon(root, page);
            gotoxy(8,6);
        }
    }

    if (s == ENTER)
    {
        // vao danh sach cau hoi cua mon dang chon
        // Lấy node môn được chọn: vị trí = state + page*10 (0-based)
        int selectedPos = state + page * 10;
        NodeMon* selectedMon = getMonAt(root, selectedPos);
        if (selectedMon == nullptr)
        {
            string tb = "Khong tim thay mon hoc duoc chon!";
            InTB(tb,132,30);
            AnConTro();
            Sleep(750);
            XoaTB(130,26);
            // quay lại vòng lặp
            batphim(s,check);
            continue;
        }

        // Duyệt cây câu hỏi dsch.DSCH (LNR) và thu ID các câu thuộc môn được chọn
        int arr[/*dsch.SLCH*/ 10000]; // nếu dsch.SLCH khả năng lớn, đảm bảo kích thước đủ; tốt nhất cấp động theo SLCH
        int dem = 0;
        Tree Stack[STACKSIZE];
        Tree p = dsch.DSCH;
        int sp = -1;
        do // duyet cay LNR
        { 
            while (p != NULL)
            {
                sp++;
                Stack[sp]= p;
                p = p->pLeft;
            }
            if (sp != -1)
            {
                p = Stack[sp];
                sp--;
                // in vao danh sach ch
                if (p->MAMH.compare(selectedMon->MAMH) == 0)
                {
                    arr[dem] = p->ID;
                    dem++;
                }
                p = p->pRight;
            }
            else break;
			} while (1);
			if(dem == 0)
			{
				string tb = "Danh sach cau hoi hien tai dang trong!";
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);
			}
			else 
			{
				system("cls");
				gotoxy(50,46);
				cout << "ESC: Thoat	 LEFT,RIGHT: Qua Cau";
				int index = 0;
				Tree ch = TimKiemCauHoi(dsch.DSCH, arr[index]);
				gotoxy(132,2);
				veKhung(9,33);
				gotoxy(135,4);
				cout << "MA MON HOC: ";
				gotoxy(150,4);
				cout << ch->MAMH;
				gotoxy(135,7);
				cout << "ID CAU HOI: ";
				gotoxy(150,7);
				cout << ch->ID;
				gotoxy(5,2);
				veKhung(36,125);
				gotoxy(6,7-2);
				cout << "NOI DUNG CH: ";
				gotoxy(19,6-2);
				veKhung(7,100);
				gotoxy(6,16-2);
				cout << "DAP AN A: ";
				gotoxy(19,15-2);
				veKhung(5,100);
				gotoxy(6,22-2);
				cout << "DAP AN B: ";
				gotoxy(19,21-2);
				veKhung(5,100);
				gotoxy(6,28-2);
				cout << "DAP AN C: ";
				gotoxy(19,27-2);
				veKhung(5,100);
				gotoxy(6,34-2);
				cout << "DAP AN D: ";
				gotoxy(19,33-2);
				veKhung(5,100);
				InNDCH(ch->NOIDUNG);
				gotoxy(20,14);
				InDA_XemCH(ch->A);
				gotoxy(20,20);
				InDA_XemCH(ch->B);
				gotoxy(20,26);
				InDA_XemCH(ch->C);
				gotoxy(20,32);
				InDA_XemCH(ch->D);
				if(ch->DA == "A")
				{
					ChangeColor(240);
					gotoxy(6,16-2);
					cout << "DAP AN A: ";
					ChangeColor(15);
				}
				else if(ch->DA == "B")
				{
					ChangeColor(240);
					gotoxy(6,22-2);
					cout << "DAP AN B: ";
					ChangeColor(15);
				}
				else if(ch->DA == "C")
				{
					ChangeColor(240);
					gotoxy(6,28-2);
					cout << "DAP AN C: ";
					ChangeColor(15);
				}
				else if(ch->DA == "D")
				{
					ChangeColor(240);
					gotoxy(6,34-2);
					cout << "DAP AN D: ";
					ChangeColor(15);
				}
				while (s != ESC)
				{
					if(s == LEFT && check == false)
					{
						if(index > 0)
						{
							index--;
							for(int i = 0; i < 30;i++)
							{
								gotoxy(20,5+i);
								if(i == 4) i = 8;
								if (i == 11) i = 14;
								if (i == 17) i = 20;
								if (i == 23) i = 26;
								cout << "                                                                                                  ";
							}
							ch = TimKiemCauHoi(dsch.DSCH, arr[index]);
							gotoxy(132,2);
							veKhung(9,33);
							gotoxy(135,4);
							cout << "MA MON HOC: ";
							gotoxy(150,4);
							cout << ch->MAMH;
							gotoxy(135,7);
							cout << "ID CAU HOI: ";
							gotoxy(150,7);
							cout << ch->ID;
							gotoxy(5,2);
							gotoxy(6,16-2);
							cout << "DAP AN A: ";
							gotoxy(19,15-2);
							veKhung(5,100);
							gotoxy(6,22-2);
							cout << "DAP AN B: ";
							gotoxy(19,21-2);
							veKhung(5,100);
							gotoxy(6,28-2);
							cout << "DAP AN C: ";
							gotoxy(19,27-2);
							veKhung(5,100);
							gotoxy(6,34-2);
							cout << "DAP AN D: ";
							InNDCH(ch->NOIDUNG);
							gotoxy(20,14);
							InDA_XemCH(ch->A);
							gotoxy(20,20);
							InDA_XemCH(ch->B);
							gotoxy(20,26);
							InDA_XemCH(ch->C);
							gotoxy(20,32);
							InDA_XemCH(ch->D);
							if(ch->DA == "A")
							{
								ChangeColor(240);
								gotoxy(6,16-2);
								cout << "DAP AN A: ";
								ChangeColor(15);
							}
							else if(ch->DA == "B")
							{
								ChangeColor(240);
								gotoxy(6,22-2);
								cout << "DAP AN B: ";
								ChangeColor(15);
							}
							else if(ch->DA == "C")
							{
								ChangeColor(240);
								gotoxy(6,28-2);
								cout << "DAP AN C: ";
								ChangeColor(15);
							}
							else if(ch->DA == "D")
							{
								ChangeColor(240);
								gotoxy(6,34-2);
								cout << "DAP AN D: ";
								ChangeColor(15);
							}
						}	
					}
					if(s == RIGHT && check == false)
					{
						if(index < dem - 1)
						{
							index++;
							for(int i = 0; i < 30;i++)
							{
								gotoxy(20,5+i);
								if(i == 4) i = 8;
								if (i == 11) i = 14;
								if (i == 17) i = 20;
								if (i == 23) i = 26;
								cout << "                                                                                                  ";
							}
							ch = TimKiemCauHoi(dsch.DSCH, arr[index]);
							gotoxy(132,2);
							veKhung(9,33);
							gotoxy(135,4);
							cout << "MA MON HOC: ";
							gotoxy(150,4);
							cout << ch->MAMH;
							gotoxy(135,7);
							cout << "ID CAU HOI: ";
							gotoxy(150,7);
							cout << ch->ID;
							gotoxy(5,2);
							gotoxy(6,16-2);
							cout << "DAP AN A: ";
							gotoxy(19,15-2);
							veKhung(5,100);
							gotoxy(6,22-2);
							cout << "DAP AN B: ";
							gotoxy(19,21-2);
							veKhung(5,100);
							gotoxy(6,28-2);
							cout << "DAP AN C: ";
							gotoxy(19,27-2);
							veKhung(5,100);
							gotoxy(6,34-2);
							cout << "DAP AN D: ";
							InNDCH(ch->NOIDUNG);
							gotoxy(20,14);
							InDA_XemCH(ch->A);
							gotoxy(20,20);
							InDA_XemCH(ch->B);
							gotoxy(20,26);
							InDA_XemCH(ch->C);
							gotoxy(20,32);
							InDA_XemCH(ch->D);
							if(ch->DA == "A")
							{
								ChangeColor(240);
								gotoxy(6,16-2);
								cout << "DAP AN A: ";
								ChangeColor(15);
							}
							else if(ch->DA == "B")
							{
								ChangeColor(240);
								gotoxy(6,22-2);
								cout << "DAP AN B: ";
								ChangeColor(15);
							}
							else if(ch->DA == "C")
							{
								ChangeColor(240);
								gotoxy(6,28-2);
								cout << "DAP AN C: ";
								ChangeColor(15);
							}
							else if(ch->DA == "D")
							{
								ChangeColor(240);
								gotoxy(6,34-2);
								cout << "DAP AN D: ";
								ChangeColor(15);
							}
						}
					}
					batphim(s,check);
				}
				//ve lai
				system("cls");
				gotoxy(50,46);
				cout << "ENTER: Chon	ESC: Thoat	PGUP: Qua trang	PGDOWN: Lui trang	UP: Len		DOWN: Xuong";
				gotoxy(130,26);
				vekhungTB(10,36);
				page = 0;
				gotoxy(5,2);
				state = 0;
				vekhungDS(34,120,2);	
				gotoxy(30,3);
				cout << "MA MON HOC";
				gotoxy(90,3);
				cout << "TEN MON HOC";
			}
			for(int i = 0; i < 10; i++)
			{
				gotoxy(7,6+i*3);
				cout << " ";
			}
			InDSMon(root,page);
			state = 0;
			gotoxy(7,6);
			cout << muiten;	
		}
		batphim(s,check);
	}
}

// ==================== FUNCTION CH ==========================
void FunctionCH(DSCH &dsch, TreeMH root, DSDT dsdt, DanhSachID &dsID)// đã sửa, xem lại
{
    // ===== Vẽ giao diện chính =====
    gotoxy(50, 46);
    cout << "ENTER: Chon    ESC: Thoat    PGUP: Qua trang    PGDOWN: Lui trang    UP: Len    DOWN: Xuong";
    gotoxy(130, 26);
    vekhungTB(10, 36);
    veNut(3, 15, 150, 5,  "Them CH", 240);
    veNut(3, 15, 150, 10, "Xoa CH", 20);
    veNut(3, 15, 150, 15, "Xem CH", 20);
    veNut(3, 15, 150, 20, "Xem CH theo mon", 20);

    int page = 0, maxpage = 0, state = 0;
    char s;
    bool check;

    // ===== Tạo mảng ID từ danh sách liên kết =====
    int *arr = new int[dsch.SLCH];
    CauHoiNode p = dsch.pHead;
    int i = 0;
    while (p != NULL && i < dsch.SLCH)
    {
        arr[i++] = p->ID;
        p = p->pNext;
    }

    gotoxy(5, 2);
    vekhungDSCH(34, 120, 5);
    InDSCH(dsch, page, arr);

    batphim(s, check);

    while (s != ESC)
    {
        // ===== Cập nhật số trang =====
        if (dsch.SLCH <= 10)
            maxpage = 0;
        else if (dsch.SLCH % 10 == 0)
            maxpage = dsch.SLCH / 10 - 1;
        else
            maxpage = dsch.SLCH / 10;

        // ===== Di chuyển con trỏ menu =====
        if (s == UP && check == false && state > 0)
        {
            state--;
            veNut(3, 15, 150, 5,  "Them CH", (state == 0) ? 240 : 20);
            veNut(3, 15, 150, 10, "Xoa CH",  (state == 1) ? 240 : 20);
            veNut(3, 15, 150, 15, "Xem CH",  (state == 2) ? 240 : 20);
            veNut(3, 15, 150, 20, "Xem CH theo mon", (state == 3) ? 240 : 20);
        }
        else if (s == DOWN && check == false && state < 3)
        {
            state++;
            veNut(3, 15, 150, 5,  "Them CH", (state == 0) ? 240 : 20);
            veNut(3, 15, 150, 10, "Xoa CH",  (state == 1) ? 240 : 20);
            veNut(3, 15, 150, 15, "Xem CH",  (state == 2) ? 240 : 20);
            veNut(3, 15, 150, 20, "Xem CH theo mon", (state == 3) ? 240 : 20);
        }

        // ===== Chuyển trang =====
        if (s == PAGEDOWN && check == false && page < maxpage)
        {
            AnConTro();
            for (int i = 0; i < 28; i++)
            {
                gotoxy(6, 6 + i);  cout << "                      ";
                gotoxy(31, 6 + i); cout << "                      ";
                gotoxy(54, 6 + i); cout << "                                                                    ";
            }
            page++;
            InDSCH(dsch, page, arr);
        }
        else if (s == PAGEUP && check == false && page > 0)
        {
            AnConTro();
            for (int i = 0; i < 28; i++)
            {
                gotoxy(6, 6 + i);  cout << "                      ";
                gotoxy(31, 6 + i); cout << "                      ";
                gotoxy(54, 6 + i); cout << "                                                                    ";
            }
            page--;
            InDSCH(dsch, page, arr);
        }

        // ===== ENTER: chọn menu =====
        if (s == ENTER)
        {
            switch (state)
            {
                // ---- THÊM CÂU HỎI ----
                case 0:
                {
                    ThemCH(dsch, root, dsID);

                    // Cập nhật lại mảng ID sau khi thêm
                    i = 0; p = dsch.pHead;
                    while (p != NULL && i < dsch.SLCH)
                    {
                        arr[i++] = p->ID;
                        p = p->pNext;
                    }

                    // Vẽ lại khung
                    system("cls");
                    gotoxy(50, 46);
                    cout << "ENTER: Chon    ESC: Thoat    PGUP: Qua trang    PGDOWN: Lui trang    UP: Len    DOWN: Xuong";
                    gotoxy(130, 26);
                    vekhungTB(10, 36);
                    veNut(3, 15, 150, 5,  "Them CH", 240);
                    veNut(3, 15, 150, 10, "Xoa CH", 20);
                    veNut(3, 15, 150, 15, "Xem CH", 20);
                    veNut(3, 15, 150, 20, "Xem CH theo mon", 20);
                    gotoxy(5, 2);
                    vekhungDSCH(34, 120, 5);
                    InDSCH(dsch, page, arr);
                    break;
                }

                // ---- XÓA CÂU HỎI ----
                case 1:
                {
                    XoaCauHoi(dsch, arr, dsdt);
                    AnConTro();
                    break;
                }

                // ---- XEM CÂU HỎI ----
                case 2:
                {
                    XemCauHoi(dsch, arr);
                    AnConTro();
                    break;
                }

                // ---- XEM CÂU HỎI THEO MÔN ----
                case 3:
                {
                    XemCHTheoMon(root, dsch);
                    AnConTro();

                    // Sau khi xem xong, vẽ lại khung chính
                    system("cls");
                    gotoxy(50, 46);
                    cout << "ENTER: Chon    ESC: Thoat    PGUP: Qua trang    PGDOWN: Lui trang    UP: Len    DOWN: Xuong";
                    gotoxy(130, 26);
                    vekhungTB(10, 36);
                    veNut(3, 15, 150, 5,  "Them CH", 20);
                    veNut(3, 15, 150, 10, "Xoa CH", 20);
                    veNut(3, 15, 150, 15, "Xem CH", 20);
                    veNut(3, 15, 150, 20, "Xem CH theo mon", 240);
                    gotoxy(5, 2);
                    vekhungDSCH(34, 120, 5);
                    InDSCH(dsch, page, arr);
                    break;
                }
            }
        }

        batphim(s, check);
    }

    delete[] arr;
}





void insertarray(char *h, TG *j) 
{
	int temp = 0;
	temp = j->Giay;
	h[7] = doichar(temp % 10);
	h[6] = doichar(temp /= 10);

	temp = j->Phut;
	h[4] = doichar(temp % 10);
	h[3] = doichar(temp /= 10);

	temp = j->Gio;
	h[1] = doichar(temp % 10);
	h[0] = doichar(temp /= 10);

}
// ==================== CAP NHAP THOI GIAN THI ==========================
bool changetime(TG *h)
{
	if (h->Giay > 0) --h->Giay;
	else if (h->Phut > 0)
	{
		h->Giay = 59;
		--h->Phut;
	}
	else if (h->Gio > 0)
	{
		--h->Gio;
		h->Phut = 59;
		h->Giay = 59;
	}
	else return false;
	return true;
}
// ==================== HAM THAY THE COUT IN RA 1 CHUOI ==========================
void WriteBlockChar(char *Arraych,int x, int y,int color)
{
	CHAR_INFO *charater = new CHAR_INFO[8];
	for (int i = 0; i < 8; i++)
	{
		charater[i].Attributes = color;
		charater[i].Char.AsciiChar = Arraych[i];
	}
	COORD sizebuff = { 8,1 };
	COORD pos = { 0,0 };
	SMALL_RECT earea = { x,y,x + 8 - 1,y + 1 - 1 }; // vung dem
	WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), charater, sizebuff, pos, &earea);
	delete[] charater;
}
// ==================== IN DONG HO ==========================
void printClock(int tg)
{
	TG h;
	if(tg < 60)
	{
		h = { 0,tg,0};
	}
	else if (tg == 60)
	{
		h = { 1,0,0};
	}
	else
	{
		int gio = tg/60;
		int phut = tg%60;
		h = { gio,phut,0};
	}
	char a[8] = { '0','0',':','0','0',':','0','0'};
	while (stop)
	{
		if (changetime(&h) == false) stop = 0;
		insertarray(a, &h);
		WriteBlockChar(a, 115, 1,0x007|0x000);
		Sleep(1000);
	}
	return;
}

void NhapTG (int &tg, int &sct)
{
	system("cls");
	gotoxy(130,26);
	vekhungTB(10,36);
	string ntg;
	string nsct;
	vekhungNhapTG();
	gotoxy(68,20);
	char s;
	bool check;
	int state = 0;
	HienConTro();
	batphim(s,check);
	while(s != ESC)
	{
		if(s == LEFT && check == false)
		{
			if(state == 1)
			{
				gotoxy(68+ntg.length(),20);
				state --;
			}
		}
		if(s == RIGHT && check == false)
		{
			if(state == 0)
			{
				gotoxy(112+nsct.length(),20);
				state ++;
			}
		}
		if((s >= '0' && s <= '9')  && check == true)
		{
			if(state == 0 && ntg.length() < 3)
			{
				cout << s;
				ntg += s;	
			}
			else if(state == 1 && nsct.length() < 3)
			{
				cout << s;
				nsct +=s;
			}
		}
		if (s == BACKSPACE)
		{
			if (ntg.length() > 0 && state == 0)
			{
				AnConTro();
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(wherex()-1,wherey());
				HienConTro();
				ntg.erase(ntg.length()-1);
			}
			else if(nsct.length() > 0 && state == 1)
			{
				AnConTro();
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(wherex()-1,wherey());
				HienConTro();
				nsct.erase(nsct.length()-1);
			}	
		}
		if(s == ENTER)
		{
			if(ntg.length() == 0 || nsct.length() == 0)
			{
				string tb = "Thoi gian thi hoac so cau thi khong hop le";
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);	
			}
			else
			{
				if(StringToInt(ntg) > 0 && StringToInt(nsct) > 0)
					{
						tg = StringToInt(ntg);
						sct = StringToInt(nsct);
						return;	
					}
				else
				{
					string tb = "Thoi gian thi hoac so cau thi phai lon hon '0'";
					InTB(tb,132,30);
					AnConTro();
					Sleep(750);
					XoaTB(130,26);
				}
			}
			gotoxy(68,20);
			cout << "   ";
			gotoxy(112,20);
			cout << "   ";
			ntg = "";
			nsct = "";
			state = 0;
			gotoxy(68+ntg.length(),20);
			HienConTro();
		}
		batphim(s,check);
	}
}

// ==================== NHAP MON THI ==========================
void NhapMonThi(TreeMH root, int &tg, int &sct, string &monthi, bool &check)
{
	AnConTro();
	gotoxy(59,1);
	cout << "CHON MON THI";
	gotoxy(5,2);
	vekhungDS(34,120,2);
	gotoxy(30,3);
	cout << "MA MON HOC";
	gotoxy(90,3);
	cout << "TEN MON HOC";
	string tb;
	int maxpage;
	int page = 0;
	InDSMon(root,page);
	char s;
	int state = 0;
	bool sCheck;
	gotoxy(7,6);
	cout << muiten;
	batphim(s,sCheck);
	while (s != ESC)
	{
		if( <= 10)	maxpage = 0;
		else if( % 10 == 0) maxpage = /10 -1;
		else maxpage = /10;
		if(s == UP && sCheck == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSMon(root,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && sCheck == false)
		{
			if(state == 9)
			{
				if((state + page*10 + 1) < )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					page++;
					InDSMon(root,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if((state + page*10 + 1) < )
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if((state + page*10 + 1) >= ) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && sCheck == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && sCheck == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if (s == ENTER)
		{
			//nhap tg
			NhapTG(tg,sct);
			monthi = getMonTheoThuTu(root, state + page * 10)->MAMH;// da sua

			if(tg > 0 && sct > 0)
			{
				check = true;
				return;
			}
			gotoxy(59,1);
			cout << "CHON MON THI";
			gotoxy(5,2);
			vekhungDS(34,120,2);
			gotoxy(30,3);
			cout << "MA MON HOC";
			gotoxy(90,3);
			cout << "TEN MON HOC";
			InDSMon(root,page);
			state = 0;
			gotoxy(7,6);
			cout << muiten;
			AnConTro();
		}	
		batphim(s,sCheck);
	}
	check = false;
}
// ==================== VE KHUNG DAP AN THI SINH DA CHON ==========================
void VeKhungDA(int page, int sct, CTDT ctdt)
{
	gotoxy(15,38);
	int socau;
	if(sct <= 10)
	{
		socau = sct;
	}
	else if((page + 1)*10 <= sct)
	{
		socau = 10;
	}
	else socau = sct%10;
	int rong = socau*10;
	int dem = 1;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < rong; j++)
		{
			if (i == 0)
			{
				if (j == 0) cout << traitren;
				else if (j == rong-1) cout << phaitren;
				else if (j == (rong/socau)*dem) cout << ngangxuong;
				else cout << ngang;
			}
			else if(i == 2)
			{
				if(j == 0) cout << docphai;
				else if (j == rong -1) cout << doctrai;
				else if (j == (rong/socau)*dem) cout << giua;
				else cout << ngang;
			}
			else if (i == 5)
			{
				if (j == 0) cout << traiduoi;
				else if (j == rong-1) cout << phaiduoi;
				else if (j == (rong/socau)*dem) cout << nganglen;
				else cout << ngang;
			}
			else if(j == (rong/socau)*dem)
			{
				cout << doc;
			}
			else
			{
				if (j == 0 || j == rong-1) cout << doc;
				else cout << " ";
			}
			if(j == dem*(rong/socau)) dem++;
			if(dem == socau) dem = 1;
		}
		gotoxy(wherex()-rong,wherey()+1);
	}
	int temp = page*10 + 1;
	for(int i = 0; i < socau ; i++)
	{
		gotoxy(15 + 4 + (i*10),38+1);
		cout << temp;
		temp ++;
	}
	for(int i = 0; i < socau; i++)
	{
		gotoxy(15 + 4 + (i*10),38+3);
		if(ctdt.dapan[(page*10) + i] == 1)
		{
			cout << "A";
		}
		else if (ctdt.dapan[(page*10) + i] == 2)
		{
			cout << "B";
		}
		else if(ctdt.dapan[(page*10) + i] == 3)
		{
			cout << "C";
		}
		else if(ctdt.dapan[(page*10) + i] == 4)
		{
			cout << "D";
		}
		else continue;
	}
}
// ==================== XOA KHUNG DAP AN THI SINH DA CHON ==========================
void XoaDA()
{
	for(int i = 0; i < 6; i++)
	{
		gotoxy(14,38+i);
		cout <<"                                                                                                     "; 
	}
}
// ==================== CAP NHAP BANG DAP AN THI SINH DA CHON ==========================
void InDA(int page, int sct, CTDT ctdt)
{
	int socau;
	if(sct <= 10)	socau = sct;
	else if((page + 1)*10 <= sct)	socau = 10;
	else socau = sct%10;
	for(int i = 0; i < socau; i++)
	{
		gotoxy(15 + 4 + (i*10),38+3);
		if(ctdt.dapan[(page*10) + i] == 1)
		{
			cout << "A";
		}
		else if (ctdt.dapan[(page*10) + i] == 2)
		{
			cout << "B";
		}
		else if(ctdt.dapan[(page*10) + i] == 3)
		{
			cout << "C";
		}
		else if(ctdt.dapan[(page*10) + i] == 4)
		{
			cout << "D";
		}
//		else continue;
	}
}
void In1CauThi(DSCH &dsch, int id) //đã sửa
{
    // Xóa khung cũ
    for (int i = 0; i < 30; i++) {
        gotoxy(20, 5 + i);
        if (i == 4)  i = 8;
        if (i == 11) i = 14;
        if (i == 17) i = 20;
        if (i == 23) i = 26;
        cout << "                                                                                                  ";
    }

    // Tìm câu hỏi theo ID
    CauHoiNode* ch = TimKiemCauHoi(dsch, id);
    if (ch == NULL) {
        gotoxy(50, 20);
        cout << "Khong tim thay cau hoi co ID: " << id;
        return;
    }

    // In nội dung
    InNDCH(ch->data.NOIDUNG);
    gotoxy(20, 14); InDA_XemCH(ch->data.A);
    gotoxy(20, 20); InDA_XemCH(ch->data.B);
    gotoxy(20, 26); InDA_XemCH(ch->data.C);
    gotoxy(20, 32); InDA_XemCH(ch->data.D);
}

//Tuyen
// ==================== LAY DE THI THEO MA MON HOC ==========================
int* LayDeThi(DSCH &dsch, int sct, const string &mamon) //đã sửa, xem lại B2
{
    // ======= B1: Kiểm tra danh sách trống =======
    if (dsch.SLCH == 0) {
        cout << "Danh sach cau hoi rong!\n";
        return NULL;
    }

    // ======= B2: Lọc câu hỏi thuộc môn học =======
    CauHoiNode arr[10000];
    int n = 0;

    for (CauHoiNode p = dsch.pHead; p != NULL; p = p->pNext) {
        if (p->MAMH == mamon) {
            arr[n++] = p;
        }
    }

    // ======= B3: Kiểm tra đủ câu hỏi để thi =======
    if (n < sct) {
        string tb = "Khong du cau hoi de thi";
        InTB(tb, 132, 30);
        AnConTro();
        Sleep(750);
        XoaTB(130, 26);
        return NULL;
    }
    // ======= B4: Trộn ngẫu nhiên danh sách =======
    srand((unsigned)time(NULL));
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() % (n - i);
        swap(arr[i], arr[j]);
    }

    // ======= B5: Tạo đề thi =======
    int *dethi = new int[sct];
    for (int i = 0; i < sct; i++) {
        dethi[i] = arr[i]->ID;
        arr[i]->daThi = true;   // gắn cờ đã thi
    }

    return dethi;
}


// ==================== TINH DIEM ==========================
int TinhDiem(CTDT ctdt, Tree t)
{
	int socaudung = 0;
	string dapan="";
	for(int i = 0; i < ctdt.sct ; i++)
	{
		Tree p = TimKiemCauHoi(t,ctdt.bode[i]);
		if(ctdt.dapan[i] == 1)	dapan = "A";
		else if(ctdt.dapan[i] == 2)	dapan = "B";
		else if(ctdt.dapan[i] == 3)	dapan = "C";
		else if(ctdt.dapan[i] == 4)	dapan = "D";
		if(p->DA.compare(dapan) == 0)	socaudung++;
		dapan="";
	}
	return socaudung;
}
void ketThucBaiThi (CTDT ctdt)
{
	system("cls");
	gotoxy(15,7);
	cout << "	 _______  _______  __    _  _______  ______    _______  _______  __   __  ___      _______  _______  ___   _______  __    _  __  ";
	gotoxy(15,8);
	cout << "	|       ||       ||  |  | ||       ||    _ |  |   _   ||       ||  | |  ||   |    |   _   ||       ||   | |       ||  |  | ||  | ";
	gotoxy(15,9);
	cout << "	|       ||   _   ||   |_| ||    ___||   | ||  |  |_|  ||_     _||  | |  ||   |    |  |_|  ||_     _||   | |   _   ||   |_| ||  | ";
	gotoxy(15,10);
	cout << "	|       ||  | |  ||       ||   | __ |   |_||_ |       |  |   |  |  |_|  ||   |    |       |  |   |  |   | |  | |  ||       ||  | ";
	gotoxy(15,11);
	cout << "	|      _||  |_|  ||  _    ||   ||  ||    __  ||       |  |   |  |       ||   |___ |       |  |   |  |   | |  |_|  ||  _    ||__| ";
	gotoxy(15,12);
	cout << "	|     |_ |       || | |   ||   |_| ||   |  | ||   _   |  |   |  |       ||       ||   _   |  |   |  |   | |       || | |   | __  ";
	gotoxy(15,13);
	cout << "	|_______||_______||_|  |__||_______||___|  |_||__| |__|  |___|  |_______||_______||__| |__|  |___|  |___| |_______||_|  |__||__| ";
	gotoxy(50,25);
	cout << "CHUC MUNG BAN DA HOAN THANH BAI THI!";
	gotoxy(50,30);
	ChangeColor(240);
	cout << "DIEM CUA BAN LA: " << ctdt.DIEM;
	ChangeColor(15);
	gotoxy(50,35);
	cout << "Bam phim bat ki de thoat!";
	getch();
}

// ==================== FUNCTION THI ==========================
void FunctionThi(DSCH dsch, int tg, int sct, string monthi, float &diem, CTDT &ctdt)
{
	if(sct == 0 && tg == 0)
	{
		return ;
	}
	ctdt.sct = sct;
	ctdt.tg = tg;
	for(int i = 0; i < sct; i++)
	{
		ctdt.dapan[i] = 0;
	}
	ctdt.bode = LayDeThi(dsch,sct,ctdt.MAMH);
	if(ctdt.bode == NULL)
	{
		return;
	}
	thread clock;
	clock = thread(printClock, tg);
	gotoxy(40,46);
	cout << "ENTER: Chon       F1: Nop bai     UP/DOWN: Chon Dap An 	  Left/Right: Di chuyen cau hoi     ";
	gotoxy(50,1);
	cout << "BAI THI MON: " << monthi;
	int cauthi = 0;
	int page = 0;
	int maxpage;
	if(sct <= 10)	maxpage = 0;
	else if(sct > 10 && sct % 10 == 0)	maxpage = (sct/10) - 1;
	else maxpage = sct/10;
	gotoxy(5,2);
	veKhung(36,125);
	gotoxy(6,7-2);
	cout << "NOI DUNG CH: ";
	gotoxy(19,6-2);
	veKhung(7,100);
	gotoxy(6,16-2);
	cout << "DAP AN A: ";
	gotoxy(19,15-2);
	veKhung(5,100);
	gotoxy(6,22-2);
	cout << "DAP AN B: ";
	gotoxy(19,21-2);
	veKhung(5,100);
	gotoxy(6,28-2);
	cout << "DAP AN C: ";
	gotoxy(19,27-2);
	veKhung(5,100);
	gotoxy(6,34-2);
	cout << "DAP AN D: ";
	gotoxy(19,33-2);
	veKhung(5,100);
	Tree ch = TimKiemCauHoi(dsch.DSCH,ctdt.bode[cauthi]);
	InNDCH(ch->NOIDUNG);
	gotoxy(20,14);
	InDA_XemCH(ch->A);
	gotoxy(20,20);
	InDA_XemCH(ch->B);
	gotoxy(20,26);
	InDA_XemCH(ch->C);
	gotoxy(20,32);
	InDA_XemCH(ch->D);
	VeKhungDA(page,sct,ctdt);
	gotoxy(7,1);
	cout << "CAU " << cauthi + 1;
	gotoxy(19 + (cauthi%10)*10,44);
	cout << muitenlen;
	gotoxy(4,14);
	cout << muiten;
	AnConTro();
	int state = 0;
	char s;
	bool check;
	bool qt = false;
	batphim(s,check);
	string da = "A";
	gotoxy(19,44);
	cout << muitenlen;
	gotoxy(4,14);
	while ((cauthi < sct) && s != ESC )
	{
		if(s == PAGEUP && check == false)
		{
			if(page > 0 )
			{
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				cauthi -= 10;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				page --;
				XoaDA();
				VeKhungDA(page,sct,ctdt);
				gotoxy(10,1);
				cout << "    ";
				gotoxy(7,1);
				cout << "CAU " << cauthi + 1;
				In1CauThi(dsch.DSCH,ctdt.bode[cauthi]);
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state = 0;
							break;
						}
					case 2:
						{
							state = 1;
							break;
						}
					case 3:
						{
							state = 2;
							break;
						}
					case 4:
						{
							state = 3;
							break;
						}			
				}
				if(state == 0)
				{
					gotoxy(4,14);
					cout << muiten;	
				}
				else if(state == 1)
				{
					gotoxy(4,20);
					cout << muiten;
				}
				else if(state == 2)
				{
					gotoxy(4,26);
					cout << muiten;
				}
				else
				{
					gotoxy(4,32);
					cout << muiten;
				}
			}
		}
		if(s == PAGEDOWN && check == false)
		{
			if(page < maxpage )
			{
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				if(cauthi < sct - 10)
				{
					cauthi += 10;
//					gotoxy(19 + (cauthi%10)*10,44);
//					cout << muitenlen;
				}
				else cauthi += sct - cauthi - 1;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				page ++;
				XoaDA();
				VeKhungDA(page,sct,ctdt);
				gotoxy(10,1);
				cout << "    ";
				gotoxy(7,1);
				cout << "CAU " << cauthi + 1;
				In1CauThi(dsch.DSCH,ctdt.bode[cauthi]);
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state = 0;
							break;
						}
					case 2:
						{
							state = 1;
							break;
						}
					case 3:
						{
							state = 2;
							break;
						}
					case 4:
						{
							state = 3;
							break;
						}			
				}
				if(state == 0)
				{
					gotoxy(4,14);
					cout << muiten;	
				}
				else if(state == 1)
				{
					gotoxy(4,20);
					cout << muiten;
				}
				else if(state == 2)
				{
					gotoxy(4,26);
					cout << muiten;
				}
				else
				{
					gotoxy(4,32);
					cout << muiten;
				}
			}
		}
		if (s == LEFT && check == false)
		{
			if(page > 0 && (cauthi + 1) % 10 == 1)
			{
				page--;
				qt = true;
			}
			if (qt == true)
			{
				XoaDA();
				VeKhungDA(page,sct,ctdt);
				qt = false;
			}
			else InDA(page,sct,ctdt);
			if (cauthi > 0)
			{
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				cauthi--;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				gotoxy(10,1);
				cout << "    ";
				gotoxy(7,1);
				cout << "CAU " << cauthi + 1;
				In1CauThi(dsch.DSCH,ctdt.bode[cauthi]);
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state = 0;
							break;
						}
					case 2:
						{
							state = 1;
							break;
						}
					case 3:
						{
							state = 2;
							break;
						}
					case 4:
						{
							state = 3;
							break;
						}			
				}
				if(state == 0)
				{
					gotoxy(4,14);
					cout << muiten;	
				}
				else if(state == 1)
				{
					gotoxy(4,20);
					cout << muiten;
				}
				else if(state == 2)
				{
					gotoxy(4,26);
					cout << muiten;
				}
				else
				{
					gotoxy(4,32);
					cout << muiten;
				}
			}
		}
		if (s == RIGHT && check == false)
		{
			if(page < maxpage && (cauthi + 1) % 10 == 0)
			{
				page++;
				qt = true;
			}
			if (qt == true)
			{
				XoaDA();
				VeKhungDA(page,sct,ctdt);
				qt = false;
			}
			else InDA(page,sct,ctdt);
			if (cauthi < sct - 1)
			{
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				cauthi++;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				gotoxy(10,1);
				cout << "            ";
				gotoxy(7,1);
				cout << "CAU " << cauthi + 1;
				In1CauThi(dsch.DSCH,ctdt.bode[cauthi]);
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state = 0;
							break;
						}
					case 2:
						{
							state = 1;
							break;
						}
					case 3:
						{
							state = 2;
							break;
						}
					case 4:
						{
							state = 3;
							break;
						}			
				}
				if(state == 0)
				{
					gotoxy(4,14);
					cout << muiten;	
				}
				else if(state == 1)
				{
					gotoxy(4,20);
					cout << muiten;
				}
				else if(state == 2)
				{
					gotoxy(4,26);
					cout << muiten;
				}
				else
				{
					gotoxy(4,32);
					cout << muiten;
				}
			}
		}
		if(s == UP && check == false)
		{
			switch(state)
			{
				case 1:
					{
						AnConTro();
						gotoxy(wherex()-1,wherey());
						cout << " ";
						gotoxy(4,14);
						cout << muiten;
						state--;
						da = "A";
						break;
					}
				case 2:
					{
						AnConTro();
						gotoxy(wherex()-1,wherey());
						cout << " ";
						gotoxy(4,20);
						cout << muiten;
						state--;
						da = "B";
						break;
					}
				case 3:
					{
						AnConTro();
						gotoxy(wherex()-1,wherey());
						cout << " ";
						gotoxy(4,26);
						cout << muiten;
						state--;
						da = "C";
						break;
					}
			}	
		}
		if(s == DOWN && check == false)
		{
			switch(state)
			{
				case 0:
					{
						AnConTro();
						gotoxy(wherex()-1,wherey());
						gotoxy(4,14);
						cout << " ";
						gotoxy(4,20);
						cout << muiten;
						state++;
						da = "B";
						break;
					}
				case 1:
					{
						AnConTro();
						gotoxy(wherex()-1,wherey());
						cout << " ";
						gotoxy(4,26);
						cout << muiten;
						state++;
						da = "C";
						break;
					}
				case 2:
					{
						AnConTro();
						gotoxy(wherex()-1,wherey());
						cout << " ";
						gotoxy(4,32);
						cout << muiten;
						state++;
						da = "D";
						break;
					}
			}
		}
		if(s == ENTER)
		{
			if(da == "A")
			{
				ctdt.dapan[cauthi] = 1;
			}
			else if(da == "B")
			{
				ctdt.dapan[cauthi] = 2;
			}
			else if(da == "C")
			{
				ctdt.dapan[cauthi] = 3;
			}
			else if (da == "D")
			{
				ctdt.dapan[cauthi] = 4;
			}
			if (cauthi < sct -1)
			{
				if(page < maxpage && (cauthi + 1) % 10 == 0)
				{
					page++;
					qt = true;
				}
				if (qt == true)
				{
					XoaDA();
					VeKhungDA(page,sct,ctdt);
					qt = false;
				}
				else InDA(page,sct,ctdt);
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				cauthi++;
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				gotoxy(10,1);
				cout << "    ";
				gotoxy(7,1);
				cout << "CAU " << cauthi + 1;
				In1CauThi(dsch.DSCH,ctdt.bode[cauthi]);
				state = 0;
				da = "A";
				for(int i = 0; i < 33; i += 6)
					{
						gotoxy(4,14+i);
						cout << " ";
					}	
				gotoxy(4,14);
				cout << muiten;
			}
			else if(cauthi == sct -1)
			{
				InDA(page,sct,ctdt);
				gotoxy(19 + (cauthi%10)*10,44);
				cout << " ";
				gotoxy(19 + (cauthi%10)*10,44);
				cout << muitenlen;
				switch(ctdt.dapan[cauthi])
				{
					case 1:
						{
							state = 0;
							break;
						}
					case 2:
						{
							state = 1;
							break;
						}
					case 3:
						{
							state = 2;
							break;
						}
					case 4:
						{
							state = 3;
							break;
						}			
				}
				if(state == 0)
				{
					gotoxy(4,14);
					cout << muiten;	
				}
				else if(state == 1)
				{
					gotoxy(4,20);
					cout << muiten;
				}
				else if(state == 2)
				{
					gotoxy(4,26);
					cout << muiten;
				}
				else
				{
					gotoxy(4,32);
					cout << muiten;
				}
			}
		}
		if (s == F1  && check == false)
		{
			string tb = "Ban chac chan muon nop bai ? (Y/N)";
			InTB(tb,132,30);
			batphim(s,check);
			while(s != ESC)
			{
				if((s == 'y' || s == 'Y')&& check == true)
				{
					stop = 0;
					clock.join();
					int socaudung = TinhDiem(ctdt,dsch.DSCH)*10;
					diem = (float)socaudung/(float)sct;
					ctdt.DIEM = diem;
					ketThucBaiThi(ctdt);
					return;
				}
				else if((s == 'n' || s == 'N') && check == true)
				{
					XoaTB(130,26);
					break;
				}
				batphim(s,check);
			}
			InTB(tb,132,30);
		}
		if(s == ESC)
		{
			int socaudung = TinhDiem(ctdt,dsch.DSCH)*10;
			cout << socaudung;
			diem = (float)socaudung/(float)sct;
			ctdt.DIEM = diem;
			cout << " " << diem;
			return ;
		}
		if(stop == 0)
		{
			clock.join();
			string tb = "Het thoi gian lam bai, bam phim bat ky de ket thuc!";
			InTB(tb,132,30);
			int socaudung = TinhDiem(ctdt,dsch.DSCH)*10;
			diem = (float)socaudung/(float)sct;
			ctdt.DIEM = diem;
			ketThucBaiThi(ctdt);
			return;
		}
		batphim(s,check);
	}
	stop = 0;
	clock.join();
}

// ==================== IN 1 CH + DAN AN CUA SV ==========================
void InCH_DASV(CauHoiNode* ch, string da)
{
	for(int i = 0; i < 30;i++)
	{
		gotoxy(20,5+i);
		if(i == 4) i = 8;
		if (i == 11) i = 14;
		if (i == 17) i = 20;
		if (i == 23) i = 26;
		cout << "                                                                                                  ";
	}
	gotoxy(6,16-2);
	cout << "DAP AN A: ";
	gotoxy(6,22-2);
	cout << "DAP AN B: ";
	gotoxy(6,28-2);
	cout << "DAP AN C: ";
	gotoxy(6,34-2);
	cout << "DAP AN D: ";
	InNDCH(ch->NOIDUNG);
	gotoxy(20,14);
	InDA_XemCH(ch->A);
	gotoxy(20,20);
	InDA_XemCH(ch->B);
	gotoxy(20,26);
	InDA_XemCH(ch->C);
	gotoxy(20,32);
	InDA_XemCH(ch->D);
	if(ch->DA == da)
	{
		if(ch->DA == "A")
		{
			ChangeColor(175);
			gotoxy(6,16-2);
			cout << "DAP AN A: ";
			ChangeColor(15);
		}
		else if(ch->DA == "B")
		{
			ChangeColor(175);
			gotoxy(6,22-2);
			cout << "DAP AN B: ";
			ChangeColor(15);
		}
		else if(ch->DA == "C")
		{
			ChangeColor(175);
			gotoxy(6,28-2);
			cout << "DAP AN C: ";
			ChangeColor(15);
		}
		else if(ch->DA == "D")
		{
			ChangeColor(175);
			gotoxy(6,34-2);
			cout << "DAP AN D: ";
			ChangeColor(15);
		}
	}
	else
	{
		if(da == "A")
		{
			ChangeColor(79);
			gotoxy(6,16-2);
			cout << "DAP AN A: ";
			ChangeColor(15);
		}
		else if(da == "B")
		{
			ChangeColor(79);
			gotoxy(6,22-2);
			cout << "DAP AN B: ";
			ChangeColor(15);
		}
		else if(da == "C")
		{
			ChangeColor(79);
			gotoxy(6,28-2);
			cout << "DAP AN C: ";
			ChangeColor(15);
		}
		else if(da == "D")
		{
			ChangeColor(79);
			gotoxy(6,34-2);
			cout << "DAP AN D: ";
			ChangeColor(15);
		}
		if(ch->DA == "A")
		{
			ChangeColor(240);
			gotoxy(6,16-2);
			cout << "DAP AN A: ";
			ChangeColor(15);
		}
		else if(ch->DA == "B")
		{
			ChangeColor(240);
			gotoxy(6,22-2);
			cout << "DAP AN B: ";
			ChangeColor(15);
		}
		else if(ch->DA == "C")
		{
			ChangeColor(240);
			gotoxy(6,28-2);
			cout << "DAP AN C: ";
			ChangeColor(15);
		}
		else if(ch->DA == "D")
		{
			ChangeColor(240);
			gotoxy(6,34-2);
			cout << "DAP AN D: ";
			ChangeColor(15);
		}
	}
}
// ==================== IN CHI TIET 1 LAN THI CUA SV ==========================
void InChiTiet1LanThi(NODEDIEMTHI *p, DSCH dsch, NODESV *k, DSDT dsdt)
{
	system("cls");
	int i;
	for(i = 0; i < dsdt.SLDSDT; i++)
	{
		if(dsdt.DS_CTDT[i].MASV.compare(k->MASV) == 0)
			if(p->DIEM == dsdt.DS_CTDT[i].DIEM && dsdt.DS_CTDT[i].MAMH.compare(p->MAMH)==0)	break; 		
	}
	gotoxy(50,46);
	cout << "ESC: 2 Lan De Thoat	 LEFT/RIGHT: Qua Cau";
	gotoxy(130,2);
	veKhung(21,35);
	gotoxy(133,4);
	cout << "MSSV: ";
	gotoxy(139,4);
	cout << k->MASV;
	gotoxy(133,7);
	cout << "HO VA TEN: ";
	gotoxy(144,7);
	cout << k->HO << " " << k->TEN;
	gotoxy(133,10);
	cout << "GIOI TINH: ";
	gotoxy(144,10);
	cout << k->PHAI;
	gotoxy(133,13);
	cout << "SO CAU DUNG: ";
	gotoxy(150,13);
	cout << TinhDiem(dsdt.DS_CTDT[i],dsch.DSCH);
	gotoxy(133,16);
	cout << "SO CAU THI: ";
	gotoxy(150,16);
	cout << dsdt.DS_CTDT[i].sct;
	gotoxy(133,19);
	cout << "DIEM: ";
	gotoxy(150,19);
	cout << p->DIEM;
	gotoxy(5,2);
	veKhung(36,125);
	gotoxy(6,7-2);
	cout << "NOI DUNG CH: ";
	gotoxy(19,6-2);
	veKhung(7,100);
	gotoxy(6,16-2);
	cout << "DAP AN A: ";
	gotoxy(19,15-2);
	veKhung(5,100);
	gotoxy(6,22-2);
	cout << "DAP AN B: ";
	gotoxy(19,21-2);
	veKhung(5,100);
	gotoxy(6,28-2);
	cout << "DAP AN C: ";
	gotoxy(19,27-2);
	veKhung(5,100);
	gotoxy(6,34-2);
	cout << "DAP AN D: ";
	gotoxy(19,33-2);
	veKhung(5,100);
	int page = 0;
	int stt = 0;
	int maxpage;
	VeKhungDA(page,dsdt.DS_CTDT[i].sct,dsdt.DS_CTDT[i]);
	bool qt = false;
	int max = dsdt.DS_CTDT[i].sct;
	if(max <= 10)	maxpage = 0;
	else if(max > 10 && max % 10 == 0)	maxpage = (max/10) - 1;
	else maxpage = max/10;
	string da;
	Tree ch = TimKiemCauHoi(dsch.DSCH,dsdt.DS_CTDT[i].bode[stt]);
	if(dsdt.DS_CTDT[i].dapan[stt] == 1)
	{
		da = "A";
	}
	else if (dsdt.DS_CTDT[i].dapan[stt] == 2)
	{
		da = "B";
	}
	else if(dsdt.DS_CTDT[i].dapan[stt] == 3)
	{
		da = "C";
	}
	else if(dsdt.DS_CTDT[i].dapan[stt] == 4)
	{
		da = "D";
	}
	else if(dsdt.DS_CTDT[i].dapan[stt] == 0)
	{
		da = "";
	}
	InCH_DASV(ch,da);
	gotoxy(5,1);
	cout << "CAU " << stt + 1;
	gotoxy(19,44);
	cout << muitenlen;
	char s;
	bool check;
	batphim(s,check);
	while (s != ESC)
	{
		if(s == LEFT && check == false)
		{
			if(page > 0 && (stt + 1) % 10 == 1)
			{
				page--;
				qt = true;
			}
			if (qt == true)
			{
				XoaDA();
				VeKhungDA(page,dsdt.DS_CTDT[i].sct,dsdt.DS_CTDT[i]);
				qt = false;
			}
			if(stt > 0)
			{
				gotoxy(19 + (stt%10)*10,44);
				cout << " ";
				stt--;
				gotoxy(19 + (stt%10)*10,44);
				cout << muitenlen;
				Tree ch = TimKiemCauHoi(dsch.DSCH,dsdt.DS_CTDT[i].bode[stt]);
				if(dsdt.DS_CTDT[i].dapan[stt] == 1)
				{
					da = "A";
				}
				else if (dsdt.DS_CTDT[i].dapan[stt] == 2)
				{
					da = "B";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 3)
				{
					da = "C";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 4)
				{
					da = "D";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 0)
				{
					da = "";
				}
				InCH_DASV(ch,da);
				gotoxy(5,1);
				cout << "       ";
				gotoxy(5,1);
				cout << "CAU " << stt + 1;
			}
		}
		if(s == RIGHT && check == false)
		{
			if(page < maxpage && (stt + 1) % 10 == 0)
			{
				page++;
				qt = true;
			}
			if (qt == true)
			{
				XoaDA();
				VeKhungDA(page,dsdt.DS_CTDT[i].sct,dsdt.DS_CTDT[i]);
				qt = false;
			}
			if(stt < max - 1)
			{
				gotoxy(19 + (stt%10)*10,44);
				cout << " ";
				stt++;
				gotoxy(19 + (stt%10)*10,44);
				cout << muitenlen;
				Tree ch = TimKiemCauHoi(dsch.DSCH,dsdt.DS_CTDT[i].bode[stt]);
				if(dsdt.DS_CTDT[i].dapan[stt] == 1)
				{
					da = "A";
				}
				else if (dsdt.DS_CTDT[i].dapan[stt] == 2)
				{
					da = "B";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 3)
				{
					da = "C";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 4)
				{
					da = "D";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 0)
				{
					da = "";
				}
				InCH_DASV(ch,da);
				gotoxy(5,1);
				cout << "       ";
				gotoxy(5,1);
				cout << "CAU " << stt + 1;
			} 
		}
		if(s == PAGEUP && check == false)
		{
			if(stt > 9)
			{
				page--;
				XoaDA();
				VeKhungDA(page,dsdt.DS_CTDT[i].sct,dsdt.DS_CTDT[i]);
				gotoxy(19 + (stt%10)*10,44);
				cout << " ";
				stt -= 10;
				gotoxy(19 + (stt%10)*10,44);
				cout << muitenlen;
				Tree ch = TimKiemCauHoi(dsch.DSCH,dsdt.DS_CTDT[i].bode[stt]);
				if(dsdt.DS_CTDT[i].dapan[stt] == 1)
				{
					da = "A";
				}
				else if (dsdt.DS_CTDT[i].dapan[stt] == 2)
				{
					da = "B";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 3)
				{
					da = "C";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 4)
				{
					da = "D";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 0)
				{
					da = "";
				}
				InCH_DASV(ch,da);
				gotoxy(5,1);
				cout << "       ";
				gotoxy(5,1);
				cout << "CAU " << stt + 1;
			}
			else
			{
				gotoxy(19 + (stt%10)*10,44);
				cout << " ";
				stt = 0;
				gotoxy(19 + (stt%10)*10,44);
				cout << muitenlen;
				Tree ch = TimKiemCauHoi(dsch.DSCH,dsdt.DS_CTDT[i].bode[stt]);
				if(dsdt.DS_CTDT[i].dapan[stt] == 1)
				{
					da = "A";
				}
				else if (dsdt.DS_CTDT[i].dapan[stt] == 2)
				{
					da = "B";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 3)
				{
					da = "C";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 4)
				{
					da = "D";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 0)
				{
					da = "";
				}
				InCH_DASV(ch,da);
				gotoxy(5,1);
				cout << "       ";
				gotoxy(5,1);
				cout << "CAU " << stt + 1;
			}
		}
		if(s == PAGEDOWN && check == false)
		{
			if(stt < max - 10)
			{
				page++;
				XoaDA();
				VeKhungDA(page,dsdt.DS_CTDT[i].sct,dsdt.DS_CTDT[i]);
				gotoxy(19 + (stt%10)*10,44);
				cout << " ";
				stt += 10;
				gotoxy(19 + (stt%10)*10,44);
				cout << muitenlen;
				Tree ch = TimKiemCauHoi(dsch.DSCH,dsdt.DS_CTDT[i].bode[stt]);
				if(dsdt.DS_CTDT[i].dapan[stt] == 1)
				{
					da = "A";
				}
				else if (dsdt.DS_CTDT[i].dapan[stt] == 2)
				{
					da = "B";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 3)
				{
					da = "C";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 4)
				{
					da = "D";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 0)
				{
					da = "";
				}
				InCH_DASV(ch,da);
				gotoxy(5,1);
				cout << "       ";
				gotoxy(5,1);
				cout << "CAU " << stt + 1;	
			}
			else
			{
				if((max - 1)/10 > stt/10)
				{
					page++;
					XoaDA();
					VeKhungDA(page,dsdt.DS_CTDT[i].sct,dsdt.DS_CTDT[i]); 
				}
				gotoxy(19 + (stt%10)*10,44);
				cout << " ";
				stt = max - 1;
				gotoxy(19 + (stt%10)*10,44);
				cout << muitenlen;
				Tree ch = TimKiemCauHoi(dsch.DSCH,dsdt.DS_CTDT[i].bode[stt]);
				if(dsdt.DS_CTDT[i].dapan[stt] == 1)
				{
					da = "A";
				}
				else if (dsdt.DS_CTDT[i].dapan[stt] ==  2)
				{
					da = "B";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 3)
				{
					da = "C";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 4)
				{
					da = "D";
				}
				else if(dsdt.DS_CTDT[i].dapan[stt] == 0)
				{
					da = "";
				}
				InCH_DASV(ch,da);
				gotoxy(5,1);
				cout << "       ";
				gotoxy(5,1);
				cout << "CAU " << stt + 1;
			}
		}
		batphim(s,check);
	}
}

// ==================== IN BANG DIEM THI TN 1 MH CUA SV ==========================
void InBangDiemSV (NODESV *sv, int page, DSCH dsch, NodeMon* m, DSDT dsdt)
{
	int maxpage;
	int slt = sv->ds_Diem.SLDiem;
	if(slt <= 10)	maxpage = 0;
	else if(slt > 10 && slt % 10 == 0)	maxpage = (slt/10) - 1;
	else maxpage = slt/10;
	NODEDIEMTHI *p = sv->ds_Diem.pHead;
	if(page > 0)
	{
		for (int i=0; i < page*10; i++)
			if (p->pNext != NULL)	p = p->pNext;	
	}
	int dem = 1;
	int k = 0;
	for(int i = 0; i < 10; i++)
	{
		if(p->pNext != NULL)
		{
			if(p->MAMH.compare(m.MAMH) == 0)
			{
				gotoxy(20,6+k);
				cout << dem;
//				gotoxy(50,6+k);
				for(int j = 0; j < dsdt.SLDSDT; j++)
				{
					if(dsdt.DS_CTDT[j].MASV.compare(sv->MASV) == 0)
					{
						if(p->DIEM == dsdt.DS_CTDT[j].DIEM && dsdt.DS_CTDT[j].MAMH.compare(p->MAMH)==0)
						{
							gotoxy(50,6+k);
							cout << dsdt.DS_CTDT[j].sct;
							gotoxy(80,6+k);
							cout << dsdt.DS_CTDT[j].tg;
							break;
						}
					}
				}
				
				gotoxy(109,6+k);
				cout << p->DIEM;
				dem ++;
				k += 3;
			}
			p = p->pNext;
		}
		else
		{
			if(p->MAMH.compare(m.MAMH) == 0)
			{
				gotoxy(20,6+k);
				cout << dem;
//				gotoxy(50,6+k);
				for(int j = 0; j < dsdt.SLDSDT; j++)
				{
					if(dsdt.DS_CTDT[j].MASV.compare(sv->MASV) == 0)
					{
						if(p->DIEM == dsdt.DS_CTDT[j].DIEM && dsdt.DS_CTDT[j].MAMH.compare(p->MAMH) == 0)
						{
							gotoxy(50,6+k);
							cout << dsdt.DS_CTDT[j].sct;
							gotoxy(80,6+k);
							cout << dsdt.DS_CTDT[j].tg;
							break;
						}
					}
				}
				gotoxy(109,6+k);
				cout << p->DIEM;
				dem ++;
				k += 3;
			}
			break;
		}
	}
	gotoxy(62,37);
	cout << "Trang" << page + 1 << "/" << maxpage + 1;
}
// ==================== XEM BANG DIEM THI TN 1 MH CUA SV ==========================
void XemBangDiemSV(NODESV *k, DSCH dsch,  NodeMon* m, DSDT dsdt)
{
	system("cls");
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat	UP/DOWN: Len Xuong";
	gotoxy(126,2);
	veKhung(11,40);
	gotoxy(128,4);
	cout << "MSSV: ";
	gotoxy(134,4);
	cout << k->MASV;
	gotoxy(128,7);
	cout << "HO VA TEN: ";
	gotoxy(139,7);
	cout << k->HO << " " << k->TEN;
	gotoxy(128,10);
	cout << "GIOI TINH: ";
	gotoxy(139,10);
	cout << k->PHAI;
	gotoxy(5,2);
	vekhungDS(34,120,4);
	gotoxy(17,3);
	cout << "LAN THI";
	gotoxy(46,3);
	cout << "SO CAU THI";
	gotoxy(76,3);
	cout << "THOI GIAN";
	gotoxy(108,3);
	cout << "DIEM";
	int state = 0;
	int maxpage;
	int page = 0;
	InBangDiemSV(k,page,dsch,m,dsdt);
	int slt = k->ds_Diem.SLDiem;
	char s;
	bool check;
	gotoxy(7,6);
	cout << muiten;
	batphim(s, check);
	while(s != ESC)
	{
		if(slt <= 10)	maxpage = 0;
		else if(slt % 10 == 0)	maxpage = slt/10 -1;
		else maxpage = slt/10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                             ";
						gotoxy(36,6+i);
						cout << "                             ";
						gotoxy(66,6+i);
						cout << "                             ";
						gotoxy(96,6+i);
						cout << "                            ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InBangDiemSV(k,page,dsch,m,dsdt);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				NODEDIEMTHI *p = k->ds_Diem.pHead;
				int i = 0;
				while(p->pNext != NULL)
				{
						if(p->MAMH.compare(m.MAMH) == 0)	i++;
						if(i == (page + 1)*10)	break;
						p = p->pNext;
				}
				while(p->pNext != NULL)
				{
					p = p->pNext;
					if(p->MAMH.compare(m.MAMH) == 0)
					{
						gotoxy(wherex()-1,wherey());
						cout << " ";
						if(page < maxpage)
						{
							for(int i = 0; i < 28;i++)
							{
								gotoxy(6,6+i);
								cout << "                             ";
								gotoxy(36,6+i);
								cout << "                             ";
								gotoxy(66,6+i);
								cout << "                             ";
								gotoxy(96,6+i);
								cout << "                            ";
							}
						}
						page++;
						InBangDiemSV(k,page,dsch,m,dsdt);
						state = 0;
						gotoxy(7,6);
						cout << muiten;
						break;
					}				
				}
			}
			else
			{
				NODEDIEMTHI *p = k->ds_Diem.pHead;
				int i = 0;
				while(p->pNext != NULL)
				{
						if(p->MAMH.compare(m.MAMH) == 0)	i++;
						if(i == state + page*10 + 1)	break;
						p = p->pNext;
				}
				while(p->pNext != NULL)
				{
					p = p->pNext;
					if(p->MAMH.compare(m.MAMH) == 0)
					{
						gotoxy(wherex()-1,wherey());
						cout << " ";
						state ++;
						gotoxy(7,wherey() + 3);
						cout << muiten;
						break;
					}
				}
				if(p->pNext == NULL) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                             ";
					gotoxy(36,6+i);
					cout << "                             ";
					gotoxy(66,6+i);
					cout << "                             ";
					gotoxy(96,6+i);
					cout << "                            ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InBangDiemSV(k,page,dsch,m,dsdt);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                             ";
					gotoxy(36,6+i);
					cout << "                             ";
					gotoxy(66,6+i);
					cout << "                             ";
					gotoxy(96,6+i);
					cout << "                            ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InBangDiemSV(k,page,dsch,m,dsdt);
				gotoxy(8,6);
			}
		}
		if (s == ENTER)
		{
			NODEDIEMTHI *p = k->ds_Diem.pHead;
			int i =0;
			while(p->pNext != NULL)
			{
					if(p->MAMH.compare(m.MAMH) == 0)	i++;
					if(i == state + page*10 +1) break;
					p = p->pNext;
			}
			InChiTiet1LanThi(p,dsch,k,dsdt);
		}
		batphim(s,check);
	}
}
// ==================== IN DANH SACH DIEM THEO MH ==========================
void InDSDiemMH (LOP *l, int page,  NodeMon* m, DSCH dsch)
{
	if (l->ds_SV.pHead == NULL)
	{
		return;
	}
	int k = 2;
	int sl = l->ds_SV.SLSV;
	int maxpage;
	if(sl <= 10)	maxpage = 0;
	else if (sl % 10 == 0)	maxpage = sl/10 - 1;
	else maxpage = sl/10;
	NODESV *j = l->ds_SV.pHead;
	if(page > 0)
	{
		for (int i = 0; i < page*10; i++)
			if (j->pNext != NULL)	j = j->pNext;
	}
	
	NODEDIEMTHI *p = new NODEDIEMTHI;
	for(int i = 0; i < 10; i++)
	{
		p = j->ds_Diem.pHead;
		int slt = 0;
		if (j->pNext != NULL) //j khong cuoi 
		{
			gotoxy(12,4+k);
			cout << j->MASV;
			gotoxy(32,4+k);
			cout << j->HO << " " << j->TEN;
			if(p == NULL) //j chua thi
			{	
				gotoxy(109,4+k);
				cout << "CHUA THI";
			}
			else //j co thi
			{
				while(p != NULL) //tim slt cua mon
				{
					if(p->MAMH.compare(m.MAMH) == 0)
					{
						slt++;
					}
					p = p->pNext;
				}
				if(slt == 0) //neu chua thi mon
				{
					gotoxy(109,4+k);
					cout << "CHUA THI";
				}
				else //neu co thi mon
				{
					gotoxy(113,4+k);
					cout << slt;
				}
			}
			k += 3;
			j = j->pNext;
		}
		else //j la cuoi
		{
			gotoxy(12,4+k);
			cout << j->MASV;
			gotoxy(32,4+k);
			cout << j->HO << " " << j->TEN;
			if(p == NULL)
			{	
				gotoxy(109,4+k);
				cout << "CHUA THI";
			}
			else //j co thi
			{
				while(p != NULL) //tim slt cua mon
				{
					if(p->MAMH.compare(m.MAMH) == 0)
					{
						slt++;
					}
					p = p->pNext;
				}
				if(slt == 0) //neu chua thi mon
				{
					gotoxy(109,4+k);
					cout << "CHUA THI";
				}
				else //neu co thi mon
				{
					gotoxy(113,4+k);
					cout << slt;
				}
			}
			k += 3;
			break;
		}
	}
	gotoxy(125/2,36);
	cout << "Trang " << page + 1 << "/" << maxpage + 1;
}
// ==================== XEM DIEM ==========================
void XemDiem1Lop(LOP *l,  NodeMon* m, DSCH dsch, DSDT dsdt)
{
	AnConTro();
	system("cls");
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat	UP/DOWN: Len Xuong";
	gotoxy(10,1);
	cout << "Diem mon : " << m.TENMH;
	gotoxy(105,1);
	cout << "Lop : " << l->MALOP;
	gotoxy(5,2);
	VeKhungDSLop1(34,120,10);
	gotoxy(130,26);
	vekhungTB(10,36);
	int page = 0;
	gotoxy(15,3);
	cout << "MA SV";
	gotoxy(60,3);
	cout << "HO VA TEN";
	gotoxy(108,3);
	cout << "SO LAN THI";
	InDSDiemMH(l,page,m,dsch);
	int maxpage;
	int state = 0;
	char s;
	bool check;
	gotoxy(7,6);
	cout << muiten;
	batphim(s,check);
	while(s != ESC)
	{
		if(l->ds_SV.SLSV % 10 == 0)	maxpage = l->ds_SV.SLSV/10 - 1;
		else maxpage = l->ds_SV.SLSV/10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(79,6+i);
						cout << "                     ";
						gotoxy(103,6+i);
						cout << "                     ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSDiemMH(l,page,m, dsch);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				NODESV *k= l->ds_SV.pHead;
				for(int i=0; i< state + page*10; i++)
					if (k->pNext != NULL)	k = k->pNext;
				if(k->pNext != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(79,6+i);
						cout << "                     ";
						gotoxy(103,6+i);
						cout << "                     ";
					}
					page++;
					InDSDiemMH(l,page,m, dsch);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				NODESV *k= l->ds_SV.pHead;
				for(int i=0; i< state + page*10; i++)
					if (k->pNext != NULL)	k = k->pNext;
				if(k->pNext != NULL)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				else 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(79,6+i);
						cout << "                     ";
						gotoxy(103,6+i);
						cout << "                     ";
					}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSDiemMH(l,page,m, dsch);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                      ";
						gotoxy(31,6+i);
						cout << "                                             ";
						gotoxy(79,6+i);
						cout << "                     ";
						gotoxy(103,6+i);
						cout << "                     ";
					}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSDiemMH(l,page,m, dsch);
				gotoxy(8,6);
			}
		}
		if(s == ENTER)
		{
			//XEM BANG DIEM SINH VIEN
			NODESV *k = l->ds_SV.pHead;
			for (int i = 0; i < state + page*10; i++)
				if (k->pNext != NULL)	k = k->pNext;
			if(k->ds_Diem.pHead == NULL)
			{
				gotoxy(wherex()-1,wherey());
				cout << " ";
				string tb = "Sinh vien chua thi lan nao";
				InTB(tb,132,30);
				AnConTro();
				Sleep(750);
				XoaTB(130,26);
				gotoxy(7,6);
				cout << muiten;
				state = 0;
			}
			else
			{
				//In chi tiet bang diem cua 1 sinh vien
				if(CheckSLThi(k->ds_Diem,m.MAMH) == false)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					string tb = "Sinh vien chua thi lan nao";
					InTB(tb,132,30);
					AnConTro();
					Sleep(750);
					XoaTB(130,26);
					gotoxy(7,6);
					cout << muiten;
					state = 0;
				}
				else
				{
					XemBangDiemSV(k,dsch,m,dsdt);
					system("cls");
					gotoxy(50,46);
					cout << "ENTER: Chon	ESC: Thoat	UP/DOWN: Len Xuong";
					gotoxy(10,1);
					cout << "Diem mon : " << m.TENMH;
					gotoxy(105,1);
					cout << "Lop : " << l->MALOP;
					gotoxy(5,2);
					VeKhungDSLop1(34,120,10);
					gotoxy(130,26);
					vekhungTB(10,36);
					int page = 0;
					gotoxy(15,3);
					cout << "MA SV";
					gotoxy(60,3);
					cout << "HO VA TEN";
					gotoxy(108,3);
					cout << "SO LAN THI";
					InDSDiemMH(l,page,m,dsch);
					gotoxy(7,6);
					cout << muiten;
					state = 0;
				}
			}
		}
	batphim(s,check);
	}
}

// ==================== NHAP MON XEM DIEM ==========================
void NhapMonXemDiem(LOP *l, TreeMH root, DSCH dsch, DSDT dsdt)
{
	if( == 0)
	{
		string tb = "Danh sach mon hien tai dang trong";
		InTB(tb,132,30);
		AnConTro();
		Sleep(850);
		XoaTB(130,26);
		return;
	}
	gotoxy(5,2);
	vekhungDS(34,120,2);
	gotoxy(30,3);
	cout << "MA MON HOC";
	gotoxy(90,3);
	cout << "TEN MON HOC";
	int page = 0;
	int maxpage;
	InDSMon(root,page);
	gotoxy(130,26);
	vekhungTB(10,36);
	char s;
	int state = 0;
	bool check;
	string tb = "Vui long chon 1 mon hoc de xem diem";
	InTB(tb,132,30);
	AnConTro();
	gotoxy(7,6);
	cout << muiten;
	batphim(s,check);
	while (s != ESC)
	{
		if( <= 10)	maxpage = 0;
		else if( % 10 == 0) 	maxpage = /10 -1;
		else maxpage = /10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSMon(root,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				if( > (state + page*10 + 1))
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 28;i++)
					{
						gotoxy(6,6+i);
						cout << "                                                          ";
						gotoxy(66,6+i);
						cout << "                                                          ";
					}
					page++;
					InDSMon(root,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if( > (state + page*10 + 1))
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if( == state + page*10 + 1) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                                          ";
					gotoxy(66,6+i);
					cout << "                                                          ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSMon(root,page);
				gotoxy(8,6);
			}
		}
		if (s == ENTER)
		{
			XemDiem1Lop(l, *getMonTheoThuTu(root, state + page*10), dsch, dsdt);// da sua
			system("cls");
			gotoxy(50,46);
			cout << "ENTER: Chon	ESC: Thoat	 PGUP: Qua trang		PGDOWN: Lui trang";
			gotoxy(5,2);
			vekhungDS(34,120,2);
			gotoxy(30,3);
			cout << "MA MON HOC";
			gotoxy(90,3);
			cout << "TEN MON HOC";
			InDSMon(root,page);
			state = 0;
			gotoxy(130,26);
			vekhungTB(10,36);
			tb = "Vui long chon 1 mon hoc de xem diem";
			InTB(tb,132,30);
			gotoxy(7,6);
			cout << muiten;
		}
		batphim(s,check);
	}
	for(int i = 0; i < 10; i++)
	{
		gotoxy(7,6+i*3);
		cout << " ";
	}
}

// ==================== NHAP LOP  ==========================
void NhapLopXemDiem(DSLOP dsl, TreeMH root, DSCH dsch, DSDT dsdt)
{
	system("cls");
	gotoxy(130,26);
	vekhungTB(10,36);
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat	 PGUP: Qua trang		PGDOWN: Lui trang	  UP: Len 	   DOWN: Xuong";
	gotoxy(5,2);
	vekhungDS(34,120,2);
	gotoxy(32,3);
	cout << "TEN LOP";
	gotoxy(93,3);
	cout << "MA LOP";
	int page = 0;
	int maxpage;
	InDSLop(dsl,page);
	char s;
	int state = 0;
	bool check;
	gotoxy(7,6);
	cout << muiten;
	batphim(s,check);
	while (s != ESC)
	{
		if(dsl.SLLOP <= 10)	maxpage = 0;
		else if(dsl.SLLOP % 10 == 0)	maxpage = dsl.SLLOP/10 -1;
		else maxpage = dsl.SLLOP/10;
		if(s == UP && check == false)
		{
			if(page == 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey() - 3);
					cout << muiten;
				}
			}
			if(page > 0)
			{
				if(state > 0)
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state --;
					gotoxy(7,wherey()-3);
					cout << muiten;
				}
				else if(state == 0)
				{
					for(int i = 0; i < 29;i++)
					{
						gotoxy(6,6+i);
						cout << "                                              ";
						gotoxy(66,6+i);
						cout << "                                              ";
					}
					gotoxy(wherex()-1,wherey());
					cout << " ";
					page --;
					InDSLop(dsl,page);
					gotoxy(7,33);
					cout << muiten;
					state = 9;	
				}
			}
		}
		if(s == DOWN && check == false)
		{
			if(state == 9)
			{
				if(dsl.SLLOP > (state + page*10 + 1))
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					for(int i = 0; i < 29;i++)
					{
						gotoxy(6,6+i);
						cout << "                                              ";
						gotoxy(66,6+i);
						cout << "                                              ";
					}
					page++;
					InDSLop(dsl,page);
					state = 0;
					gotoxy(7,6);
					cout << muiten;
				}
			}
			else
			{
				if(dsl.SLLOP > (state + page*10 + 1))
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					state ++;
					gotoxy(7,wherey() + 3);
					cout << muiten;	
				}
				if(dsl.SLLOP == (state + page*10 + 1)) 
				{
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(7,wherey());
					cout << muiten;
				}
			}
		}	
		if (s == PAGEDOWN && check == false)
		{
			AnConTro();
			if(page < maxpage)
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                              ";
					gotoxy(66,6+i);
					cout << "                                              ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page ++;
				InDSLop(dsl,page);
				gotoxy(8,6);
			}
		}
		if(s == PAGEUP && check == false)
		{
			AnConTro();
			if (page > 0 )
			{
				for(int i = 0; i < 28;i++)
				{
					gotoxy(6,6+i);
					cout << "                                              ";
					gotoxy(66,6+i);
					cout << "                                              ";
				}
				gotoxy(wherex()-1,wherey());
				cout << " ";
				gotoxy(7,6);
				cout << muiten;
				state = 0;
				page--;
				InDSLop(dsl,page);
				gotoxy(8,6);
			}
		}
		if (s == ENTER)
		{
			if(dsl.DS_LOP[state + page*10]->ds_SV.pHead == NULL)
			{
				string tb = "Lop khong co sinh vien khong the xem diem !";
				InTB(tb,132,30);
				AnConTro();
				Sleep(850);
				XoaTB(130,26);
				gotoxy(7,6 + state*3);
				cout << " ";
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			else
			{
				NhapMonXemDiem(dsl.DS_LOP[state + page*10], root, dsch, dsdt);
				system("cls");
				gotoxy(50,46);
				cout << "ENTER: Chon	ESC: Thoat	 PGUP: Qua trang		PGDOWN: Lui trang";
				gotoxy(130,26);
				vekhungTB(10,36);
				gotoxy(5,2);
				vekhungDS(34,120,2);
				gotoxy(32,3);
				cout << "TEN LOP";
				gotoxy(93,3);
				cout << "MA LOP";
				InDSLop(dsl,page);
				state = 0;
				gotoxy(7,6);
				cout << muiten;
			}
			
		}
	batphim(s,check);
	}
}
// ==================== FUNCTION DIEM ==========================
void FunctionDiem(DSLOP dsl, TreeMH root, DSCH dsch, DSDT dsdt)
{
	int page = 0;
	gotoxy(130,26);
	vekhungTB(10,36);
	string tb;
	if(dsl.SLLOP == 0)
	{
		string tb = "Danh sach lop hien tai dang trong";
		InTB(tb,132,30);
		AnConTro();
		Sleep(750);
		XoaTB(130,26);
	}
	else
	{
		NhapLopXemDiem(dsl,root,dsch,dsdt);
	}
}

void DocFileDSLop(DSLOP &dsl)
{
	ifstream f;
	f.open("DS_LOP.txt", ios::in);
	if(f.fail())
	{
		cout << "Mo FILE THAT BAI";
	}
	else
	{
		f >> dsl.SLLOP;
		f.ignore();
		for(int i =0; i< dsl.SLLOP; i++)
		{
			LOP *l = new LOP;
			getline(f, l->MALOP, ',');
			getline(f, l->TENLOP);
			f >> l->ds_SV.SLSV;
			f.ignore();
			for(int j = 0; j < l->ds_SV.SLSV; j++)
			{
				NODESV *p = new NODESV;
				getline(f, p->MASV, ',');
				getline(f, p->HO, ',');
				getline(f, p->TEN, ',');
				getline(f, p->PHAI, ',');
				getline(f, p->PASSWORD, '\n');
				p->pNext = NULL;
				f >> p->ds_Diem.SLDiem;
				f.ignore();
				if(p->ds_Diem.SLDiem > 0)
				{
					for(int k = 0; k < p->ds_Diem.SLDiem; k++)
					{
						NODEDIEMTHI *d = new NODEDIEMTHI;
						getline(f, d->MAMH, ':');
						d->pNext = NULL;
						f >> d->DIEM;
						f.ignore();
						if(p->ds_Diem.pHead == NULL)	p->ds_Diem.pHead = p->ds_Diem.pLast = d;
						else
						{
							p->ds_Diem.pLast->pNext = d;
							p->ds_Diem.pLast = d;	
						}	
					}
				}
				if(l->ds_SV.pHead == NULL)	l->ds_SV.pHead = l->ds_SV.pLast = p;
				else
				{
					if(TachMSSV(p->MASV) < TachMSSV(l->ds_SV.pHead->MASV))
					{
						p->pNext = l->ds_SV.pHead;
						l->ds_SV.pHead = p;
					}
					else
					{
						NODESV *r = l->ds_SV.pHead;
						while(r->pNext != NULL && TachMSSV(r->pNext->MASV) < TachMSSV(p->MASV))
							r = r->pNext;
						p->pNext = r->pNext;
						r->pNext = p;
					}
				}
			}
			dsl.DS_LOP[i] = l;
		}
	}
	f.close();
}
//      GHI FILE
void GhiFileDSLop(DSLOP dsl)
{
	ofstream f;
	f.open("DS_LOP.txt", ios::out);
	f << dsl.SLLOP << endl;
	for(int i = 0; i < dsl.SLLOP; i++)
	{
		f << dsl.DS_LOP[i]->MALOP << ",";
		f << dsl.DS_LOP[i]->TENLOP << endl;
		f << dsl.DS_LOP[i]->ds_SV.SLSV << endl;
		for(NODESV *p = dsl.DS_LOP[i]->ds_SV.pHead; p != NULL; p = p->pNext)
		{
			f << p->MASV <<",";
			f << p->HO << ",";
			f << p->TEN << ",";
			f << p->PHAI <<",";
			f << p->PASSWORD << endl;
			f << p->ds_Diem.SLDiem << endl;
			if(p->ds_Diem.SLDiem > 0)
			{
				for(NODEDIEMTHI *j = p->ds_Diem.pHead; j != NULL; j = j->pNext)
				{
					f << j->MAMH << ":";
					f << j->DIEM << endl;
				}
			}
			else
			{
				continue;
			}
		} 
	}
	f.close();
}

void DocFileDSDiem(DSDT &dsdt)
{
	ifstream f;
	f.open("DS_DIEMTHI.txt", ios::in);
	if(f.fail())
	{
		gotoxy(50,50);
		cout << "Mo file Khong thanh cong";
		return;	
	}
	else
	{
		f >> dsdt.SLDSDT;
		f.ignore();
		for(int i = 0; i < dsdt.SLDSDT; i++)
		{
			getline(f, dsdt.DS_CTDT[i].MASV, ',');
			getline(f, dsdt.DS_CTDT[i].MAMH,'\n');
			f >> dsdt.DS_CTDT[i].DIEM;
			f >> dsdt.DS_CTDT[i].sct;
			f >> dsdt.DS_CTDT[i].tg;
			dsdt.DS_CTDT[i].bode = new int [dsdt.DS_CTDT[i].sct];
			dsdt.DS_CTDT[i].dapan = new int [dsdt.DS_CTDT[i].sct];
			for(int j = 0; j < dsdt.DS_CTDT[i].sct; j++)
			{
				f >> dsdt.DS_CTDT[i].bode[j];
				f >> dsdt.DS_CTDT[i].dapan[j];
			}
			f.ignore();	
		}	
	}
	f.close();	
}

void GhiFileDSDiem(DSDT dsdt)
{
	ofstream f;
	f.open("DS_DIEMTHI.txt", ios::out);
	f << dsdt.SLDSDT << endl;
	for(int i = 0; i < dsdt.SLDSDT; i++)
	{
		f << dsdt.DS_CTDT[i].MASV << ",";
		f << dsdt.DS_CTDT[i].MAMH << endl;
		f << dsdt.DS_CTDT[i].DIEM << " ";
		f << dsdt.DS_CTDT[i].sct << " ";
		f << dsdt.DS_CTDT[i].tg << " ";
		for(int j = 0; j < dsdt.DS_CTDT[i].sct; j++)
		{
			if(j == dsdt.DS_CTDT[i].sct - 1)
			{
				f << dsdt.DS_CTDT[i].bode[j] << " ";
				f << dsdt.DS_CTDT[i].dapan[j] << endl;
				break;
			}
			f << dsdt.DS_CTDT[i].bode[j] << " ";
			f << dsdt.DS_CTDT[i].dapan[j] << " ";
		}
	}
	f.close();
}

void DocFileDSMH(TreeMH &root) {
    ifstream f("DS_MonHoc.txt");
    if (!f.is_open()) {
        cout << "Khong mo duoc file DS_MonHoc.txt\n";  // da sua mon hoc
        return;
    }

    string mamh, tenmh;
    while (getline(f, mamh)) {
        if (mamh == "") break; // tránh dòng trống cuối file
        getline(f, tenmh);
        NodeMon* mon = TaoNodeMon(mamh, tenmh);
        ChenMonHoc(root, mon);
    }

    f.close();
    cout << "Doc file DS_MonHoc hoan tat!\n";
}

void GhiFileDSMH(TreeMH root) {
    ofstream f("DS_MonHoc.txt");
    if (!f.is_open()) {
        cout << "Khong ghi duoc file DS_MonHoc.txt\n";   // đã sửa môn học
        return;
    }

    // Hàm đệ quy duyệt cây và ghi từng môn
    function<void(NodeMon*)> GhiCay = [&](NodeMon* node) {
        if (node == nullptr) return;
        GhiCay(node->pLeft);
        f << node->MAMH << "\n";
        f << node->TENMH << "\n";
        GhiCay(node->pRight);
    };

    GhiCay(root);
    f.close();
}

void DocFileCauHoi(DSCH &dsch)
{
	fstream f;
	f.open("DS_CauHoi.txt", ios::in);
	if(f.fail())
	{
		cout << "Khong mo dc file.";
		return;
	}
	while(!f.eof())
	{
		CauHoi *x = KhoiTaoCauHoi();
		f >> x->ID;
		f.ignore();
		getline(f, x->MAMH,'\n');
		if(x->MAMH=="") break;
		getline(f, x->NOIDUNG,'\n');
		getline(f, x->A,'\n');
		getline(f, x->B,'\n');
		getline(f, x->C,'\n');
		getline(f, x->D,'\n');
		getline(f, x->DA,'\n');
		Them1CauHoi(dsch.DSCH, x);
		dsch.SLCH++;
	//	delete x;
	}
	f.close();
}

void GhiFileCauHoi(DSCH dsch)
{
	ofstream f("DS_CauHoi.txt", ios::out);
    if (!f.is_open()) {
        cout << "Khong ghi duoc file DS_CauHoi.txt\n";// đã sửa bỏ stack 
        return;
    }

    CauHoiNode p = dsch.pHead;
    while (p != nullptr) {
        f << p->ID << endl;
        f << p->MAMH << endl;
        f << p->NOIDUNG << endl;
        f << p->A << endl;
        f << p->B << endl;
        f << p->C << endl;
        f << p->D << endl;
        f << p->DA << endl;

        p = p->pNext;
    }

    f.close();
	return;
}

void SapXepDSLOP(DSLOP &dsl)
{
	int i, j, min_id;
	for(i = 0; i < dsl.SLLOP - 1; i++)
	{
		min_id = i;
		for(j = i+1; j < dsl.SLLOP; j++)
			if(SoSanhMa(dsl.DS_LOP[j]->MALOP,dsl.DS_LOP[min_id]->MALOP) == 1)
				min_id = j;	 
		LOP l;
		l = *dsl.DS_LOP[i];
		*dsl.DS_LOP[i] = *dsl.DS_LOP[min_id];
		*dsl.DS_LOP[min_id] = l;
	}
}

void SapXepDSMonHoc(TreeMH &root)   //đã sửa lại kiểu sắp xếp cho khớp cây avl
{
    if (root == NULL) return;

    // Đếm số môn trong cây
    int count = 0;
    function<void(TreeMH)> DemNode = [&](TreeMH t){
        if (t == NULL) return;
        count++;
        DemNode(t->pLeft);
        DemNode(t->pRight);
    };
    DemNode(root);

    // Sắp xếp kiểu selection sort dựa vào getMonTheoThuTu
    for (int i = 0; i < count - 1; i++) {
        int min_id = i;
        for (int j = i + 1; j < count; j++) {
            int idx_i = 0, idx_j = 0;
            NodeMon* mon_i = getMonTheoThuTu(root, idx_i, i);
            NodeMon* mon_j = getMonTheoThuTu(root, idx_j, j);

            if (mon_i == NULL || mon_j == NULL) continue;

            if (mon_j->MAMH < mon_i->MAMH)
                min_id = j;
        }

        if (min_id != i) {
            int idx_i = 0, idx_min = 0;
            NodeMon* mon_i = getMonTheoThuTu(root, idx_i, i);
            NodeMon* mon_min = getMonTheoThuTu(root, idx_min, min_id);

            if (mon_i != NULL && mon_min != NULL) {
                swap(mon_i->MAMH, mon_min->MAMH);
                swap(mon_i->TENMH, mon_min->TENMH);
                swap(mon_i->ds_cauhoi, mon_min->ds_cauhoi);
            }
        }
    }
}


void SapXepDSDiemThi(DSDT &dsdt)
{
	int i, j, min_id;
	for(i = 0; i < dsdt.SLDSDT - 1; i++)
	{
		min_id = i;
		for(j = i+1; j < dsdt.SLDSDT; j++)
			if(SoSanhMa(dsdt.DS_CTDT[j].MASV,dsdt.DS_CTDT[min_id].MASV) == 1)
				min_id = j;	 
		CTDT ctdt;
		ctdt = dsdt.DS_CTDT[i];
		dsdt.DS_CTDT[i] = dsdt.DS_CTDT[min_id];
		dsdt.DS_CTDT[min_id] = ctdt;
	}
}


void GiaiPhongVungNhoDSLOP(DSLOP &dsl)
{
	for(int i = dsl.SLLOP - 1; i >= 0; i--)
	{
		NODESV *p;
		while(dsl.DS_LOP[i]->ds_SV.pHead != NULL)
		{
			p = dsl.DS_LOP[i]->ds_SV.pHead;
			dsl.DS_LOP[i]->ds_SV.pHead = dsl.DS_LOP[i]->ds_SV.pHead->pNext;
			NODEDIEMTHI *k;
			while(p->ds_Diem.pHead != NULL)
			{
				k = p->ds_Diem.pHead;
				p->ds_Diem.pHead = p->ds_Diem.pHead->pNext;
				delete k;
			}
			delete p;
		}
		delete dsl.DS_LOP[i];	
	} 
}

void GiaiPhongVungNhoDSCH(Tree &t)
{
	if(t == NULL)	return;
	else
	{
		GiaiPhongVungNhoDSCH(t->pLeft);
		GiaiPhongVungNhoDSCH(t->pRight);
		delete t;
	}
}

void GiaiPhongVungNhoDSDT(DSDT &dsdt)
{
	for(int i = dsdt.SLDSDT-1; i >= 0; i--)
	{
		delete []	dsdt.DS_CTDT[i].bode;
		delete []	dsdt.DS_CTDT[i].dapan;
	}
}

//=============================DANG NHAP================================
int DangNhap(DSLOP &dsl, string &masv)
{
	system("cls");
	KhungDangNhap();
	string user;
	string pass;
	InTen();
	char s;
	bool state = false;
	bool check;
	gotoxy(90 + 10,27);
	batphim(s,check);
	while (s != ESC)
	{
		if (s == UP && check == false)
		{
			if (state == true)
			{
				gotoxy(90+10+user.length(),27);
				state = !state;
			}
		}
		if (s == DOWN && check == false)
		{
			if (state == false)
			{
				gotoxy(90+10+pass.length(),31);
				state = !state;
			}
		}
		if (((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9')) && check == true)
		{
			HienConTro();
			if (state == true)
			{
				if (pass.length() < MAXPW)
				{
					SetBGColor(15);
					SetColor(0);
					cout << "*";
					pass += s;
				}
			}
			else
			{
				if (user.length() < MAXMASV)
				{
					SetBGColor(15);
					SetColor(0);
					cout << inhoa(s);
					user += inhoa(s);
				}
			}
		}
		if (s == BACKSPACE)
		{
			if (state == true)
			{
				if (pass.length() > 0)
				{
					SetBGColor(15);
					SetColor(0);
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					pass.erase(pass.length()-1);
				}
			}
			else
			{
				if (user.length() > 0)
				{
					SetBGColor(15);
					SetColor(0);
					AnConTro();
					gotoxy(wherex()-1,wherey());
					cout << " ";
					gotoxy(wherex()-1,wherey());
					HienConTro();
					user.erase(user.length()-1);
				}
			}
		}
		if (s == ENTER)
		{
			// neu user = "GV" va mat khau = "GV" thi return 1 la quyen giang vien
			if((user == "GV" && pass == "GV") || (user == "GV") && (pass == "gv"))
			{
				return 1;
			}
			// Duyet trong dssv kiem tra masv voi mat khau. neu dung thi return 0 la quyen sv
			else
			{	
				for(int i = 0; i < dsl.SLLOP; i++)
				{
					for(NODESV *k = dsl.DS_LOP[i]->ds_SV.pHead; k != NULL; k = k->pNext)
					{
						string x;
						for (int i = 0; i < k->MASV.length(); i++)
						{
							x += inhoa(k->MASV[i]);
						}
						string y = k->PASSWORD;
						if(x == user && y == pass)
						{
							masv = user;
							return 0;
						}
					}
				}
				return 2;
			}
		}
	batphim(s,check);
	}
	return -1;
}

int MainMenuGV()
{
	ChangeColor(15);
	system("cls");
	gotoxy(50,46);
	cout << "ENTER: Chon	ESC: Thoat 	UP/DOWN: LEN XUONG";
	gotoxy(80,10);
	cout << " __   __  _______  __    _  __   __ ";
	gotoxy(80,11);
	cout << "|  |_|  ||       ||  |  | ||  | |  |";
	gotoxy(80,12);
	cout << "|       ||    ___||   |_| ||  | |  |";
	gotoxy(80,13);
	cout << "|       ||   |___ |       ||  |_|  |";
	gotoxy(80,14);
	cout << "|       ||    ___||  _    ||       |";
	gotoxy(80,15);
	cout << "| ||_|| ||   |___ | | |   ||       |";
	gotoxy(80,16);
	cout << "|_|   |_||_______||_|  |__||_______|";
	gotoxy(60,20);
	cout << " _______  ___   _______  __    _  _______    __   __  ___   _______  __    _ ";
	gotoxy(60,21);
	cout << "|       ||   | |   _   ||  |  | ||       |  |  | |  ||   | |       ||  |  | |";
	gotoxy(60,22);
	cout << "|    ___||   | |  |_|  ||   |_| ||    ___|  |  |_|  ||   | |    ___||   |_| |";
	gotoxy(60,23);
	cout << "|   | __ |   | |       ||       ||   | __   |       ||   | |   |___ |       |";
	gotoxy(60,24);
	cout << "|   ||  ||   | |       ||  _    ||   ||  |  |       ||   | |    ___||  _    |";
	gotoxy(60,25);
	cout << "|   |_| ||   | |   _   || | |   ||   |_| |   |     | |   | |   |___ | | |   |";
	gotoxy(60,26);
	cout << "|_______||___| |__| |__||_|  |__||_______|    |___|  |___| |_______||_|  |__|";
	veNutMenu(3,10,6,"Lop",240);
	veNutMenu(3,10,11,"Sinh vien",31);
	veNutMenu(3,10,16,"Mon hoc",31);
	veNutMenu(3,10,21,"Cau hoi",31);
	veNutMenu(3,10,26,"Diem",31);
	gotoxy(50,5);
	AnConTro();
	int choose = 0;
	char s;
	bool check;
	batphim(s,check);
	while(1)
	{
		if (s == ESC)
		{
			if (Exit(s,check) == true)
			{
				return -1;
			}
			else 
			{
				system("cls");
				gotoxy(50,46);
				cout << "ENTER: Chon	ESC: Thoat";
				gotoxy(80,10);
				cout << " __   __  _______  __    _  __   __ ";
				gotoxy(80,11);
				cout << "|  |_|  ||       ||  |  | ||  | |  |";
				gotoxy(80,12);
				cout << "|       ||    ___||   |_| ||  | |  |";
				gotoxy(80,13);
				cout << "|       ||   |___ |       ||  |_|  |";
				gotoxy(80,14);
				cout << "|       ||    ___||  _    ||       |";
				gotoxy(80,15);
				cout << "| ||_|| ||   |___ | | |   ||       |";
				gotoxy(80,16);
				cout << "|_|   |_||_______||_|  |__||_______|";
				gotoxy(60,20);
				cout << " _______  ___   _______  __    _  _______    __   __  ___   _______  __    _ ";
				gotoxy(60,21);
				cout << "|       ||   | |   _   ||  |  | ||       |  |  | |  ||   | |       ||  |  | |";
				gotoxy(60,22);
				cout << "|    ___||   | |  |_|  ||   |_| ||    ___|  |  |_|  ||   | |    ___||   |_| |";
				gotoxy(60,23);
				cout << "|   | __ |   | |       ||       ||   | __   |       ||   | |   |___ |       |";
				gotoxy(60,24);
				cout << "|   ||  ||   | |       ||  _    ||   ||  |  |       ||   | |    ___||  _    |";
				gotoxy(60,25);
				cout << "|   |_| ||   | |   _   || | |   ||   |_| |   |     | |   | |   |___ | | |   |";
				gotoxy(60,26);
				cout << "|_______||___| |__| |__||_|  |__||_______|    |___|  |___| |_______||_|  |__|";
				veNutMenu(3,10,6,"Lop",240);
				veNutMenu(3,10,11,"Sinh vien",31);
				veNutMenu(3,10,16,"Mon hoc",31);
				veNutMenu(3,10,21,"Cau hoi",31);
				veNutMenu(3,10,26,"Diem",31);
				choose = 0;
			}
		}
		if (s == UP && check == false )
		{
			if(choose > 0 )
			{
				switch(choose)
				{
					case 1:
						{
							veNutMenu(3,10,6,"Lop",240);
							veNutMenu(3,10,11,"Sinh Vien",31);
							break;
						}
					case 2:
						{
							veNutMenu(3,10,11,"Sinh vien",240);
							veNutMenu(3,10,16,"Mon hoc",31);
							break;
						}
					case 3:
						{
							veNutMenu(3,10,16,"Mon hoc",240);
							veNutMenu(3,10,21,"Cau hoi",31);
							break;
						}
					case 4:
						{
							veNutMenu(3,10,21,"Cau hoi",240);
							veNutMenu(3,10,26,"Diem",31);
							break;
						}	
				}
				choose --;
			}
		}
		if (s == DOWN && check == false )
		{
			if(choose < 4 )
			{
				switch(choose)
				{
					case 0:
						{
							veNutMenu(3,10,6,"Lop",31);
							veNutMenu(3,10,11,"Sinh vien",240);
							break;
						}
					case 1:
						{
							veNutMenu(3,10,11,"Sinh vien",31);
							veNutMenu(3,10,16,"Mon hoc",240);
							break;
						}
					case 2:
						{
							veNutMenu(3,10,16,"Mon hoc",31);
							veNutMenu(3,10,21,"Cau hoi",240);
							break;
						}
					case 3:
						{
							veNutMenu(3,10,21,"Cau hoi",31);
							veNutMenu(3,10,26,"Diem",240);
							break;
						}	
				}
				choose ++;
			}
		}
		if (s == ENTER)
		{
			return choose;
		}
		batphim(s,check);
	}
	return -1;
}

void MainProcess(DSLOP &dsl, NodeMon* &root, DSCH &dsch, DSDT &dsdt, DanhSachID &dsID)
{
    string masv;

    // ======= ĐỌC DỮ LIỆU TỪ FILE =======
    DocFileCauHoi(dsch);
    DocFileDSLop(dsl);
    DocFileDSMH(root);
    DocFileDSDiem(dsdt);

    // ======= SẮP XẾP DỮ LIỆU =======
    SapXepDSLOP(dsl);
    SapXepDSMonHoc(root);
    SapXepDSDiemThi(dsdt);

    fullscreen();

    while (1)
    {
        HienConTro();

        switch (DangNhap(dsl, masv))
        {
        case 0: // === SINH VIÊN THI ===
        {
            SetBGColor(0);
            SetColor(15);
            system("cls");

            int tg = 0, sct = 0;
            string monthi;
            bool check;

            NhapMonThi(root, tg, sct, monthi, check);
            if (!check)
                break;

            int sch = dsch.SLCH;
            if (sct > sch)
            {
                string tb = "Khong the thi, so cau thi vuot qua so cau hoi trong ngan hang de thi";
                InTB(tb, 132, 30);
                AnConTro();
                Sleep(1500);
                XoaTB(130, 26);
                break;
            }

            float diem;
            CTDT ctdt;
            ctdt.MASV = masv;
            ctdt.MAMH = monthi;
            ctdt.bode = new int[sct];
            ctdt.dapan = new int[sct];

            FunctionThi(dsch, tg, sct, monthi, diem, ctdt);
            stop = 1;

            if (ctdt.bode != NULL)
            {
                NODESV *p = nullptr;
                NODEDIEMTHI *diemsv = new NODEDIEMTHI;
                diemsv->DIEM = diem;
                diemsv->MAMH = monthi;
                diemsv->pNext = NULL;

                for (int i = 0; i < dsl.SLLOP; i++)
                {
                    for (p = dsl.DS_LOP[i]->ds_SV.pHead; p != NULL; p = p->pNext)
                    {
                        if (p->MASV == masv)
                        {
                            ThemDiemThiVaoDS(p->ds_Diem, diemsv);
                            break;
                        }
                    }
                }

                InsertDSDiemThi(dsdt, ctdt);
            }
            break;
        }

        case 1: // === GIẢNG VIÊN ===
        {
            system("cls");
            bool check = true;

            while (check)
            {
                switch (MainMenuGV())
                {
                case 0: // LỚP
                    ChangeColor(15);
                    system("cls");
                    FunctionLop(dsl);
                    break;

                case 1: // SINH VIÊN
                    ChangeColor(15);
                    system("cls");
                    FunctionSV(dsl);
                    break;

                case 2: // MÔN HỌC
                    ChangeColor(15);
                    system("cls");
                    FunctionMon(root, dsl, dsch);
                    break;

                case 3: // CÂU HỎI
                    ChangeColor(15);
                    system("cls");
                    FunctionCH(dsch, root, dsdt, dsID);
                    break;

                case 4: // ĐIỂM
                    ChangeColor(15);
                    system("cls");
                    FunctionDiem(dsl, root, dsch, dsdt);
                    break;

                case 5: // QUAY LẠI
                    ChangeColor(15);
                    system("cls");
                    break;

                case -1: // THOÁT
                    check = false;
                    break;
                }
            }
            break;
        }

        case 2: // === ĐĂNG NHẬP SAI ===
        {
            SetBGColor(0);
            SetColor(15);
            AnConTro();
            gotoxy(132, 32);
            cout << "Sai ten dang nhap hoac mat khau";
            Sleep(500);
            HienConTro();
            break;
        }

        case -1: // === THOÁT HỆ THỐNG ===
        {
            char s;
            bool sCheck;

            if (Exit(s, sCheck))
            {
                // === GHI DỮ LIỆU RA FILE ===
                GhiFileDSLop(dsl);
                GhiFileDSMH(root);
                GhiFileCauHoi(dsch);
                GhiFileDSDiem(dsdt);
                LuuDanhSachID(dsID, "ID.txt"); // lưu trạng thái ID hiện tại

                // === GIẢI PHÓNG BỘ NHỚ ===
                GiaiPhongVungNhoDSLOP(dsl);
                GiaiPhongVungNhoDSCH(dsch);
                GiaiPhongVungNhoDSDT(dsdt);

                // === IN DÒNG CHÀO KẾT THÚC ===
                system("cls");
                SetBGColor(0);
                SetColor(15);
                gotoxy(30, 20);
                cout << " _________  ____  ____       _       ____  _____  ___  ____    ____  ____   ___   _____  _____  _  ";
                gotoxy(30, 21);
                cout << "|  _   _  ||_   ||   _|     / \\     |_   \\|_   _||_  ||_  _|  |_  _||_  _|.'   `.|_   _||_   _|| | ";
                gotoxy(30, 22);
                cout << "|_/ | | \\_|  | |__| |      / _ \\      |   \\ | |    | |_/ /      \\ \\  / / /  .-.  \\ | |    | |  | | ";
                gotoxy(30, 23);
                cout << "    | |      |  __  |     / ___ \\     | |\\ \\| |    |  __'.       \\ \\/ /  | |   | | | '    ' |  | | ";
                gotoxy(30, 24);
                cout << "   _| |_    _| |  | |_  _/ /   \\ \\_  _| |_\\   |_  _| |  \\ \\_     _|  |_  \\  `-'  /  \\ \\__/ /   |_| ";
                gotoxy(30, 25);
                cout << "  |_____|  |____||____||____| |____||_____|\\____||____||____|   |______|  `.___.'    `.__.'    (_) ";
                getch();
                return;
            }
            break;
        }
        }
    }
}
