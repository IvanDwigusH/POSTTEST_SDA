#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk stack
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

// Fungsi pop: mengambil elemen dari atas stack
char pop(Node*& top) {
    if (top == NULL) return '\0'; // kalau kosong, return karakter null
    Node* temp = top;             // simpan node paling atas sementara
    char poppedValue = temp->data; // ambil data dari node atas
    top = top->next;              // pindahkan top ke node di bawahnya
    delete temp;                  // hapus node lama untuk bebas memori
    return poppedValue;           // kembalikan data yang di-pop
}

// Fungsi untuk cek apakah pasangan kurung cocok
bool isMatchingPair(char open, char close) {
    // Jika kurung buka dan tutup pasangannya sesuai
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

// Fungsi utama untuk memeriksa keseimbangan kurung
bool areBracketsBalanced(string expr) {
    Node* stackTop = NULL; // buat stack kosong untuk menyimpan kurung buka

    // Loop tiap karakter di string
    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i]; // ambil satu karakter

        // Jika kurung buka, push ke stack
        if (c == '(' || c == '{' || c == '[') {
            push(stackTop, c);
        }
        // Jika kurung tutup, cek pasangan
        else if (c == ')' || c == '}' || c == ']') {
            if (stackTop == NULL) {
                // kalau stack kosong tapi ada kurung tutup, tidak seimbang
                return false;
            }

            // pop kurung buka terakhir dari stack
            char topChar = pop(stackTop);

            // cek apakah pasangan buka-tutup cocok
            if (!isMatchingPair(topChar, c)) {
                return false; // kalau tidak cocok, tidak seimbang
            }
        }
    }

    // setelah loop selesai, stack harus kosong kalau seimbang
    bool balanced = (stackTop == NULL);

    // bersihkan sisa node kalau masih ada (mencegah memory leak)
    while (stackTop != NULL) {
        pop(stackTop);
    }

    return balanced;
}

int main() {
    // Tes contoh pertama (seimbang)
    string expr1 = "{[()]}";
    cout << expr1 << " -> " 
         << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") 
         << endl;

    // Tes contoh kedua (tidak seimbang)
    string expr2 = "{[(])}";
    cout << expr2 << " -> " 
         << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") 
         << endl;

    return 0;
}

