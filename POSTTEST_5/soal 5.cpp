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
    // Kalau nilai lebih kecil, taruh di kiri
    if (val < root->data) {
        root->left = insert(root->left, val);
    } 
    // Kalau nilai lebih besar, taruh di kanan
    else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    // Kembalikan root setelah proses selesai
    return root;
}

/**
 * Fungsi untuk traversal pre-order (root, left, right)
 */
void preOrderTraversal(Node* root) {
    // Base case: kalau node kosong, langsung kembali
    if (root == NULL) {
        return;
    }

    // Cetak data node sekarang (karena pre-order: root dulu)
    cout << root->data << " ";

    // Rekursif ke subtree kiri
    preOrderTraversal(root->left);

    // Rekursif ke subtree kanan
    preOrderTraversal(root->right);
}

int main() {
    Node* root = NULL;  // Tree awal kosong

    // Masukkan data ke dalam BST
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    // Cetak hasil traversal pre-order
    cout << "Pre-order traversal dari tree adalah: ";
    preOrderTraversal(root); // Output: 50 30 20 40 70 60 80
    cout << endl;

    return 0;
}

