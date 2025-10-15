#pragma once
#include <iostream>
using namespace std;


// Danh sách câu hỏi thi: danh sách liên kết đơn
struct CauHoi {
    int ID;                 
    char NoiDung[256];      
    char A[100], B[100], C[100], D[100]; 
    char DapAn;             
};

// Nút của danh sách câu hỏi (liên kết đơn)
struct nodeCH {
    CauHoi ch;              
    nodeCH *next;           
};
typedef nodeCH* PTRCH;      


// Danh sách môn học: cây nhị phân tìm kiếm cân bằng (AVL)
struct MonHoc {
    char MAMH[16];          
    char TENMH[51];        
    int height;             
    PTRCH FirstCH = NULL;   
};

// Nút của cây môn học
struct nodeMH {
    MonHoc mh;              
    nodeMH *left;          
    nodeMH *right;          
};
typedef nodeMH* TREE_MH;    


// Danh sách điểm thi: danh sách liên kết đơn
struct DiemThi {
    char MAMH[16];          
    float diem;             
};

struct nodeDiem {
    DiemThi dt;             // Dữ liệu điểm thi
    nodeDiem *next;         
};
typedef nodeDiem* PTRDIEM;  


struct SinhVien {
    char MASV[16];          
    char HO[51];            
    char TEN[11];           
    char PHAI[4];           
    char password[20];      
    PTRDIEM dsDiemThi = NULL; 
};

// Nút danh sách liên kết đơn của sinh viên
struct nodeSV {
    SinhVien sv;            
    nodeSV *next;           
};
typedef nodeSV* PTRSV;      

// Danh sách lớp: mảng con trỏ (tối đa 10000 lớp)
const int MAX_LOP = 10000;

struct Lop {
    char MALOP[16];         
    char TENLOP[51];        
    PTRSV FirstSV = NULL;   
};


struct DS_LOP {
    int n = 0;              
    Lop* nodes[MAX_LOP];    
};



// Lưu trữ thông tin 1 bài thi của sinh viên (sau khi thi)
struct CauTrucDeThi {
    char MASV[16];         
    char MAMH[16];          
    float DIEM;             
    int soCau;              
    int thoiGian;           
    int *boDe = NULL;       // Mảng ID các câu hỏi được chọn (size = soCau)
    char *dapAn = NULL;     // Mảng đáp án sinh viên chọn (size = soCau)
};



const int MAX_DETHI = 1000;
struct DS_DETHI {
    CauTrucDeThi ds[MAX_DETHI]; // Mảng lưu các bài thi
    int soLuong = 0;            // Số lượng đề thi hiện có
};



struct ThoiGian {
    int Gio;
    int Phut;
    int Giay;
};



int main() {
    TREE_MH dsMH = NULL;     
    DS_LOP dsLop;            
    DS_DETHI dsDeThi;        
    return 0;
}
