/*  Nama program    : MultiListPerusahaan
    Nama Anggota    : Renadi Wilantara, Gibraldi Zilal Fachry, Muhammad Yunus Habiby, Azrel Sakhi Reswara
    NPM             : 140810240061, 140810250038, 140810250014, 140810250098
    Tanggal buat    : 24 Mei 2026
    Deskripsi       : Multi Linked List Perusahaan 
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
    cout << "NIP        : "; cin >> pBaru->NIP;
    cout << "Nama       : "; cin.ignore(40000, '\n'); getline(cin, pBaru->nama);
    pBaru->next = nullptr;
}

void createDivisi(PointerDivisi& pBaru) {
    pBaru = new Divisi;
    cout << "Nama Divisi : "; cin.ignore(40000, '\n'); getline(cin, pBaru->namaDivisi);
    pBaru->karyawan = nullptr;
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

void insertFirstKaryawan(PointerDivisi& Div, PointerKaryawan pBaru){
    if (isEmptyKaryawan(Div->karyawan)) {
        Div->karyawan = pBaru;
    } else {
        pBaru->next = Div->karyawan;
        Div->karyawan = pBaru;
    }
}

void deleteFirstKaryawan(PointerDivisi& Div, PointerKaryawan& pHapus) {
    if (isEmptyKaryawan(Div->karyawan)) {
        cout << "Tidak Ada Karyawan." << endl;
        pHapus = NULL;
    } else if (Div->karyawan->next == nullptr) {
        pHapus = Div->karyawan;
        Div->karyawan = nullptr;
    } else {
        pHapus = Div->karyawan;
        Div->karyawan = Div->karyawan->next;
        pHapus->next = nullptr;
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

void deleteFirstDivisi(List& Div, PointerDivisi& pHapus) {
    if (isEmptyDivisi(Div)) {
        cout << "Tidak Ada Divisi." << endl;
        pHapus = NULL;
    } else if (Div->next == nullptr) {
        pHapus = Div;
        Div = nullptr;
    } else {
        pHapus = Div;
        Div = Div->next;
        pHapus->next = nullptr;
    }
}

void traversalSemua(List Div) {
    if (Div == nullptr) {
        cout << "Queue kosong." << endl;
    } else {
        cout << string(80, '-') << endl;
        cout << setw(42) << " Daftar Divisi dan Karyawan PT KomputerKu Tbk " << endl;
        cout << string(80, '-') << endl;
        cout << left
             << "| " << setw(4)  << "No"
             << "| " << setw(20) << "Nama Divisi"
             << "| " << setw(20) << "NIP"
             << "| " << setw(30) << "Nama Karyawan"
             << "|" << endl;
        cout << string(80, '-') << endl;
        int countDivisi = 0;
        PointerDivisi tempDivisi = Div;
        while (tempDivisi != nullptr) {
            PointerKaryawan tempKaryawan = tempDivisi->karyawan;
            cout << left
                 << "| " << setw(4)  << countDivisi + 1
                 << "| " << setw(20) << tempDivisi->namaDivisi;
            if (tempKaryawan != nullptr) {
                cout << "| " << setw(20) << tempKaryawan->NIP
                     << "| " << setw(30) << tempKaryawan->nama
                     << "|" << endl;
                tempKaryawan = tempKaryawan->next;
                while (tempKaryawan != nullptr) {
                    cout << left
                        << "| " << setw(4)  << ""
                        << "| " << setw(20) << ""
                        << "| " << setw(20) << tempKaryawan->NIP
                        << "| " << setw(30) << tempKaryawan->nama
                        << "|" << endl;
                    tempKaryawan = tempKaryawan->next;
                }
            } else {
                cout << "| " << setw(20) << ""
                     << "| " << setw(30) << ""
                     << "|" << endl;
            }
            tempDivisi = tempDivisi->next;
            countDivisi++;
        }
        cout << string(80, '-') << endl;
    }

}

void traversalDivisi(PointerDivisi Div) {
    if (Div == nullptr) {
        cout << "Divisi kosong." << endl;
    } else {
        cout << string(80, '-') << endl;
        cout << setw(42) << " Daftar Divisi dan Karyawan PT KomputerKu Tbk " << endl;
        cout << string(80, '-') << endl;
        cout << left
             << "| " << setw(4)  << "No"
             << "| " << setw(20) << "Nama Divisi"
             << "| " << setw(20) << "NIP"
             << "| " << setw(30) << "Nama Karyawan"
             << "|" << endl;
        cout << string(80, '-') << endl;
        cout << left
             << "| " << setw(4)  << "1."
             << "| " << setw(20) << Div->namaDivisi;
        PointerKaryawan tempKaryawan = Div->karyawan;
        if (tempKaryawan != nullptr) {
            cout << "| " << setw(20) << tempKaryawan->NIP
                 << "| " << setw(30) << tempKaryawan->nama
                 << "|" << endl;
            tempKaryawan = tempKaryawan->next;
            while (tempKaryawan != nullptr) {
                cout << left
                    << "| " << setw(4)  << ""
                    << "| " << setw(20) << ""
                    << "| " << setw(20) << tempKaryawan->NIP
                    << "| " << setw(30) << tempKaryawan->nama
                    << "|" << endl;
                tempKaryawan = tempKaryawan->next;
            }
        } else {
            cout << "| " << setw(20) << ""
                 << "| " << setw(30) << ""
                 << "|" << endl;
        }
         cout << string(80, '-') << endl;
    }
}

void deleteDivisi(PointerDivisi& Div) {
    while(!isEmptyKaryawan(Div->karyawan)) {
        PointerKaryawan tempKaryawan;
        deleteFirstKaryawan(Div, tempKaryawan);
        delete tempKaryawan;
    }
}

void menu() {
    cout << "\n==========================================" << endl;
    cout << "           MENU MULTI LIST PERUSAHAAN       " << endl;
    cout << "============================================" << endl;
    cout << "  1. Insert First Karyawan " << endl;
    cout << "  2. Delete First Karyawan " << endl;
    cout << "  3. Insert First Divisi " << endl;
    cout << "  4. Delete First Divisi " << endl;
    cout << "  5. Tampilkan Semua" << endl;
    cout << "  6. Tampilkan Divisi" << endl;
    cout << "  0. Keluar" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "  Pilihan: ";
}

int main() {
    List DivisiPT;
    createList(DivisiPT);

    int pilihan;

    do {
        menu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                PointerKaryawan pBaru;
                string namaDivisi;
                if (isEmptyDivisi(DivisiPT)) {
                    cout << "Belum ada divisi. Silakan buat divisi terlebih dahulu." << endl;
                } else {
                    cout << "Masukkan nama divisi untuk menambahkan karyawan: ";
                    cin.ignore(40000, '\n'); getline(cin, namaDivisi);
                    PointerDivisi hasil;
                    bool found;
                    linearSearchDivisi(DivisiPT, namaDivisi, hasil, found);
                    if (found) {
                        cout << "\n--- Input Karyawan Baru ---" << endl;
                        createKaryawan(pBaru);
                        insertFirstKaryawan(hasil, pBaru);
                        cout << "Karyawan berhasil di-insert." << endl;
                    } else {
                        cout << "Divisi tidak ditemukan." << endl;
                    }
                }
                break;
            }
            case 2: {
                PointerKaryawan pHapus;
                string namaDivisi;
                if (isEmptyDivisi(DivisiPT)) {
                    cout << "Belum ada divisi. Silakan buat divisi terlebih dahulu." << endl;
                } else {
                    cout << "Masukkan nama divisi untuk menghapus karyawan: ";
                    cin.ignore(40000, '\n'); getline(cin, namaDivisi);
                    PointerDivisi hasil;
                    bool found;
                    linearSearchDivisi(DivisiPT, namaDivisi, hasil, found);
                    if (found) {
                        deleteFirstKaryawan(hasil, pHapus);
                        if (pHapus != nullptr) {
                            cout << "\nKaryawan \"" << pHapus->nama << "\" berhasil di-delete." << endl;
                            delete pHapus; 
                        }
                    } else {
                        cout << "Divisi tidak ditemukan." << endl;
                    }
                }
                break;
            }
            case 3: {
                PointerDivisi pBaru;
                cout << "\n--- Input Divisi Baru ---" << endl;
                createDivisi(pBaru);
                insertFirstDivisi(DivisiPT, pBaru);
                cout << "Divisi berhasil di-insert." << endl;
                break;
            }
            case 4: {
                PointerDivisi pHapus;
                deleteFirstDivisi(DivisiPT, pHapus);
                if (pHapus != nullptr) {
                    deleteDivisi(pHapus);
                    cout << "\nDivisi \"" << pHapus->namaDivisi << "\" berhasil di-delete." << endl;
                    delete pHapus; 
                }
                break;
            }
            case 5:
                traversalSemua(DivisiPT);
                break;
            case 6: {
                string namaDivisi;
                if (isEmptyDivisi(DivisiPT)) {
                    cout << "Belum ada divisi. Silakan buat divisi terlebih dahulu." << endl;
                } else {
                    cout << "Masukkan nama divisi untuk menampilkan karyawan: ";
                    cin.ignore(40000, '\n'); getline(cin, namaDivisi);
                    PointerDivisi hasil;
                    bool found;
                    linearSearchDivisi(DivisiPT, namaDivisi, hasil, found);
                    if (found) {
                        traversalDivisi(hasil);
                    } else {
                        cout << "Divisi tidak ditemukan." << endl;
                    }
                }
                break;
            }
            case 0: 
                cout << "\nProgram Selesai." << endl;
                while (!isEmptyDivisi(DivisiPT)) {
                    deleteDivisi(DivisiPT);
                    PointerDivisi temp = DivisiPT;
                    if (DivisiPT->next != nullptr) {
                        DivisiPT = DivisiPT->next;
                    } else {
                        DivisiPT = nullptr;
                    }
                    delete temp;
                }
                break;
            default:
                cin.clear();
                cin.ignore(40000, '\n');
                cout << "\nPilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);

    return 0;
}