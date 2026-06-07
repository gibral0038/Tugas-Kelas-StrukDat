/*  Nama program    : TreePegawai
    Nama Anggota    : Renadi Wilantara, Gibraldi Zilal Fachry, Muhammad Yunus Habiby, Azrel Sakhi Reswara
    NPM             : 140810240061, 140810250038, 140810250014, 140810250098
    Tanggal buat    : 07 Juni 2026
    Deskripsi       : Binary Search Tree Pegawai Menggunakan Library map
******************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <map>            // container Binary Search Tree (key terurut)
using namespace std;

struct Pegawai {
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

// Sisip pegawai ke tree (otomatis ke posisi BST yang benar berdasarkan NIP)
void insertPegawai(map<int, Pegawai>& pohon) {
    int nip;
    Pegawai P;
    cout << "NIP        : "; cin >> nip;
    if (pohon.count(nip) > 0) {           // count: cek apakah key sudah ada
        cout << "NIP sudah ada di tree." << endl;
    } else {
        cout << "Nama       : "; cin.ignore(); getline(cin, P.nama);
        do {
            cout << "Golongan (1-3) : "; cin >> P.gol;
            if (P.gol < 1 || P.gol > 3) {
                cout << "Golongan tidak valid!" << endl;
            }
        } while (P.gol < 1 || P.gol > 3);
        pohon[nip] = P;                   // masukkan node ke tree
        cout << "Pegawai berhasil di-insert." << endl;
    }
}

// Cari pegawai berdasarkan NIP
void cariByNIP(map<int, Pegawai>& pohon, int nip) {
    // find mengembalikan iterator ke node, atau end() bila tidak ada
    auto it = pohon.find(nip);
    if (it == pohon.end()) {
        cout << "Pegawai dengan NIP " << nip << " tidak ditemukan." << endl;
    } else {
        // it->first  = key (NIP),  it->second = value (Pegawai)
        cout << "\nNIP    : " << it->first
             << "\nNama   : " << it->second.nama
             << "\nGol    : " << it->second.gol
             << "\nGaji   : " << formatRibuan(hitungGaji(it->second.gol))
             << "\nTunjangan : " << formatRibuan(hitungTunjangan(it->second.gol))
             << "\nTotal  : " << formatRibuan(hitungTotal(it->second.gol)) << endl;
    }
}

// Hapus pegawai berdasarkan NIP
void deleteByNIP(map<int, Pegawai>& pohon, int nip) {
    // erase mengembalikan jumlah elemen yang dihapus (0 jika tidak ada)
    if (pohon.erase(nip) > 0) {
        cout << "Pegawai dengan NIP " << nip << " berhasil di-delete." << endl;
    } else {
        cout << "Pegawai dengan NIP " << nip << " tidak ditemukan." << endl;
    }
}

// Tampilkan semua data (InOrder = otomatis terurut menaik by NIP)
// Catatan: map menyembunyikan struktur kiri/kanan, jadi hanya InOrder
//          yang bisa ditampilkan; PreOrder & PostOrder tidak tersedia.
void traversalInOrder(map<int, Pegawai>& pohon) {
    if (pohon.empty()) {
        cout << "Tree masih kosong." << endl;
    } else {
        cout << "\n";
        cout << string(80, '-') << endl;
        cout << string(17, ' ') << "DAFTAR GAJI PEGAWAI PT. INFORMATIKA (InOrder)" << endl;
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
        for (auto& x : pohon) {                  // map sudah terurut -> InOrder
            cout << left
                 << setw(4)  << (to_string(no++) + ".")
                 << setw(10) << x.first
                 << setw(20) << x.second.nama
                 << setw(5)  << x.second.gol
                 << setw(14) << formatRibuan(hitungGaji(x.second.gol))
                 << setw(14) << formatRibuan(hitungTunjangan(x.second.gol))
                 << setw(14) << formatRibuan(hitungTotal(x.second.gol))
                 << endl;
            totalGaji        += hitungGaji(x.second.gol);
            totalTunjangan   += hitungTunjangan(x.second.gol);
            totalKeseluruhan += hitungTotal(x.second.gol);
        }
        cout << string(80, '-') << endl;
        cout << left
             << setw(39) << "Jumlah"
             << setw(14) << formatRibuan(totalGaji)
             << setw(14) << formatRibuan(totalTunjangan)
             << setw(14) << formatRibuan(totalKeseluruhan)
             << endl;
        cout << string(80, '-') << endl;
    }
}

void menu() {
    cout << "\n==========================================" << endl;
    cout << "   MENU TREE PEGAWAI (BST / map)" << endl;
    cout << "==========================================" << endl;
    cout << "  1. Insert Pegawai" << endl;
    cout << "  2. Cari by NIP" << endl;
    cout << "  3. Delete by NIP" << endl;
    cout << "  4. Traversal InOrder (Tampilkan Semua)" << endl;
    cout << "  0. Keluar" << endl;
    cout << "------------------------------------------" << endl;
    cout << "  Pilihan: ";
}

int main() {
    map<int, Pegawai> PegawaiInfor;
    int pilihan;

    do {
        menu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                cout << "\n--- Input Pegawai Baru ---" << endl;
                insertPegawai(PegawaiInfor);
                break;
            }
            case 2: {
                int nip;
                cout << "Masukkan NIP yang dicari : "; cin >> nip;
                cariByNIP(PegawaiInfor, nip);
                break;
            }
            case 3: {
                int nip;
                cout << "Masukkan NIP yang akan dihapus : "; cin >> nip;
                deleteByNIP(PegawaiInfor, nip);
                break;
            }
            case 4:
                traversalInOrder(PegawaiInfor);
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
