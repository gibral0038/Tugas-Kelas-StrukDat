/* Nama program    : SinglyPriorityQueueIGD
    Nama Anggota    : Renadi Wilantara, Gibraldi Zilal Fachry, Muhammad Yunus Habiby, Azrel Sakhi Reswara
    NPM             : 140810240061, 140810250038, 140810250014, 140810250098
    Tanggal buat    : 20 Mei 2026
    Deskripsi       : Priority Queue IGD menggunakan STL queue
******************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <deque> 

using namespace std;

struct Pasien {
    string IDPasien;
    string nama;
    int triase; 
};

struct banding {
    bool operator ()(const Pasien& a, const Pasien& b){
        return a.triase > b.triase; 
    }
};

int triase(){
    int prioritas;
    bool accepted = false;
    do {
        accepted = true;
        cout << "Tingkat Prioritas : \n"
             << "1. Prioritas 1 (Merah)\n"
             << "2. Prioritas 2 (Kuning)\n"
             << "3. Prioritas 3 (Hijau)\n"
             << "Pilih Prioritas (1-3): ";
        cin >> prioritas;
        if (cin.fail() || prioritas < 1 || prioritas > 3) {
            cin.clear(); 
            cin.ignore(400000, '\n'); 
            cout << "Prioritas tidak valid! Masukkan angka antara 1 dan 3." << endl;
            accepted = false;
        }
    } while (!accepted);
    return prioritas;
}

void inputPasien (Pasien& P) {
    cout << "ID Pasien  : "; cin >> P.IDPasien;
    cout << "Nama       : "; cin.clear(); cin.ignore(400000,'\n'); getline(cin, P.nama);
    P.triase = triase();
}

void traversal(priority_queue<Pasien, deque<Pasien>, banding> daftar) {
    if (daftar.empty()) {
        cout << "\nQueue kosong." << endl;
    }
    else {
        cout << "\n";
        cout << string(73, '-') << endl;
        cout << setw(45) << " DAFTAR ANTRIAN PASIEN IGD " << endl;
        cout << string(73, '-') << endl;
        cout << left
             << "| " << setw(4)  << "No"
             << "| " << setw(20) << "ID Pasien"
             << "| " << setw(30) << "Nama"
             << "| " << setw(10) << "Prioritas"
             << "|" << endl;
        cout << string(73, '-') << endl;

        int count = 0;
        while (!daftar.empty()) {
            Pasien p = daftar.top();
            cout << left
                 << "| " << setw(4)  << count + 1
                 << "| " << setw(20) << p.IDPasien
                 << "| " << setw(30) << p.nama
                 << "| " << setw(10) << (p.triase == 1 ? "1 (Merah)" : p.triase == 2 ? "2 (Kuning)" : "3 (Hijau)")
                 << "|" << endl;
            daftar.pop();
            count++;
        }
        cout << string(73, '-') << endl;
    }
}

void menu() {
    cout << "\n==========================================" << endl;
    cout << "   MENU PRIORITY QUEUE IGD (STL DEQUE)" << endl;
    cout << "==========================================" << endl;
    cout << "   1. InsertQueue (Tambah Pasien)" << endl;
    cout << "   2. DeleteQueue (Tangani Pasien Utama)" << endl;
    cout << "   3. Traversal   (Tampilkan Semua)" << endl;
    cout << "   0. Keluar" << endl;
    cout << "------------------------------------------" << endl;
    cout << "   Pilihan: ";
}

int main() {
    priority_queue<Pasien, deque<Pasien>, banding> PasienIGD;
    int pilihan;

    do {
        menu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                Pasien newElement;
                cout << "\n--- Input Pasien Baru ---" << endl;
                inputPasien(newElement);
                PasienIGD.push(newElement); 
                cout << "Pasien \"" << newElement.nama << "\" berhasil masuk antrean." << endl;
                break;
            }
            case 2: {
                if (PasienIGD.empty()) {
                    cout << "\nQueue kosong. Tidak ada pasien yang perlu ditangani." << endl;
                } else {
                    Pasien delElement = PasienIGD.top();
                    PasienIGD.pop();
                    cout << "\nPasien \"" << delElement.nama << "\" (Triase " << delElement.triase << ") berhasil ditangani & dikeluarkan dari queue." << endl;
                }
                break;
            }
            case 3:
                traversal(PasienIGD);
                break;
            case 0:
                cout << "\nProgram Selesai. Membersihkan sisa antrean..." << endl;
                while (!PasienIGD.empty()) {
                    PasienIGD.pop();
                }
                break;
            default:
                cin.clear(); 
                cin.ignore(400000, '\n');
                cout << "\nPilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);

    return 0;
}