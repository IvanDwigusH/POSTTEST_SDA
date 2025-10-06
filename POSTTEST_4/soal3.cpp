#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk menyimpan dokumen
struct Node {
    string document; // nama dokumen yang akan diproses
    Node* next;      // pointer ke node berikutnya
};

// Fungsi enqueue: menambahkan dokumen ke antrian
void enqueue(Node*& front, Node*& rear, string document) {
    Node* newNode = new Node;  // buat node baru
    newNode->document = document; // isi data dokumen
    newNode->next = NULL;         // node baru selalu jadi elemen terakhir

    // Jika queue kosong (belum ada antrian)
    if (front == NULL) {
        front = rear = newNode;   // front dan rear menunjuk ke node baru
    } 
    // Jika queue sudah ada isinya
    else {
        rear->next = newNode;     // sambungkan node baru di belakang
        rear = newNode;           // ubah rear agar menunjuk ke node baru
    }
}

// Fungsi dequeue: menghapus dokumen dari antrian (yang paling depan)
string dequeue(Node*& front, Node*& rear) {
    if (front == NULL) return ""; // kalau antrian kosong, kembalikan string kosong

    Node* temp = front;           // simpan node paling depan
    string docName = temp->document; // ambil nama dokumen
    front = front->next;          // geser front ke node berikutnya

    // Jika setelah dequeue antrian jadi kosong
    if (front == NULL) {
        rear = NULL;              // reset rear juga jadi NULL
    }

    delete temp;                  // hapus node lama untuk membebaskan memori
    return docName;               // kembalikan nama dokumen yang dihapus
}

// Fungsi untuk memproses semua dokumen di antrian
void processAllDocuments(Node*& front, Node*& rear) {
    // Loop selama antrian belum kosong
    while (front != NULL) {
        string currentDoc = dequeue(front, rear); // ambil dokumen paling depan
        cout << "Memproses: " << currentDoc << endl; // tampilkan dokumen yang sedang diproses
    }
}

int main() {
    Node* front = NULL; // pointer ke elemen depan antrian
    Node* rear = NULL;  // pointer ke elemen belakang antrian

    // Tambahkan beberapa dokumen ke antrian printer
    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");

    // Proses seluruh antrian
    cout << "Memulai pemrosesan antrian printer:" << endl;
    processAllDocuments(front, rear);

    return 0;
}
