#include <iostream>
using namespace std;

// Struktur Node untuk circular doubly linked list
struct Node {
    int data;    // nilai data node
    Node* next;  // pointer ke node berikutnya
    Node* prev;  // pointer ke node sebelumnya
};

// Fungsi untuk menyisipkan node baru agar urutan tetap ascending
void sortedInsert(Node *&head_ref, int data) {
    Node* newNode = new Node;  // buat node baru
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    // Kasus 1: List masih kosong
    if (head_ref == NULL) {
        newNode->next = newNode; // next menunjuk dirinya sendiri
        newNode->prev = newNode; // prev juga menunjuk dirinya sendiri
        head_ref = newNode;      // head menunjuk node baru
        return;
    }

    Node* last = head_ref->prev; // node terakhir (karena list circular)

    // Kasus 2: Data baru lebih kecil dari head (sisipkan di awal)
    if (data < head_ref->data) {
        newNode->next = head_ref;     // node baru menunjuk head lama
        newNode->prev = last;         // node baru menunjuk tail lama
        head_ref->prev = newNode;     // head lama menunjuk balik ke node baru
        last->next = newNode;         // tail lama menunjuk ke node baru
        head_ref = newNode;           // update head ke node baru (karena paling kecil)
        return;
    }

    // Kasus 3: Sisipkan di tengah atau di akhir
    Node* current = head_ref;

    // cari posisi di mana data saat ini lebih besar dari data baru
    while (current->next != head_ref && current->next->data < data) {
        current = current->next;
    }

    // Sisipkan setelah current
    newNode->next = current->next; // newNode menunjuk ke node setelah current
    newNode->prev = current;       // newNode menunjuk balik ke current
    current->next->prev = newNode; // node setelah current menunjuk balik ke newNode
    current->next = newNode;       // current menunjuk ke newNode

}

// Fungsi untuk mencetak list secara sirkular
void printList(Node *head_ref) {
    if (head_ref == NULL) {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do {
        cout << current->data << " ";  // tampilkan data
        current = current->next;       // pindah ke node berikutnya
    } while (current != head_ref);     // berhenti kalau sudah kembali ke head
    cout << endl;
}

int main() {
    Node *head = NULL; // inisialisasi list kosong

    // Menyisipkan data secara acak (program akan urut otomatis)
    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 40);
    sortedInsert(head, 20);

    cout << "Circular Doubly Linked List (sorted): ";
    // Output yang diharapkan: 10 20 30 40
    printList(head);

    return 0;
}
