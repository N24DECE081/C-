#pragma once
#include <string>
#include <iostream>
#define MAXMONHOC 100
#define MAXLOP 10000
#define MAXDSCTDT 1000
#define MAX_ID_POOL 10000000

using namespace std;


struct CauHoi {
    int ID;                 // ID ngẫu nhiên duy nhất
    string NOIDUNG;
    string A, B, C, D;
    string DA;              // Đáp án đúng
    bool daThi;   
    CauHoi* pNext = NULL;
};
typedef CauHoi* CauHoiNode;

struct DanhSachCauHoi {
    int SLCH = 0;
    CauHoiNode pHead = NULL;
    CauHoiNode pLast = NULL;
};
typedef struct DanhSachCauHoi DSCH;



struct MonHoc {
    string MAMH;
    string TENMH;
    DSCH* ds_cauhoi = NULL;
    MonHoc* pLeft = NULL;
    MonHoc* pRight = NULL;
    int height = 1;  // cần cho AVL tree
};
typedef MonHoc* TreeMH;

// Gốc của cây
struct DanhSachMonHoc {
    TreeMH root = NULL;
    int SLMH = 0;
};
typedef struct DanhSachMonHoc DSMH;



struct DiemThi {
    string MAMH;
    float DIEM;
    DiemThi* pNext = NULL;
};
typedef struct DiemThi NODEDIEMTHI;

struct DanhSachDiem {
    int SLDiem = 0;
    NODEDIEMTHI* pHead = NULL;
    NODEDIEMTHI* pLast = NULL;
};
typedef struct DanhSachDiem DSDIEM;



struct SinhVien {
    string MASV;
    string TEN;
    string HO;
    string PHAI;
    string PASSWORD;
    DSDIEM ds_Diem;
    SinhVien* pNext = NULL;
};
typedef struct SinhVien NODESV;

struct DanhSachSinhVien {
    int SLSV = 0;
    NODESV* pHead = NULL;
    NODESV* pLast = NULL;
};
typedef struct DanhSachSinhVien DSSV;



struct Lop {
    string MALOP;
    string TENLOP;
    DSSV ds_SV;
};
typedef struct Lop LOP;

struct DanhSachLop {
    int SLLOP = 0;
    LOP* DS_LOP[MAXLOP];
};
typedef struct DanhSachLop DSLOP;



struct CauTrucDeThi {
    string MASV;
    string MAMH;
    float DIEM;
    int sct;    // số câu thi
    int tg;     // thời gian (phút)
    int* bode = NULL;   // mảng ID câu hỏi
    int* dapan = NULL;  // mảng đáp án sinh viên
};
typedef struct CauTrucDeThi CTDT;

struct DanhSachDeThi {
    CTDT DS_CTDT[MAXDSCTDT];
    int SLDSDT = 0;
};
typedef struct DanhSachDeThi DSDT;


struct ThoiGian {
    int Gio;
    int Phut;
    int Giay;
};
typedef struct ThoiGian TG;

struct DanhSachID {
    int nodes[MAX_ID_POOL + 5]; 
    int n;                      // Tổng số ID trong danh sách
    int index;                  // Vị trí ID hiện tại (đã dùng đến đâu)
};
