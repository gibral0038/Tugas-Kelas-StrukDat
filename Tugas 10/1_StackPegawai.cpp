/*  Nama program    : 1_StackPegawai
    Nama Kelompok   : - Renadi Wilantara (140810240061)
                      - Muhammad Yunus Habiby (140810250014)
                      - Gibraldi Zilal Fachry (140810250038)
                      - Azrel Sakhi Reswara   (140810250098)
    Tanggal buat    : 09 Mei 2026
    Deskripsi       : Sebuah program untuk melakukan modifikasi pada
                      sebuah List dengan konsep Stack berisikan data 
                      pegawai pada PT INFORMATIKA dengan menu fungsi 
                      berupa Push, Pop dan Cetak Data.
******************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Pegawai{
    int NIP;
    string nama;
    int gol;
};
struct Node{
    Pegawai info;
    Node* next;
};
typedef Node* Pointer;
typedef Pointer List;
typedef Pointer Stack;
void createStack(Stack& StackPegawai);
void menu(Stack& StackPegawai);
int main(){
    List StackPegawai;
    createStack(StackPegawai);
    menu(StackPegawai);
}
int validInputInteger(int jenis){
    int n;
    bool valid;
    if (jenis == 1){
        do{
            valid = true;
            std::cin >> n;
            if (std::cin.fail()){
                std::cout << "Input Tidak Valid\nUlangi : ";
                std::cin.clear();
                std::cin.ignore(1000000, '\n');
                valid = false;
            }
        } while (!valid); 
    } else {
        do{
            valid = true;
            std::cin >> n;
            if (std::cin.fail() || n < 1 || n > 3){
                std::cout << "Input Tidak Valid\nUlangi (1/2/3): ";
                std::cin.clear();
                std::cin.ignore(1000000, '\n');
                valid = false;
            }
        } while (!valid); 
    }
    return n;
}
void createStack(Stack& top){
    top = nullptr;
}
Pointer createElement(){
    Pointer baru = new Node;
    cout << "NIP : "; baru->info.NIP = validInputInteger(1); 
    cout << "Nama : "; 
    cin.ignore(); 
    getline(cin, baru->info.nama);
    cout << "Golongan (1/2/3) : "; baru->info.gol = validInputInteger(2);
    baru->next = nullptr;
    
    return baru;
}
void Push(Stack& top, Pointer& tail){
    Pointer baru = createElement();
    if (top == nullptr){
        top = baru;
        tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }
}
void Pop(Stack& top, Pointer& tail, Pointer& hasil){
    if (top == nullptr){
        cout << "Stack Kosong\n";
        hasil = nullptr;
    } else if (top == tail){
        hasil = top;
        top = nullptr;
        tail = nullptr;
    } else {
        Pointer prec = top;
        while (prec->next != tail){
            prec = prec->next;
        }
        hasil = tail;
        tail = prec;
        tail -> next = nullptr;
    }
}
long int gaji(const int& gol){
    long int hasil;
    if (gol == 1) hasil = 3000000;
    else if (gol == 2) hasil = 4000000;
    else if (gol == 3) hasil = 5000000;
    else hasil = 0;
    return hasil;
}
long double tunjangan(const int& gol){
    long double hasil;
    if (gol == 1) hasil = gaji(gol) * 1;
    else if (gol == 2) hasil = gaji(gol) * 1.25;
    else if (gol == 3) hasil = gaji(gol) * 1.5;
    else hasil = 0;
    return hasil;
}
long double total(const int& gol){
    long double hasil;
    if (gol == 1) hasil = gaji(gol) * 2;
    else if (gol == 2) hasil = gaji(gol) * 2.25;
    else if (gol == 3) hasil = gaji(gol) * 2.5;
    else hasil = 0;
    return hasil;
}
void cetakStack(Stack list){
    if (list == nullptr){
        cout << "Stack kosong\n";
    } else {
        int count = 0;
        long int totalGaji = 0;
        long int totalTunjangan = 0;
        long int totalGabungan = 0;
        Pointer jalan = list;
        cout << setw(38) << "DATA GAJI PEGAWAI PT INFORMATIKA" << "\n";
        cout << left;
        cout << "-----------------------------------------------------------------------------\n";
        cout << setw(4) << "No" 
            << setw(8) << "NIP" 
            << setw(20) << "Nama" 
            << setw(4) << "gol"
            << setw(14) << "Gaji"
            << setw(14) << "Tunjangan"
            << setw(16) << "Total" << "\n";
        cout << "-----------------------------------------------------------------------------\n";
        do {
            count++;
            cout << left << setw(4) << count
                << setw(8) << jalan -> info.NIP
                << setw(20) << jalan -> info.nama
                << setw(4) << jalan -> info.gol
                << setw(14) << gaji(jalan->info.gol)
                << setw(14) << tunjangan(jalan->info.gol)
                << setw(16) << total(jalan->info.gol) << "\n";
            totalGaji += gaji(jalan->info.gol);
            totalTunjangan += tunjangan(jalan->info.gol);
            totalGabungan += total(jalan->info.gol);
            jalan = jalan -> next;
        } while (jalan != nullptr);
        cout << "-----------------------------------------------------------------------------\n";
        cout << left << setw(36) << "Jumlah : " 
            << setw(14) << totalGaji
            << setw(14) << totalTunjangan
            << setw(16) << totalGabungan;
        cout << "\n-----------------------------------------------------------------------------\n";
        cout << "Rata rata total gaji : " << totalGabungan / count << endl;
    }
}
void display(){
    cout << "-------------------\n"
         << "1. Push Stack\n"
         << "2. Pop Stack\n"
         << "3. Tampilkan Data\n"
         << "4. Keluar\n"
         << "-------------------\n"
         << "Pilihan : ";
}
void menu(Stack& StackPegawai){
    int pilih;
    Pointer last = nullptr;
    do {
        display();
        cin >> pilih;
        switch (pilih)
        {
        case 1 : {
            Push(StackPegawai, last);
            break;
        }
        case 2 : {
            Pointer hasil;
            Pop(StackPegawai, last, hasil);
            delete hasil;
            break;
        }
        case 3 : {
            cetakStack(StackPegawai);
            break;
        }
        case 4 :
            cout << "Program selesai.\nTerima kasih telah menggunakan program ini\n";
            break;
        default:
            cout << "Input tidak valid.\nUlangi\n";
            cin.clear();
            cin.ignore(4000000, '\n');
            break;
        }
    } while (pilih != 4);
}