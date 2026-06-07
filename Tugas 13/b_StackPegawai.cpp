/*  Nama program    : 1_StackPegawai
    Nama Kelompok   : - Renadi Wilantara (140810240061)
                      - Muhammad Yunus Habiby (140810250014)
                      - Gibraldi Zilal Fachry (140810250038)
                      - Azrel Sakhi Reswara   (140810250098)
    Tanggal buat    : 07 Juni 2026
    Deskripsi       : Stack Pegawai Menggunakan Library Stack
******************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
using namespace std;

struct Pegawai{
    int NIP;
    string nama;
    int gol;
};

int validInputInteger(int jenis){
    int n;
    bool valid = true;
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
    std::cout << "NIP : "; baru.NIP = validInputInteger(1); 
    std::cout << "Nama : "; 
    std::cin.ignore(); 
    std::getline(std::cin, baru.nama);
    std::cout << "Golongan (1/2/3) : "; baru.gol = validInputInteger(2);
    
    return baru;
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
void cetakStack(stack<Pegawai> daftar){
    if (daftar.empty()){
        cout << "Stack kosong\n";
    } else {
        int count = 0;
        long int totalGaji = 0;
        long int totalTunjangan = 0;
        long int totalGabungan = 0;
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
                << setw(8) << daftar.top().NIP
                << setw(20) << daftar.top().nama
                << setw(4) << daftar.top().gol
                << setw(14) << gaji(daftar.top().gol)
                << setw(14) << tunjangan(daftar.top().gol)
                << setw(16) << total(daftar.top().gol) << "\n";
            totalGaji += gaji(daftar.top().gol);
            totalTunjangan += tunjangan(daftar.top().gol);
            totalGabungan += total(daftar.top().gol);
            daftar.pop();
        } while (!daftar.empty()); 
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
void menu(stack<Pegawai>& StackPegawai){
    int pilih;
    do {
        display();
        cin >> pilih;
        switch (pilih)
        {
        case 1 : {
            Pegawai baru;
            baru = createElement();
            StackPegawai.push(baru);
            break;
        }
        case 2 : {
            Pegawai hasil;
            hasil = StackPegawai.top();
            StackPegawai.pop();
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
int main(){
    stack<Pegawai> Daftar;
    menu(Daftar);

    return 0;
}