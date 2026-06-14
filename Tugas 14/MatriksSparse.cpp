/*  Nama program    : MatriksSparse
    Nama Anggota    : Renadi Wilantara, Gibraldi Zilal Fachry, Muhammad Yunus Habiby, Azrel Sakhi Reswara
    NPM             : 140810240061, 140810250038, 140810250014, 140810250098
    Tanggal buat    : 02 Juni 2026
    Deskripsi       : MatriksSparse
******************************************************/
#include <iostream>
using namespace std;

struct ElementNode {
    int row;
    int column;
    int value;
    ElementNode* right;     
    ElementNode* down;      
};

struct HeaderNode {
    int indexValue;         
    HeaderNode* nextHeader; 
    ElementNode* firstElem; 
};

struct SparseMatrix {
    int totalRows;
    int totalCols;
    HeaderNode* rowHead;    
    HeaderNode* colHead;    
};

void destroyMatrix(SparseMatrix& M) {
    HeaderNode* currRow = M.rowHead;
    while (currRow != NULL) {
        ElementNode* currElem = currRow->firstElem;
        while (currElem != NULL) {
            ElementNode* tempElem = currElem;
            currElem = currElem->right; 
            delete tempElem;            
        }
        HeaderNode* tempRow = currRow;
        currRow = currRow->nextHeader;  
        delete tempRow;                 
    }

    HeaderNode* currCol = M.colHead;
    while (currCol != NULL) {
        HeaderNode* tempCol = currCol;
        currCol = currCol->nextHeader;  
        delete tempCol;                 
    }

    M.rowHead = NULL;
    M.colHead = NULL;
    M.totalRows = 0;
    M.totalCols = 0;
}

void createNewMatrix(SparseMatrix& M) {
    M.colHead = NULL;
    M.rowHead = NULL;
    M.totalCols = 0;
    M.totalRows = 0;
}

void createMatrix(SparseMatrix& M, int rows, int cols) {
    if (M.rowHead != NULL || M.colHead != NULL) {
        destroyMatrix(M);
    }
    M.totalRows = rows;
    M.totalCols = cols;
    M.rowHead = NULL;
    M.colHead = NULL;

    HeaderNode* lastRow = NULL;
    for (int i = 0; i < rows; i++) {
        HeaderNode* newRow = new HeaderNode{i, NULL, NULL};
        if (M.rowHead == NULL) M.rowHead = newRow;
        else lastRow->nextHeader = newRow;
        lastRow = newRow;
    }

    HeaderNode* lastCol = NULL;
    for (int j = 0; j < cols; j++) {
        HeaderNode* newCol = new HeaderNode{j, NULL, NULL};
        if (M.colHead == NULL) M.colHead = newCol;
        else lastCol->nextHeader = newCol;
        lastCol = newCol;
    }
}

void insertElement(SparseMatrix& M, int r, int c, int val) {
    if (val == 0) cout << "Tidak perlu menyimpan elemen nol!" << endl;
    else {
        ElementNode* newElem = new ElementNode{r, c, val, NULL, NULL};

        HeaderNode* currRow = M.rowHead;
        while (currRow != NULL && currRow->indexValue != r) {
            currRow = currRow->nextHeader;
        }
        if (currRow != NULL) {
            if (currRow->firstElem == NULL || currRow->firstElem->column > c) {
                newElem->right = currRow->firstElem;
                currRow->firstElem = newElem;
            } else {
                ElementNode* temp = currRow->firstElem;
                while (temp->right != NULL && temp->right->column < c) {
                    temp = temp->right;
                }
                newElem->right = temp->right;
                temp->right = newElem;
            }
        }

        HeaderNode* currCol = M.colHead;
        while (currCol != NULL && currCol->indexValue != c) {
            currCol = currCol->nextHeader;
        }
        if (currCol != NULL) {
            if (currCol->firstElem == NULL || currCol->firstElem->row > r) {
                newElem->down = currCol->firstElem;
                currCol->firstElem = newElem;
            } else {
                ElementNode* temp = currCol->firstElem;
                while (temp->down != NULL && temp->down->row < r) {
                    temp = temp->down;
                }
                newElem->down = temp->down;
                temp->down = newElem;
            }
        }
    }
}

void inputMatrix(SparseMatrix& M, int id) {
    int nonZeroCount;
    cout << "\n--- Input Data Matriks[" << id << "] ---" << endl;
    cout << "Masukkan jumlah elemen bukan nol: ";
    cin >> nonZeroCount;

    for (int i = 0; i < nonZeroCount; i++) {
        int r, c, val;
        cout << "Data ke-" << i + 1 << " (Baris Kolom Nilai): ";
        cout << "Baris: "; cin >> r;
        cout << "Kolom: "; cin >> c;
        cout << "Nilai: "; cin >> val;
        
        if (r >= M.totalRows || c >= M.totalCols || r < 0 || c < 0) {
            cout << "Koordinat di luar jangkauan matriks! Silakan ulangi." << endl;
            i--; 
        } else {
            insertElement(M, r, c, val);
        }
    }
}

