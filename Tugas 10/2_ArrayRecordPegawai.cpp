/*  Nama program    : 2_ArrayRecordPegawai
    Nama            : - Gibraldi Zilal Fachry (250038)
                      - Muhammad Yunus Habiby (250014)
                      - Azrel Sakhi Reswara   (250098)
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
void menu(Data DaftarPegawai, int& n);
int main(){
    int n = 0;
    Data DaftarPegawai;
    menu(DaftarPegawai, n);
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
Pegawai createElement(){
    Pegawai baru;
    cout << "NIP : "; baru.NIP = validInputInteger(1); 
    cout << "Nama : "; 
    cin.ignore(); 
    getline(cin,baru.nama);
    cout << "Golongan (1/2/3) : "; baru.gol = validInputInteger(2);

    return baru;
}
void insert(Data arr, int& n){
    if (n >= 100){
        cout << "Array Penuh\n";
    } else {
        n++;
        if (n == 1){
            arr[0] = createElement();
        } else {
            for (int i = n - 1; i > 0; i--){
                arr[i] = arr[i - 1];
            }
            arr[0] = createElement();
        }
    }
}
void Out(Data arr, int& n, Pegawai& hasil){
    if (n == 0){
        cout << "Array Kosong\n";
    } else {
        hasil = arr[0];
        for (int i = 0; i < n - 1; i++){
            arr[i] = arr[i + 1];
        }
        n--;
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
void tampil(Data arr, int n){
    if (n <= 0){
        cout << "Array Kosong\n";
        return;
    } else {
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
        long int totalGaji = 0; 
        long int totalTunjangan = 0;
        long int totalKeseluruhan = 0;
        for(int i = 0; i < n; i++){
            cout << setw(4) << i+1 
                << setw(8) << arr[i].NIP
                << setw(20) << arr[i].nama
                << setw(4) << arr[i].gol
                << setw(14) << gaji(arr[i].gol)
                << setw(14) << tunjangan(arr[i].gol)
                << setw(16) << total(arr[i].gol) << "\n";
            totalGaji += gaji(arr[i].gol);
            totalTunjangan += tunjangan(arr[i].gol);
            totalKeseluruhan += total(arr[i].gol);
        }
        cout << "-----------------------------------------------------------------------------\n";
        cout << left << setw(36) << "Jumlah : " 
            << setw(14) << totalGaji 
            << setw(14) << totalTunjangan
            << setw(16) << totalKeseluruhan;
        cout << "\n-----------------------------------------------------------------------------\n";
        cout << "Rata rata total gaji : " << totalKeseluruhan / n << "\n";
    }
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
void menu(Data DaftarPegawai, int& n){
    int pilih;
    do {
        display();
        cin >> pilih;
        switch (pilih)
        {
        case 1 : {
            insert(DaftarPegawai, n);
            break;
        }
        case 2 : {
            Pegawai hasil;
            Out(DaftarPegawai, n, hasil);
            break;
        }
        case 3 :
            tampil(DaftarPegawai, n);
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