/*  Nama program    : 2_ArrayRecordPegawai
    Nama            : Gibraldi Zilal Fachry
    NPM             : 140810250038
    Tanggal buat    : 09 Mei 2026
    Deskripsi       : Sebuah program untuk melakukan modifikasi pada
                      sebuah array of record yang berisikan data pegawai
                      pada PT INFORMATIKA dengan menu fungsi berupa
                      insert indeks 0 dan delete indeks 0 serta tampilkan.
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
typedef Pegawai Data[100];
void menu(Data arr, int& n);
int main(){
    int n = 0;
    Data arr;
    menu(arr, n);
}
Pegawai createElement(){
    Pegawai baru;
    cout << "NIP : "; cin >> baru.NIP;
    cout << "Nama : "; cin >> baru.nama;
    cout << "Golongan : "; cin >> baru.gol;

    return baru;
}
void insert(Data arr, int& n){
    n++;
    if (n >= 100){
        cout << "Array Penuh\n";
        n--;
        return;
    }
    if (n == 1){
        arr[0] = createElement();
        return;
    }
    for (int i = n - 1; i > 0; i--){
        arr[i] = arr[i - 1];
    }
    arr[0] = createElement();
}
void Out(Data arr, int& n, Pegawai& hasil){
    if (n == 0){
        cout << "Array Kosong\n";
        return;
    } else {
        hasil = arr[0];
        for (int i = 0; i < n - 1; i++){
            arr[i] = arr[i + 1];
        }
    }
    n--;
}
void tampil(Data arr, int n){
    if (n <= 0){
        cout << "Array masih kosong\n";
        return;
    }
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
    float tunjangan[3] = {1.0, 1.25, 1.5};
    int totalGaji = 0, totalTunjangan = 0, totalKeseluruhan = 0;
    for(int i = 0; i < n; i++){
        int total;
        cout << setw(4) << i+1 
             << setw(8) << arr[i].NIP
             << setw(20) << arr[i].nama
             << setw(4) << arr[i].gol
             << setw(14) << gaji[arr[i].gol - 1];
        long int tunjanganPegawai = gaji[arr[i].gol - 1] * tunjangan[arr[i].gol - 1];
        cout << setw(14) << tunjanganPegawai;
        total = gaji[arr[i].gol - 1] * (1 + tunjangan[arr[i].gol - 1]);
        totalGaji += gaji[arr[i].gol - 1];
        totalTunjangan += (gaji[arr[i].gol - 1] * tunjangan[arr[i].gol - 1]);
        totalKeseluruhan += total;
        cout << setw(16) << total << "\n";
    }
    cout << "-----------------------------------------------------------------------------\n";
    cout << left << setw(36) << "Jumlah : " 
         << setw(14) << totalGaji 
         << setw(14) << totalTunjangan
         << setw(16) << totalKeseluruhan;
    cout << "\n-----------------------------------------------------------------------------\n";
    cout << "Rata rata total gaji : " << totalKeseluruhan / n << "\n";
}
void display(){
    cout << "-------------------\n"
         << "1. Insert First\n"
         << "2. Out First\n"
         << "3. Tampilkan Data\n"
         << "4. Keluar\n"
         << "-------------------\n"
         << "Pilihan : ";
}
void menu(Data arr, int& n){
    int pilih;
    do {
        display();
        cin >> pilih;
        switch (pilih)
        {
        case 1 : {
            insert(arr, n);
            break;
        }
        case 2 : {
            Pegawai hasil;
            Out(arr, n, hasil);
            break;
        }
        case 3 :
            tampil(arr, n);
            break;
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