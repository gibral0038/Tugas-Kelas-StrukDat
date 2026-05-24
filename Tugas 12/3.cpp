/*  Nama program    : Modifikasi Pointer dan Refereces
    Nama Anggota    : Renadi Wilantara, Gibraldi Zilal Fachry, Muhammad Yunus Habiby, Azrel Sakhi Reswara
    NPM             : 140810240061, 140810250038, 140810250014, 140810250098
    Tanggal buat    : 20 Mei 2026
    Deskripsi       : Priority Queue Singly Linked List IGD 
******************************************************/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Karyawan {
    string NIP;
    string nama;
    Karyawan* next;
};

struct Divisi {
    string namaDivisi;
    Karyawan* karyawan;
    Divisi* next;
};

typedef Divisi* PointerDivisi;
typedef Karyawan* PointerKaryawan;
typedef PointerDivisi List;

bool isEmptyDivisi(List Q) {
    return Q == nullptr;
}

bool isEmptyKaryawan(PointerKaryawan Q) {
    return Q == nullptr;
}

void createList(List& Div) {
    Div = nullptr;
}

void createKaryawan(PointerKaryawan& pBaru) {
    pBaru = new Karyawan;
    cout << "NIP        : "; cin >> pBaru.NIP;
    cout << "Nama       : "; cin.ignore(); getline(cin, pBaru.nama);
    pBaru.next = nullptr;
}

void createDivisi(PointerDivisi& pBaru) {
    pBaru = new Divisi;
    cout << "Nama Divisi : "; cin.ignore(); getline(cin, pBaru->namaDivisi);
    pBaru->next = nullptr;
}

void linearSearchDivisi(List Q, string key, PointerDivisi& hasil, bool& found){
    found = false;
    if (isEmptyDivisi(Q)) {
        hasil = nullptr;
    } else {
        hasil = nullptr;
        PointerDivisi temp = Q;
        while (!found && temp != nullptr) {
            if (temp->namaDivisi == key) {
                hasil = temp;
                found = true;
                break;
            }
            temp = temp->next;
        }
    }
}

void insertFirstDivisi(List& First, PointerDivisi pBaru) {
    if (isEmptyDivisi(First)) {
        First = pBaru;
    } else {
        pBaru->next = First;
        First = pBaru;
    }
}

void insertFirstKaryawan(PointerDivisi& Div, PointerKaryawan pBaru){
    if (isEmptyKaryawan(Div->karyawan)) {
        Div->karyawan = pBaru;
    } else {
        pBaru->next = Div->karyawan;
        Div->karyawan = pBaru;
    }
}

void deleteQueue(Queue& Q, Pointer& pHapus) {
    if (Q.Head == nullptr) {
        cout << "Queue kosong." << endl;
        pHapus = NULL;
    } else if (Q.Head->next == nullptr) {
        pHapus = Q.Head;
        Q.Head = nullptr;
        Q.Tail = nullptr;
    } else {
        pHapus = Q.Head;
        Q.Head = Q.Head->next;
        pHapus->next = nullptr;
    }
}

long long hitungGaji(int gol) {
    long long gaji = 0;
    if (gol == 1) {
        gaji = 3000000;
    } else if (gol == 2) {
        gaji = 4000000;
    } else {
        gaji = 5000000;
    }
    return gaji;
}

long long hitungTunjangan(int gol) {
    long long tunjangan = hitungGaji(gol);
    if (gol == 1) {
        tunjangan *= 1;
    } else if (gol == 2) {
        tunjangan *= 1.25;
    } else {
        tunjangan *= 1.5;
    }
    return tunjangan;
}

long long hitungTotal(int gol) {
    return hitungGaji(gol) + hitungTunjangan(gol);
}

long long hitungTotalGaji(Queue Q) {
    long long total = 0;
    Pointer pBantu = Q.Head;
    while (pBantu != nullptr) {
        total += hitungGaji(pBantu->info.gol);
        pBantu = pBantu->next;
    }
    return total;
}

