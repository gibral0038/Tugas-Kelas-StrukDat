/*  Nama program    : SinglyListPegawai
    Nama Anggota    : Renadi Wilantara, Gibraldi Zilal Fachry, Muhammad Yunus Habiby, Azrel Sakhi Reswara
    NPM             : 140810240061, 140810250038, 140810250014, 140810250098
    Tanggal buat    : 07 Juni 2026
    Deskripsi       : Singly Linked List Pegawai Menggunakan Library forward_list
******************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <forward_list>   // container singly linked list STL
#include <algorithm>      // untuk find_if (cari pegawai by NIP)
using namespace std;

struct Pegawai {
    string NIP;
    string nama;
    int gol;
};

string formatRibuan(long long n) {
    string s = to_string(n);
    int insert = s.length() - 3;
    while (insert > 0) {
        s.insert(insert, ".");
        insert -= 3;
    }
    return s;
}

void inputPegawai(Pegawai& P) {
    cout << "NIP        : "; cin >> P.NIP;
    cout << "Nama       : "; cin.ignore(); getline(cin, P.nama);
    do {
        cout << "Golongan (1-3) : "; cin >> P.gol;
        if (P.gol < 1 || P.gol > 3) {
            cout << "Golongan tidak valid!" << endl;
        }
    } while (P.gol < 1 || P.gol > 3);
}

long long hitungGaji(int gol) {
    long long gaji = 0;
    if (gol == 1) gaji = 3000000;
    else if (gol == 2) gaji = 4000000;
    else gaji = 5000000;
    return gaji;
}

long long hitungTunjangan(int gol) {
    long long tunjangan = hitungGaji(gol);
    if (gol == 1) tunjangan *= 1;
    else if (gol == 2) tunjangan *= 1.25;
    else tunjangan *= 1.5;
    return tunjangan;
}

long long hitungTotal(int gol) {
    return hitungGaji(gol) + hitungTunjangan(gol);
}

// Rata-rata total (gaji+tunjangan) seluruh pegawai dalam list
long long hitungRataRata(forward_list<Pegawai>& daftar) {
    long long total = 0;
    long long rata = 0;
    int jumlah = 0;
    for (auto& p : daftar) {        // telusuri tiap elemen list
        total += hitungTotal(p.gol);
        jumlah++;
    }
    if (jumlah > 0) {              // hindari bagi nol
        rata = total / jumlah;
    }
    return rata;
}

// Sisip pegawai di depan list
void insertFirst(forward_list<Pegawai>& daftar, Pegawai P) {
    daftar.push_front(P);   // tambah elemen di awal
}

// Hapus pegawai terdepan
void deleteFirst(forward_list<Pegawai>& daftar) {
    if (daftar.empty()) {                       // cek list kosong
        cout << "List kosong." << endl;
        return;
    }
    Pegawai depan = daftar.front();             // ambil data terdepan utk pesan
    daftar.pop_front();                         // hapus elemen pertama
    cout << "Pegawai \"" << depan.nama << "\" berhasil di-delete." << endl;
}

// Hapus pegawai berdasarkan NIP (di posisi mana pun)
void deleteByNIP(forward_list<Pegawai>& daftar, string nip) {
    // cek dulu apakah NIP ada, baru hapus dengan remove_if
    auto it = find_if(
        daftar.begin(),
        daftar.end(),
        [&](Pegawai p){ return p.NIP == nip; }
    );
    if (it == daftar.end()) {
        cout << "Pegawai dengan NIP " << nip << " tidak ditemukan." << endl;
    } else {
        // remove_if menghapus semua elemen yang memenuhi kondisi
        daftar.remove_if([&](Pegawai p){ return p.NIP == nip; });
        cout << "Pegawai dengan NIP " << nip << " berhasil di-delete." << endl;
    }
}

// Cari pegawai berdasarkan NIP lalu tampilkan datanya
void cariByNIP(forward_list<Pegawai>& daftar, string nip) {
    // find_if mengembalikan iterator ke elemen pertama yang cocok, atau end() bila tidak ada
    auto it = find_if(
        daftar.begin(),
        daftar.end(),
        [&](Pegawai p){ return p.NIP == nip; }
    );
    if (it == daftar.end()) {
        cout << "Pegawai dengan NIP " << nip << " tidak ditemukan." << endl;
    } else {
        cout << "\nNIP    : " << it->NIP
             << "\nNama   : " << it->nama
             << "\nGol    : " << it->gol
             << "\nGaji   : " << formatRibuan(hitungGaji(it->gol))
             << "\nTunjangan : " << formatRibuan(hitungTunjangan(it->gol))
             << "\nTotal  : " << formatRibuan(hitungTotal(it->gol)) << endl;
    }
}

// Tampilkan semua data dalam tabel
void traversal(forward_list<Pegawai>& daftar) {
    if (daftar.empty()) {                        // cek list kosong
        cout << "List kosong." << endl;
        return;
    }
    cout << "\n";
    cout << string(80, '-') << endl;
    cout << setw(57) << "DAFTAR GAJI PEGAWAI PT. INFORMATIKA" << endl;
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

    int no = 1;
    long long totalGaji = 0, totalTunjangan = 0, totalKeseluruhan = 0;
    for (auto& p : daftar) {                      // telusuri tiap elemen list
        cout << left
             << setw(4)  << (to_string(no++) + ".")
             << setw(10) << p.NIP
             << setw(20) << p.nama
             << setw(5)  << p.gol
             << setw(14) << formatRibuan(hitungGaji(p.gol))
             << setw(14) << formatRibuan(hitungTunjangan(p.gol))
             << setw(14) << formatRibuan(hitungTotal(p.gol))
             << endl;
        totalGaji        += hitungGaji(p.gol);
        totalTunjangan   += hitungTunjangan(p.gol);
        totalKeseluruhan += hitungTotal(p.gol);
    }
    cout << string(80, '-') << endl;
    cout << left
         << setw(39) << "Jumlah"
         << setw(14) << formatRibuan(totalGaji)
         << setw(14) << formatRibuan(totalTunjangan)
         << setw(14) << formatRibuan(totalKeseluruhan)
         << endl;
    cout << string(80, '-') << endl;
    cout << "Rata-rata Gaji Total : "
         << formatRibuan(hitungRataRata(daftar)) << endl;
    cout << string(80, '-') << endl;
}

void menu() {
    cout << "\n==========================================" << endl;
    cout << "   MENU LIST PEGAWAI (Singly Linked List)" << endl;
    cout << "==========================================" << endl;
    cout << "  1. InsertFirst (Tambah Pegawai)" << endl;
    cout << "  2. DeleteFirst (Hapus Pegawai Terdepan)" << endl;
    cout << "  3. Delete by NIP (Hapus Pegawai Tertentu)" << endl;
    cout << "  4. Cari by NIP (Cari Pegawai)" << endl;
    cout << "  5. Traversal   (Tampilkan Semua)" << endl;
    cout << "  0. Keluar" << endl;
    cout << "------------------------------------------" << endl;
    cout << "  Pilihan: ";
}

int main() {
    forward_list<Pegawai> PegawaiInfor;

    Pegawai newElement;
    int pilihan;

    do {
        menu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                cout << "\n--- Input Pegawai Baru ---" << endl;
                inputPegawai(newElement);
                insertFirst(PegawaiInfor, newElement);
                cout << "Pegawai berhasil di-insert." << endl;
                break;
            }
            case 2:
                deleteFirst(PegawaiInfor);
                break;
            case 3: {
                string nip;
                cout << "Masukkan NIP yang akan dihapus : "; cin >> nip;
                deleteByNIP(PegawaiInfor, nip);
                break;
            }
            case 4: {
                string nip;
                cout << "Masukkan NIP yang dicari : "; cin >> nip;
                cariByNIP(PegawaiInfor, nip);
                break;
            }
            case 5:
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
