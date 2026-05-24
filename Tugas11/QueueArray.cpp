/*  Nama      : Renadi Wilantara, Gibraldi Zilal Fachry, Muhammad Yunus Habiby, Azrel Sakhi Reswara  
    NPM       : 140810240061, 140810250038, 140810250014, 140810250098
    Tanggal   : 17 Mei 2026
    Deskripsi : Queue Array Pegawai 
*/


#include <iostream>
#include <iomanip>

using namespace std;

const int MAKS = 255;

struct Pegawai {
    string NIP;
    string nama;
    int gol;
};

struct QueueArray {
    Pegawai info[MAKS];
    int head;
    int tail;
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


void createQueue(QueueArray& Q) {
    Q.head = 0;
    Q.tail = -1;
}

void inputPegawai (Pegawai& P) {
    cout << "NIP        : "; cin >> P.NIP;
    cout << "Nama       : "; cin.ignore(); getline(cin, P.nama);
    do {
        cout << "Golongan (1-3) : "; cin >> P.gol;
        if (P.gol < 1 || P.gol > 3) {
            cout << "Golongan tidak valid!" << endl;
        }
    } while (P.gol < 1 || P.gol > 3);
}

bool isFullArray(QueueArray& Q) {
    return Q.tail == MAKS - 1;
}

bool isEmptyArray(QueueArray& Q) {
    return Q.head > Q.tail;
}

void insertQueue(QueueArray& Q, Pegawai newElement) {
    if (isFullArray(Q)) {
        cout << "Queue Sudah Penuh." << endl;
    } else {
        Q.tail++;
        Q.info[Q.tail] = newElement;
    }
}

void deleteQueue(QueueArray& Q, Pegawai& delElement) {
    if (isEmptyArray(Q)) {
        cout << "Queue Kosong." << endl;
    } else {
        delElement = Q.info[Q.head];
        int i = 0;
        while (i < Q.tail) {
            Q.info[i] = Q.info[i+1];
            i++;
        }
        Q.tail--;
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
        tunjangan *= 1 ;
    } else if (gol == 2) {
        tunjangan *= 1.25 ;
    } else {
        tunjangan *= 1.5;
    }

    return tunjangan;
}

long long hitungTotal(int gol) {
    return hitungGaji(gol) + hitungTunjangan(gol);
}

long long hitungTotalGaji(QueueArray Q) {
    long long total = 0;
    int idx = Q.head;
    while (idx <= Q.tail) {
        total += hitungGaji(Q.info[idx].gol);
        idx++;
    }
    return total;
}

long long hitungTotalTunjangan(QueueArray Q) {
    long long total = 0;
    int idx = Q.head;
    while (idx <= Q.tail) {
        total += hitungTunjangan(Q.info[idx].gol);
        idx++;
    }
    return total;
}

long long hitungTotalKeseluruhan(QueueArray Q) {
    long long total = 0;
    int idx = Q.head;
    while (idx <= Q.tail) {
        total += hitungTotal(Q.info[idx].gol);
        idx++;
    }
    return total;
}

double hitungRataRata(QueueArray Q) {
    double rata = 0;
    
    if (!isEmptyArray(Q)) {
        long long total = 0;
        int idx = Q.head;
        while (idx <= Q.tail) {
            total += hitungTotal(Q.info[idx].gol);
            idx++;
        }
        rata = (double)total / (Q.tail - Q.head + 1);
    }
    return rata;
}

void traversal(QueueArray Q) {
    if (isEmptyArray(Q)) {
        cout << "Queue kosong." << endl;
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

    int idx = Q.head;
    int no  = 1;
    while (idx <= Q.tail) {
        cout << left
             << setw(4)  << (to_string(no++) + ".")
             << setw(10) << Q.info[idx].NIP
             << setw(20) << Q.info[idx].nama
             << setw(5)  << Q.info[idx].gol
             << setw(14) << formatRibuan(hitungGaji(Q.info[idx].gol))
             << setw(14) << formatRibuan(hitungTunjangan(Q.info[idx].gol))
             << setw(14) << formatRibuan(hitungTotal(Q.info[idx].gol))
             << endl;
        idx++;
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
         << formatRibuan(hitungRataRata(Q)) << endl;
    cout << string(80, '-') << endl;
}

void menu() {
    cout << "\n==========================================" << endl;
    cout << "   MENU QUEUE PEGAWAI (Array)" << endl;
    cout << "==========================================" << endl;
    cout << "  1. InsertQueue (Tambah Pegawai)" << endl;
    cout << "  2. DeleteQueue (Hapus Pegawai Terdepan)" << endl;
    cout << "  3. Traversal   (Tampilkan Semua)" << endl;
    cout << "  0. Keluar" << endl;
    cout << "------------------------------------------" << endl;
    cout << "  Pilihan: ";
}


int main() {
    QueueArray PegawaiInfor;
    createQueue(PegawaiInfor);

    Pegawai newElement, delElement;
    int pilihan;

    do {
        menu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\n--- Input Pegawai Baru ---" << endl;
                inputPegawai(newElement);
                insertQueue(PegawaiInfor, newElement);
                cout << "Pegawai berhasil di-insert." << endl;
                break;
            case 2:
                if (isEmptyArray(PegawaiInfor)) {
                    cout << "\nQueue kosong." << endl;
                } else {
                    deleteQueue(PegawaiInfor, delElement);
                    cout << "\nPegawai \"" << delElement.nama << "\" berhasil di-delete." << endl;
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