void addMatrices(SparseMatrix A, SparseMatrix B, SparseMatrix& C, bool& isValid) {
    isValid = true;
    if (A.totalRows != B.totalRows || A.totalCols != B.totalCols) {
        cout << "Error: Dimensi matriks tidak sama!" << endl;
        isValid = false;
    }
    else {
        createMatrix(C, A.totalRows, A.totalCols);

        HeaderNode* rA = A.rowHead;
        HeaderNode* rB = B.rowHead;

        while (rA != NULL && rB != NULL) {
            ElementNode* eA = rA->firstElem;
            ElementNode* eB = rB->firstElem;
            int currRowIdx = rA->indexValue;

            while (eA != NULL && eB != NULL) {
                if (eA->column == eB->column) {
                    int sumResult = eA->value + eB->value;
                    if (sumResult != 0) {
                        insertElement(C, currRowIdx, eA->column, sumResult);
                    }
                    eA = eA->right;
                    eB = eB->right;
                } 
                else if (eA->column < eB->column) {
                    insertElement(C, currRowIdx, eA->column, eA->value);
                    eA = eA->right;
                } 
                else {
                    insertElement(C, currRowIdx, eB->column, eB->value);
                    eB = eB->right;
                }
            }

            while (eA != NULL) {
                insertElement(C, currRowIdx, eA->column, eA->value);
                eA = eA->right;
            }

            while (eB != NULL) {
                insertElement(C, currRowIdx, eB->column, eB->value);
                eB = eB->right;
            }

            rA = rA->nextHeader;
            rB = rB->nextHeader;
        }
    }
}

void printMatrix(SparseMatrix M) {
    HeaderNode* rCurr = M.rowHead;
    bool isEmpty = true;

    cout << "Baris\tKolom\tNilai" << endl;
    cout << "------------------------" << endl;
    
    while (rCurr != NULL) {
        ElementNode* eCurr = rCurr->firstElem;
        while (eCurr != NULL) {
            cout << eCurr->row << "\t" << eCurr->column << "\t" << eCurr->value << endl;
            isEmpty = false;
            eCurr = eCurr->right;
        }
        rCurr = rCurr->nextHeader;
    }

    if (isEmpty) {
        cout << "(Semua elemen bernilai nol)" << endl;
    }
    cout << endl;
}

void printMatrixFormatGrid(SparseMatrix M) {
    HeaderNode* currRow = M.rowHead;

    for (int i = 0; i < M.totalRows; i++) {
        // Ambil elemen pertama di baris ini
        ElementNode* currElem = (currRow != NULL) ? currRow->firstElem : NULL;
        
        for (int j = 0; j < M.totalCols; j++) {
            if (currElem != NULL && currElem->column == j) {
                cout << currElem->value << "\t";
                currElem = currElem->right; 
            } else {
                
                cout << "0\t";
            }
        }
        cout << endl;

        if (currRow != NULL) {
            currRow = currRow->nextHeader;
        }
    }
    cout << endl;
}

void inputSizeMatriks(SparseMatrix Matriks[], int n){
    for (int i = 0; i < n; i++){
        int baris, kolom;
        cout << "MATRIKS " << i + 1 << " : \n";
        cout << "Baris : "; cin >> baris;
        cout << "Kolom : "; cin >> kolom;
        createMatrix(Matriks[i], baris, kolom);
    }
}

void inputMatrixAll(SparseMatrix Matriks[], int n){
    for (int i = 0; i < n; i++){
        inputMatrix(Matriks[i], i);
    }
}

void printMatrixAll(SparseMatrix Matriks[], int n){
    for (int i = 0; i < n; i++){
        cout << "\n=== Matriks " << i + 1 << " ===" << endl;
        printMatrixFormatGrid(Matriks[i]);
    }
}

void display(){
    cout << "\n============================" << endl;
    cout << "=    Menu Matriks Sparse   =" << endl;
    cout << "============================" << endl;
    cout << "1. Input Ukuran Matriks" << endl;
    cout << "2. Input Isi Matriks" << endl;
    cout << "3. Tampilkan Matriks" << endl;
    cout << "4. Jumlahkan Matriks" << endl;
    cout << "5. Keluar" << endl;
    cout << "============================" << endl;
    cout << "Pilih menu (1-5): ";
}

int main() {
    SparseMatrix Matriks[2];
    SparseMatrix Hasil;
    createNewMatrix(Matriks[0]);
    createNewMatrix(Matriks[1]);
    createNewMatrix(Hasil);
    int jMatriks = 2; 
    int baris, kolom;
    cout << "=== PROGRAM PENJUMLAHAN MATRIKS SPARSE MULTI LIST ===\n\n" << endl;
    int pilih;
    bool isFill = false, isValued = false;
    do {
        display();
        cin >> pilih;
        switch (pilih) {
            case 1: {
                inputSizeMatriks(Matriks, 2);
                isFill = true;
                isValued = false;
                break;
            }
            case 2:
                if (!isFill) {
                    cout << "Silakan input ukuran matriks terlebih dahulu (Menu 1)!" << endl;
                } else {
                    inputMatrixAll(Matriks, 2);
                    isValued = true;
                }
                break;
            case 3:
                if (!isFill || !isValued) {
                    cout << "Silakan input ukuran dan isi matriks terlebih dahulu (Menu 1 dan 2)!" << endl;
                } else {
                    printMatrixAll(Matriks, 2);
                }
                break;
            case 4: {
                bool isValid;
                if (!isFill || !isValued) {
                    cout << "Silakan input ukuran dan isi matriks terlebih dahulu (Menu 1 dan 2)!" << endl;
                } else {
                    addMatrices(Matriks[0], Matriks[1], Hasil, isValid);
                    if (isValid) {
                        cout << "Hasil penjumlahan : " << endl;
                        printMatrixFormatGrid(Hasil);
                    } else {
                        cout << "Matriks tidak dapat dijumlahkan!" << endl;
                    }
                }
                break;
            }
            case 5: 
                cout << "Terima kasih telah menggunakan program ini!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan pilih antara 1-5." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
        }
    } while (pilih != 5);

    return 0;
}