#include <iostream>
using namespace std;

// Struktur Node untuk Binary Tree
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor untuk membuat node baru
    Node(int val) {
        data = val;
        left = NULL;   // anak kiri belum ada
        right = NULL;  // anak kanan belum ada
    }
};

// Fungsi insert untuk membangun tree BST
Node* insert(Node* root, int val) {
    // Kalau tree kosong, buat node baru
    if (root == NULL) {
        return new Node(val);
    }
    // Kalau nilai lebih kecil, masuk subtree kiri
    if (val < root->data) {
        root->left = insert(root->left, val);
    } 
    // Kalau nilai lebih besar, masuk subtree kanan
    else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    // Kembalikan root setelah selesai insert
    return root;
}

/**
 * Fungsi untuk mencari nilai terbesar dalam BST
 */
int findMaxValue(Node* root) {
    // Kalau tree kosong, kembalikan -1
    if (root == NULL) {
        return -1;
    }

    // Selama masih ada anak kanan, geser terus ke kanan
    while (root->right != NULL) {
        root = root->right;
    }

    // Node paling kanan adalah nilai terbesar
    return root->data;
}

int main() {
    Node* root = NULL;  // Tree awal masih kosong

    // Masukkan data ke dalam BST
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 80);

    // Cetak hasil nilai terbesar
    cout << "Nilai terbesar dalam tree adalah: " << findMaxValue(root) << endl; // Output: 80

    return 0;
}

