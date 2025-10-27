#include <iostream>
using namespace std;

// Struktur Node untuk Binary Tree
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor untuk inisialisasi node baru
    Node(int val) {
        data = val;
        left = NULL;   // diganti dari nullptr ke NULL
        right = NULL;  // sama juga
    }
};

// Fungsi insert untuk membangun tree
Node* insert(Node* root, int val) {
    // Kalau root masih kosong, buat node baru
    if (root == NULL) {
        return new Node(val);
    }
    // Kalau nilai lebih kecil dari data root, masuk ke subtree kiri
    if (val < root->data) {
        root->left = insert(root->left, val);
    } 
    // Kalau nilai lebih besar, masuk ke subtree kanan
    else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    // Kembalikan root setelah proses insert selesai
    return root;
}

/**
 * Fungsi untuk menghitung jumlah total node dalam tree
 */
int countNodes(Node* root) {
    // Kalau tree kosong (root = NULL), berarti tidak ada node
    if (root == NULL) {
        return 0;
    }
    // Kalau ada node, hitung:
    // 1 untuk node ini + jumlah node di kiri + jumlah node di kanan
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    Node* root = NULL;  // Deklarasi root sebagai awal tree kosong

    // Menambahkan data ke tree secara bertahap
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);

    // Menampilkan hasil total node di tree
    cout << "Jumlah total node dalam tree adalah: " << countNodes(root) << endl; // Harusnya output: 4

    return 0;
}

