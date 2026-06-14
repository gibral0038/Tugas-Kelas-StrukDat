/* Nama program    : GraphSoalB
     Nama Anggota    : Renadi Wilantara, Gibraldi Zilal Fachry, Muhammad Yunus Habiby, Azrel Sakhi Reswara
     NPM             : 140810240061, 140810250038, 140810250014, 140810250098
     Tanggal buat    : 14 Juni 2026
     Deskripsi       : Graph dengan adjacency list, BFS, dan DFS disertai Menu Pilihan
                       (Soal B: struktur graf sama seperti Soal A, label simpul diubah)
******************************************************/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct AdjListNode {
    int data;
    AdjListNode* next;
};

struct AdjList {
    AdjListNode* head;
};

struct Graph {
    int V;
    AdjList* arr;
};

AdjListNode* newAdjListNode(int data) {
    AdjListNode* node = new AdjListNode;
    node->data = data;
    node->next = nullptr;
    return node;
}

Graph* createGraph(int V) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->arr = new AdjList[V];
    for (int i = 0; i < V; i++) {
        graph->arr[i].head = nullptr;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    AdjListNode* node = newAdjListNode(dest);
    node->next = graph->arr[src].head;
    graph->arr[src].head = node;

    node = newAdjListNode(src);
    node->next = graph->arr[dest].head;
    graph->arr[dest].head = node;
}

void printGraph(Graph* graph) {
    // label simpul yang dipakai pada Soal B adalah 2..9
    for (int i = 2; i < graph->V; i++) {
        cout << "Adjacency list vertex " << i << ": ";
        AdjListNode* temp = graph->arr[i].head;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }
}

void BFS(Graph* graph, int startVertex) {
    vector<bool> visited(graph->V, false);
    queue<int> q;
    visited[startVertex] = true;
    q.push(startVertex);

    cout << "\nHasil Penelusuran BFS (dimulai dari simpul " << startVertex << "): ";
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";

        AdjListNode* temp = graph->arr[curr].head;
        while (temp != nullptr) {
            int adj = temp->data;
            if (!visited[adj]) {
                visited[adj] = true;
                q.push(adj);
            }
            temp = temp->next;
        }
    }
    cout << "\n" << endl;
}

void DFSUtil(Graph* graph, int vertex, vector<bool>& visited) {
    visited[vertex] = true;
    cout << vertex << " ";

    AdjListNode* temp = graph->arr[vertex].head;
    while (temp != nullptr) {
        int adj = temp->data;
        if (!visited[adj]) {
            DFSUtil(graph, adj, visited);
        }
        temp = temp->next;
    }
}

void DFS(Graph* graph, int startVertex) {
    vector<bool> visited(graph->V, false);
    cout << "\nHasil Penelusuran DFS (dimulai dari simpul " << startVertex << "): ";
    DFSUtil(graph, startVertex, visited);
    cout << "\n" << endl;
}

int main() {
    // Label simpul Soal B: 2..9 (label maksimum = 9, jadi ukuran array = 10)
    int totalVertices = 10;
    Graph* graph = createGraph(totalVertices);

    // Inisialisasi struktur graf sesuai Soal B (label sudah diubah)
    addEdge(graph, 4, 9);
    addEdge(graph, 4, 6);
    addEdge(graph, 9, 6);
    addEdge(graph, 9, 2);
    addEdge(graph, 9, 7);
    addEdge(graph, 6, 3);
    addEdge(graph, 6, 8);
    addEdge(graph, 2, 5);
    addEdge(graph, 7, 5);
    addEdge(graph, 3, 5);
    addEdge(graph, 8, 5);

    int pilihan;
    int startVertex;

    do {
        cout << "=== MENU PROGRAM GRAPH ===" << endl;
        cout << "1. Tampilkan Representasi Graph (Adjacency List)" << endl;
        cout << "2. Penelusuran Breadth-First Search (BFS)" << endl;
        cout << "3. Penelusuran Depth-First Search (DFS)" << endl;
        cout << "4. Keluar" << endl;
        cout << "==========================" << endl;
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\n=== REPRESENTASI GRAPH ===" << endl;
                printGraph(graph);
                cout << "==========================\n" << endl;
                break;
            case 2:
                cout << "Masukkan simpul awal penelusuran BFS (2-9): ";
                cin >> startVertex;
                if (startVertex >= 2 && startVertex <= 9) {
                    BFS(graph, startVertex);
                } else {
                    cout << "Error: Simpul tidak valid!\n" << endl;
                }
                break;
            case 3:
                cout << "Masukkan simpul awal penelusuran DFS (2-9): ";
                cin >> startVertex;
                if (startVertex >= 2 && startVertex <= 9) {
                    DFS(graph, startVertex);
                } else {
                    cout << "Error: Simpul tidak valid!\n" << endl;
                }
                break;
            case 4:
                cout << "Keluar dari program. Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Silakan masukkan angka 1-4.\n" << endl;
        }
    } while (pilihan != 4);

    return 0;
}