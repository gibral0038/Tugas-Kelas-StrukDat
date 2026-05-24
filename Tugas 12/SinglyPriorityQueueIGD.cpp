/*  Nama program    : SinglyPriorityQueueIGD
    Nama Anggota    : Renadi Wilantara, Gibraldi Zilal Fachry, Muhammad Yunus Habiby, Azrel Sakhi Reswara
    NPM             : 140810240061, 140810250038, 140810250014, 140810250098
    Tanggal buat    : 20 Mei 2026
    Deskripsi       : Priority Queue Singly Linked List IGD 
******************************************************/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Pasien {
    string IDPasien;
    string nama;
    int triase;
};

struct ElementQueue {
    Pasien info;
    int Priority;
    ElementQueue* next;
};

typedef ElementQueue* Pointer;
typedef Pointer List;

struct Queue {
    List head;
    List tail;
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

bool isempty(Queue Q) {
    return Q.head == nullptr;
}

void createQueue(Queue& Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

void inputPasien (Pointer& P) {
    P = new ElementQueue;
    cout << "ID Pasien  : "; cin >> P->info.IDPasien;
    cout << "Nama       : "; cin.clear(); cin.ignore(400000,'\n'); getline(cin, P->info.nama);
    P->info.triase = triase();
    P->Priority = P->info.triase;
    P->next = nullptr;
}

void insertQueue(Queue& Q, Pointer newElement) {
    if (isempty(Q)) {
        Q.head = newElement;
        Q.tail = Q.head;
    } else {
        if (Q.head->Priority > newElement->Priority) {
            newElement->next = Q.head;
            Q.head = newElement;
        } else {
            Pointer temp = Q.head;
            do {
                if (temp->next == nullptr || temp->next->Priority > newElement->Priority) {
                    newElement->next = temp->next;
                    temp->next = newElement;
                    if (newElement->next == nullptr) {
                        Q.tail = newElement;
                    }
                    break;
                }
                temp = temp->next;
            } while (temp != nullptr);
        }
    }
}

void deleteQueue(Queue& Q, Pointer& delElement) {
    if (isempty(Q)) {
        cout << "\nAntrian Kosong." << endl;
    }
    else if (Q.head == Q.tail) {
        delElement = Q.head;
        Q.head = nullptr;
        Q.tail = nullptr;
    }
    else {
        delElement = Q.head;
        Q.head = Q.head->next;
    }
}

void traversal(Queue Q) {
    if (isempty(Q)) {
        cout << "Queue kosong." << endl;
    }
    else {
        cout << "\n";
        cout << string(73, '-') << endl;
        cout << setw(42) << " DAFTAR PASIEN IGD " << endl;
        cout << string(73, '-') << endl;
        cout << left
             << "| " << setw(4)  << "No"
             << "| " << setw(20) << "ID Pasien"
             << "| " << setw(30) << "Nama"
             << "| " << setw(10) << "Prioritas"
             << "|" << endl;
        cout << string(73, '-') << endl;

        int count = 0;
        Pointer temp = Q.head;
        while (temp != nullptr) {
            cout << left
                 << "| " << setw(4)  << count + 1
                 << "| " << setw(20) << temp->info.IDPasien
                 << "| " << setw(30) << temp->info.nama
                 << "| " << setw(10)  << temp->Priority
                 << "|" << endl;
            temp = temp->next;
            count++;
        }
        cout << string(73, '-') << endl;
    }
}

void menu() {
    cout << "\n==========================================" << endl;
    cout << "   MENU QUEUE IGD (Singly)" << endl;
    cout << "==========================================" << endl;
    cout << "  1. InsertQueue (Tambah Pasien)" << endl;
    cout << "  2. DeleteQueue (Hapus Pasien Terdepan)" << endl;
    cout << "  3. Traversal   (Tampilkan Semua)" << endl;
    cout << "  0. Keluar" << endl;
    cout << "------------------------------------------" << endl;
    cout << "  Pilihan: ";
}

int main() {
    Queue PasienIGD;
    createQueue(PasienIGD);

    int pilihan;

    do {
        menu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                Pointer newElement;
                cout << "\n--- Input Pasien Baru ---" << endl;
                inputPasien(newElement);
                insertQueue(PasienIGD, newElement);
                cout << "Pasien berhasil di-insert." << endl;
                break;
            }
            case 2: {
                Pointer delElement;
                if (isempty(PasienIGD)) {
                    cout << "\nQueue kosong." << endl;
                } else {
                    deleteQueue(PasienIGD, delElement);
                    cout << "\nPasien \"" << delElement->info.nama << "\" berhasil di-delete." << endl;
                    delete delElement; 
                }
                break;
            }
            case 3:
                traversal(PasienIGD);
                break;
            case 0:
                cout << "\nProgram Selesai." << endl;
                while (!isempty(PasienIGD)) {
                    Pointer temp;
                    deleteQueue(PasienIGD, temp);
                    delete temp;
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