long long hitungTotalTunjangan(Queue Q) {
    long long total = 0;
    Pointer pBantu = Q.Head;
    while (pBantu != nullptr) {
        total += hitungTunjangan(pBantu->info.gol);
        pBantu = pBantu->next;
    }
    return total;
}

long long hitungTotalKeseluruhan(Queue Q) {
    long long total = 0;
    Pointer pBantu = Q.Head;
    while (pBantu != nullptr) {
        total += hitungTotal(pBantu->info.gol);
        pBantu = pBantu->next;
    }
    return total;
}

double hitungRataRata(Queue Q) {
    double rata = 0;
    if (Q.Head != nullptr) {
        int n = 0;
        Pointer pBantu = Q.Head;
        while (pBantu != nullptr) {
            n++;
            pBantu = pBantu->next;
        }
        rata = (double)hitungTotalKeseluruhan(Q) / n;
    }
    return rata;
}

void traversal(Queue Q) {
    if (Q.Head == nullptr) {
        cout << "Queue kosong." << endl;
        return;
    }

    cout << "\n";
    cout << string(80, '-') << endl;
    cout << setw(45) << "DAFTAR GAJI PEGAWAI PT. INFORMATIKA" << endl;
    cout << string(80, '-') << endl;
    cout << left
         << setw(4)  << "No"
         << setw(10) << "NIP"
         << setw(20) << "Nama"
         << setw(5)  << "Gol"
         << setw(14) << "Gaji"
         << setw(14) << "Tunjangan"
         << setw(14) << "Total"
         << endl;
    cout << string(80, '-') << endl;

    Pointer pBantu = Q.Head;
    int no = 1;
    while (pBantu != nullptr) {
        cout << left
             << setw(4)  << (to_string(no++) + ".")
             << setw(10) << pBantu->info.NIP
             << setw(20) << pBantu->info.nama
             << setw(5)  << pBantu->info.gol
             << setw(14) << formatRibuan(hitungGaji(pBantu->info.gol))
             << setw(14) << formatRibuan(hitungTunjangan(pBantu->info.gol))
             << setw(14) << formatRibuan(hitungTotal(pBantu->info.gol))
             << endl;
        pBantu = pBantu->next;
    }

    cout << string(80, '-') << endl;
    cout << left
         << setw(39) << "Jumlah"
         << setw(14) << formatRibuan(hitungTotalGaji(Q))
         << setw(14) << formatRibuan(hitungTotalTunjangan(Q))
         << setw(14) << formatRibuan(hitungTotalKeseluruhan(Q))
         << endl;
    cout << string(80, '-') << endl;
    cout << "Rata-rata Gaji Total : " << fixed << setprecision(0)
         << formatRibuan((long long)hitungRataRata(Q)) << endl;
    cout << string(80, '-') << endl;
}

void menu() {
    cout << "\n==========================================" << endl;
    cout << "   MENU QUEUE PEGAWAI (Linked List)" << endl;
    cout << "==========================================" << endl;
    cout << "  1. InsertQueue (Tambah Pegawai)" << endl;
    cout << "  2. DeleteQueue (Hapus Pegawai Terdepan)" << endl;
    cout << "  3. Traversal   (Tampilkan Semua)" << endl;
    cout << "  0. Keluar" << endl;
    cout << "------------------------------------------" << endl;
    cout << "  Pilihan: ";
}

int main() {
    Queue PegawaiInfor;
    createQueue(PegawaiInfor);

    Pointer pBaru, pHapus;
    int pilihan;

    do {
        menu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\n--- Input Pegawai Baru ---" << endl;
                createElmt(pBaru);
                insertQueue(PegawaiInfor, pBaru);
                cout << "Pegawai berhasil di-insert." << endl;
                break;
            case 2:
                deleteQueue(PegawaiInfor, pHapus);
                if (pHapus != nullptr) {
                    cout << "\nPegawai \"" << pHapus->info.nama
                         << "\" berhasil di-delete." << endl;
                    delete pHapus;
                    pHapus = nullptr;
                }
                break;
            case 3:
                traversal(PegawaiInfor);
                break;
            case 0:
                cout << "\nProgram Selesai." << endl;
                break;
            default:
                cout << "\nPilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);

    return 0;
}