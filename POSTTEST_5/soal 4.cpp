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
        left = NULL;   // anak kiri kosong
        right = NULL;  // anak kanan kosong
    }
};

// Fungsi insert untuk membangun tree BST
Node* insert(Node* root, int val) {
    // Kalau tree masih kosong, buat node baru
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
    // Kembalikan root
    return root;
}

/**
 * Fungsi untuk melakukan traversal post-order (left, right, root)
 */
void postOrderTraversal(Node* root) {
    // Base case: kalau node kosong, langsung kembali
    if (root == NULL) {
        return;
    }

    // Telusuri subtree kiri dulu
    postOrderTraversal(root->left);

    // Lalu telusuri subtree kanan
    postOrderTraversal(root->right);

    // Terakhir baru cetak data node saat ini
    cout << root->data << " ";
}

int main() {
    Node* root = NULL;  // Mulai dengan tree kosong

    // Masukkan data ke dalam tree
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    // Cetak hasil traversal post-order
    cout << "Post-order traversal dari tree adalah: ";
    postOrderTraversal(root); // Output: 20 40 30 60 80 70 50
    cout << endl;

    return 0;
}

