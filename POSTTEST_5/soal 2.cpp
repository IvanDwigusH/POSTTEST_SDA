#include <iostream>
using namespace std;

// Struktur Node untuk Binary Tree
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor untuk buat node baru
    Node(int val) {
        data = val;
        left = NULL;   // inisialisasi anak kiri kosong
        right = NULL;  // inisialisasi anak kanan kosong
    }
};

// Fungsi insert untuk membangun tree BST
Node* insert(Node* root, int val) {
    // Kalau tree masih kosong, buat node pertama
    if (root == NULL) {
        return new Node(val);
    }
    // Kalau nilai lebih kecil, masuk ke subtree kiri
    if (val < root->data) {
        root->left = insert(root->left, val);
    }
    // Kalau nilai lebih besar, masuk ke subtree kanan
    else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    // Kembalikan root setelah proses insert
    return root;
}

/**
 * Fungsi untuk mencari nilai terkecil dalam BST
 */
int findMinValue(Node* root) {
    // Kalau tree kosong, langsung kembalikan -1
    if (root == NULL) {
        return -1;
    }

    // Selama masih ada anak kiri, geser terus ke kiri
    while (root->left != NULL) {
        root = root->left;
    }

    // Node paling kiri adalah nilai terkecil
    return root->data;
}

int main() {
    Node* root = NULL;  // Mulai dengan tree kosong

    // Masukkan data ke dalam tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);

    // Cetak nilai terkecil di tree
    cout << "Nilai terkecil dalam tree adalah: " << findMinValue(root) << endl; // Output: 20

    return 0;
}

