/*  Nama program    : StackPegawai
    Nama            : Gibraldi Zilal Fachry
    NPM             : 140810250038
    Tanggal buat    : 28 April 2026
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
void createStack(List& list);
void menu(List& list);
int main(){
    List list;
    createStack(list);
    menu(list);
}
void createStack(List& list){
    list = nullptr;
}
Pointer createElement(){
    Pointer baru = new Node;
    cout << "NIP : "; cin >> baru->info.NIP;
    cout << "Nama : "; cin >> baru->info.nama;
    cout << "Golongan : "; cin >> baru->info.gol;
    baru->next = nullptr;
    
    return baru;
}
void Push(List& list, Pointer& tail){
    Pointer baru = createElement();
    if (list == nullptr){
        list = baru;
        tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }
}
void Pop(List& list, Pointer& tail, Pointer& hasil){
    if (list == nullptr){
        cout << "List Kosong\n";
        hasil = nullptr;
    } else if (list == tail){
        hasil = list;
        list = nullptr;
        tail = nullptr;
    } else {
        Pointer prec = list;
        while (prec->next != tail){
            prec = prec->next;
        }
        hasil = tail;
        tail = prec;
    }
}
void cetakList(List list){
    if (list == nullptr){
        cout << "List kosong\n";
        return;
    }
    Pointer jalan = list;
    cout << setw(38) << "DATA GAJI PEGAWAI PT INFORMATIKA\n";
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
    int gaji[3] = {3000000, 4000000, 5000000};
    float tunjangan[3] = {1, 1.25, 1.5};
    int totalGaji = 0, totalTunjangan = 0, totalKeseluruhan = 0, count = 0;
    do {
        int total;
        cout << left << setw(4) << count + 1 
             << setw(8) << jalan -> info.NIP
             << setw(20) << jalan -> info.nama
             << setw(4) << jalan -> info.gol
             << setw(14) << gaji[jalan -> info.gol - 1];
        long int tunjanganPegawai = gaji[jalan -> info.gol - 1] * tunjangan[jalan -> info.gol - 1];
        cout << left << setw(14) << tunjanganPegawai;
        total = gaji[jalan -> info.gol - 1] + tunjanganPegawai;
        totalGaji += gaji[jalan -> info.gol - 1];
        totalTunjangan += tunjanganPegawai;
        totalKeseluruhan += total;
        cout << left << setw(16) << total << "\n";
        count++;
        jalan = jalan -> next;
    } while (jalan != nullptr);
    cout << "-----------------------------------------------------------------------------\n";
    cout << left << setw(36) << "Jumlah : " 
         << setw(14) << totalGaji 
         << setw(14) << totalTunjangan
         << setw(16) << totalKeseluruhan;
    cout << "\n-----------------------------------------------------------------------------\n";
    cout << "Rata rata total gaji : " << totalKeseluruhan / count << endl;
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
void menu(List& list){
    int pilih;
    Pointer tail = nullptr;
    do {
        display();
        cin >> pilih;
        switch (pilih)
        {
        case 1 : {
            Push(list, tail);
            break;
        }
        case 2 : {
            Pointer hasil;
            Pop(list, tail, hasil);
            delete hasil;
            break;
        }
        case 3 : {
            cetakList(list);
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