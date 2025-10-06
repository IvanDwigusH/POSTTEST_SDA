#include <iostream>
using namespace std;

// Struktur Node untuk Circular Doubly Linked List
struct Node {
    int data;
    Node* next;
    Node* prev;
};

// Fungsi untuk menukar posisi head dan tail
void exchangeHeadAndTail(Node *&head_ref) {
    // Jika list kosong atau hanya 1 node, tidak perlu ditukar
    if (head_ref == NULL || head_ref->next == head_ref)
        return;

    Node* head = head_ref;
    Node* tail = head_ref->prev;
    Node* headNext = head->next;
    Node* tailPrev = tail->prev;

    // Jika hanya ada 2 node (head <-> tail)
    if (headNext == tail) {
        tail->next = head;
        tail->prev = head;
        head->next = tail;
        head->prev = tail;
        head_ref = tail; // tail jadi head baru
        return;
    }

    // Putus koneksi head & tail dengan posisinya
    headNext->prev = tail;
    tailPrev->next = head;

    // Tukar posisi head dan tail
    tail->next = headNext;
    tail->prev = head->prev; // tail lama jadi sebelum head lama (tetap circular)
    head->next = tail->next; // head lama di belakang tail lama
    head->prev = tailPrev;

    // Hubungkan ujung circular
    tailPrev->next = head;
    headNext->prev = tail;

    // Update koneksi antar head dan tail baru
    tail->next = headNext;
    head->prev = tailPrev;
    tail->prev = tailPrev;
    head->next = tail;

    // Update head_ref ke tail (karena tail sekarang di depan)
    head_ref = tail;
}

// Fungsi untuk mencetak isi list
void printList(Node *head_ref) {
    if (head_ref == NULL) {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

// Fungsi untuk menambah node di akhir list
void insertEnd(Node *&head_ref, int data) {
    Node *newNode = new Node;
    newNode->data = data;

    if (head_ref == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    Node *tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    tail->next = newNode;
    head_ref->prev = newNode;
}

int main() {
    Node *head = NULL;

    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    printList(head); // Expected: 5 2 3 4 1

    return 0;
}

