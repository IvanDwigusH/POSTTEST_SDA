#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

// Fungsi push: menambah elemen ke atas stack
void push(Node*& top, char data) {
    Node* newNode = new Node; // buat node baru
    newNode->data = data;     // isi datanya dengan karakter kurung
    newNode->next = top;      // sambungkan ke node paling atas sebelumnya
    top = newNode;            // ubah top jadi node baru
}

// Fungsi untuk menghapus elemen dari stack
char pop(Node*& top) {
    if (top == NULL) return '\0'; // kalau kosong, return karakter null
    Node* temp = top;             // simpan node paling atas sementara
    char poppedValue = temp->data; // ambil data dari node atas
    top = top->next;              // pindahkan top ke node di bawahnya
    delete temp;                  // hapus node lama untuk bebas memori
    return poppedValue;           // kembalikan data yang di-pop
}

string reverseString(string s) {
    Node* stackTop = NULL;
    string reversed = "";

    // --- Proses push setiap karakter ke stack ---
    for (int i = 0; i < s.length(); i++) {
        push(stackTop, s[i]);
    }

    // --- Proses pop untuk membalik string ---
    while (stackTop != NULL) {
        reversed += pop(stackTop);
    }

    return reversed;
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl; // Output: ataD rutkutrS
    return 0;
}

/*
Program ini membalik string dengan konsep stack berbasis linked list.
Setiap karakter dimasukkan (push) ke stack, lalu dikeluarkan (pop).
Karena sifat LIFO, urutannya otomatis terbalik.
*/

