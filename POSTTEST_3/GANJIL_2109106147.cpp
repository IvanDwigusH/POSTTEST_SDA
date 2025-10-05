#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <algorithm>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define CLEAR "cls"

// Struktur data untuk Double Linked List
struct Node {
    int id;
    string namaItem;
    int jumlah;
    string tipe;
    string rarity;
    Node* prev;
    Node* next;
};

Node* head = NULL;
Node* tail = NULL;
int nextID = 1; // auto increment ID

string nama = "Ivan Dwigus Herdiyan";
string nim  = "2109106147";

// ---------- Utility ----------
int getJumlahAwal() {
    if (nim.size() < 2) return 1;
    int duaDigit = atoi(nim.substr(nim.size() - 2).c_str());
    return duaDigit;
}
int getPosisiSisip() {
    int lastDigit = nim[nim.size() - 1] - '0';
    return (lastDigit == 0) ? 2 : lastDigit + 1;
}
// ---------- Validasi Input ----------
string inputNama() {
    string n;
    do {
        cout << "Nama item (contoh: Sword, Potion, Shield): ";
        getline(cin, n);
        if (n.size() < 2) cout << RED << "Nama item minimal 2 huruf!\n" << RESET;
    } while (n.size() < 2);
    return n;
}
string inputTipe() {
    string t;
    do {
        cout << "Tipe item (contoh: Weapon, Consumable, Armor): ";
        getline(cin, t);
        if (t.empty()) cout << RED << "Tipe item tidak boleh kosong!\n" << RESET;
    } while (t.empty());
    return t;
}
string inputRarity() {
    string r;
    const string valid[] = {"Common","Rare","Epic","Legendary"};
    bool ok;
    do {
        cout << "Rarity (Common, Rare, Epic, Legendary): ";
        getline(cin, r);
        if (!r.empty()) {
            r[0] = toupper(r[0]);
            for (size_t i=1; i<r.size(); i++) r[i] = tolower(r[i]);
        }
        ok = false;
        for (int i=0; i<4; i++)
            if (r == valid[i]) { ok = true; break; }
        if (!ok) cout << RED << "Rarity harus salah satu dari: Common, Rare, Epic, Legendary!\n" << RESET;
    } while (!ok);
    return r;
}

// ---------- Node creation ----------
Node* buatNode(const string& namaItem, const string& tipe, const string& rarity) {
    Node* nodeBaru = new Node;
    nodeBaru->id = nextID++;
    nodeBaru->namaItem = namaItem;
    nodeBaru->tipe = tipe;
    nodeBaru->rarity = rarity;
    nodeBaru->jumlah = getJumlahAwal();
    nodeBaru->prev = NULL;
    nodeBaru->next = NULL;
    return nodeBaru;
}

// ---------- Display ----------
void tampilkanInventory() {
    cout << CYAN << "\n=== INVENTORY (dari depan) ===\n" << RESET;
    Node* temp = head;
    if (!temp) { cout << "(Kosong)\n"; return; }
    while (temp) {
        cout << "[" << temp->id << "] " << temp->namaItem 
             << " | Jumlah: " << temp->jumlah 
             << " | Tipe: " << temp->tipe
             << " | Rarity: " << temp->rarity << endl;
        temp = temp->next;
    }
}
void tampilkanDariBelakang() {
    cout << CYAN << "\n=== INVENTORY (dari belakang) ===\n" << RESET;
    Node* temp = tail;
    if (!temp) { cout << "(Kosong)\n"; return; }
    while (temp) {
        cout << "[" << temp->id << "] " << temp->namaItem 
             << " | Jumlah: " << temp->jumlah 
             << " | Tipe: " << temp->tipe
             << " | Rarity: " << temp->rarity << endl;
        temp = temp->prev;
    }
}

// ---------- Core Features ----------
void tambahItemBaru(const string& namaItem, const string& tipe, const string& rarity) {
    Node* nodeBaru = buatNode(namaItem, tipe, rarity);
    if (!head) {
        head = tail = nodeBaru;
        return;
    }
    tail->next = nodeBaru;
    nodeBaru->prev = tail;
    tail = nodeBaru;
}

void sisipItem(const string& namaItem, const string& tipe, const string& rarity) {
    Node* nodeBaru = buatNode(namaItem, tipe, rarity);
    int pos = getPosisiSisip();
    if (pos <= 1 || !head) {
        nodeBaru->next = head;
        if (head) head->prev = nodeBaru;
        head = nodeBaru;
        if (!tail) tail = nodeBaru;
        return;
    }
    Node* temp = head;
    for (int i=1; temp->next && i<pos-1; i++) temp = temp->next;
    nodeBaru->next = temp->next;
    if (temp->next) temp->next->prev = nodeBaru;
    temp->next = nodeBaru;
    nodeBaru->prev = temp;
    if (!nodeBaru->next) tail = nodeBaru;
}

void hapusItemTerakhir() {
    if (!tail) { cout << RED << "Inventory kosong!\n" << RESET; return; }
    Node* hapus = tail;
    if (tail->prev) tail->prev->next = NULL;
    tail = tail->prev;
    if (!tail) head = NULL;
    delete hapus;
    cout << YELLOW << "Item terakhir dihapus.\n" << RESET;
}

void gunakanItem(const string& namaItem) {
    Node* temp = head;
    while (temp) {
        if (temp->namaItem == namaItem) {
            temp->jumlah--;
            if (temp->jumlah <= 0) {
                if (temp->prev) temp->prev->next = temp->next;
                else head = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                else tail = temp->prev;
                cout << YELLOW << "Item \"" << namaItem << "\" habis dan dihapus!\n" << RESET;
                delete temp;
            } else cout << GREEN << "Gunakan " << namaItem << ", sisa: " << temp->jumlah << RESET << endl;
            return;
        }
        temp = temp->next;
    }
    cout << RED << "Item tidak ditemukan!\n" << RESET;
}

void searchItem(const string& namaItem) {
    Node* temp = head;
    while (temp) {
        if (temp->namaItem == namaItem) {
            cout << GREEN << "Item ditemukan: [" << temp->id << "] " << temp->namaItem 
                 << " (" << temp->tipe << ", " << temp->rarity 
                 << ", jumlah: " << temp->jumlah << ")\n" << RESET;
            return;
        }
        temp = temp->next;
    }
    cout << RED << "Item tidak ada di inventory.\n" << RESET;
}

void detailItem() {
    cout << "Cari berdasarkan (1) ID atau (2) Nama? ";
    int opsi; cin >> opsi; cin.ignore();
    Node* temp = head;
    bool found = false;
    if (opsi == 1) {
        int id; cout << "Masukkan ID item: "; cin >> id; cin.ignore();
        while (temp) {
            if (temp->id == id) {
                cout << CYAN << "\n=== DETAIL ITEM ===\n" << RESET;
                cout << "ID      : " << temp->id << endl;
                cout << "Nama    : " << temp->namaItem << endl;
                cout << "Jumlah  : " << temp->jumlah << endl;
                cout << "Tipe    : " << temp->tipe << endl;
                cout << "Rarity  : " << temp->rarity << endl;
                found = true;
                break;
            }
            temp = temp->next;
        }
    } else {
        string namaCari; 
        cout << "Masukkan nama item: "; getline(cin, namaCari);
        while (temp) {
            if (temp->namaItem == namaCari) {
                cout << CYAN << "\n=== DETAIL ITEM ===\n" << RESET;
                cout << "ID      : " << temp->id << endl;
                cout << "Nama    : " << temp->namaItem << endl;
                cout << "Jumlah  : " << temp->jumlah << endl;
                cout << "Tipe    : " << temp->tipe << endl;
                cout << "Rarity  : " << temp->rarity << endl;
                found = true;
                break;
            }
            temp = temp->next;
        }
    }
    if (!found) cout << RED << "Item tidak ditemukan.\n" << RESET;
}

void clearInventory() {
    char konfirmasi;
    cout << YELLOW << "Yakin hapus semua item? (y/n): " << RESET;
    cin >> konfirmasi;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << GREEN << "Dibatalkan.\n" << RESET;
        return;
    }
    Node* temp = head;
    while (temp) {
        Node* hapus = temp;
        temp = temp->next;
        delete hapus;
    }
    head = tail = NULL;
    cout << YELLOW << "Semua item dihapus!\n" << RESET;
}

int countTotalItems() {
    int total = 0;
    Node* temp = head;
    while (temp) { total += temp->jumlah; temp = temp->next; }
    return total;
}

// ---------- Menu ----------
void tungguKembali() {
    cout << "\nTekan 0 lalu ENTER untuk kembali ke menu utama...";
    int dummy;
    while (true) {
        cin >> dummy;
        if (dummy == 0) break;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void menu() {
    int pilihan;
    do {
        system(CLEAR);
        cout << CYAN << "+--------------------------------------+\n";
        cout << "     GAME INVENTORY MANAGEMENT (DLL)\n";
        cout << "     [" << nama << " - " << nim << "]\n";
        cout << "+--------------------------------------+" << RESET << "\n";
        cout << "1. Tambah Item Baru\n";
        cout << "2. Sisipkan Item\n";
        cout << "3. Hapus Item Terakhir\n";
        cout << "4. Gunakan Item\n";
        cout << "5. Tampilkan Inventory (depan)\n";
        cout << "6. Tampilkan Inventory (belakang)\n";
        cout << "7. Cari Item\n";
        cout << "8. Lihat Detail Item\n";
        cout << "9. Hapus Semua Item\n";
        cout << "10. Hitung Total Jumlah Item\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan; cin.ignore();

        system(CLEAR);

        if (pilihan == 1) {
            tampilkanInventory();
            string n = inputNama(), t = inputTipe(), r = inputRarity();
            tambahItemBaru(n, t, r);
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 2) {
            tampilkanInventory();
            string n = inputNama(), t = inputTipe(), r = inputRarity();
            sisipItem(n, t, r);
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 3) {
            tampilkanInventory();
            hapusItemTerakhir();
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 4) {
            tampilkanInventory();
            string n = inputNama();
            gunakanItem(n);
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 5) {
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 6) {
            tampilkanDariBelakang();
            tungguKembali();
        } else if (pilihan == 7) {
            tampilkanInventory();
            string n = inputNama();
            searchItem(n);
            tungguKembali();
        } else if (pilihan == 8) {
            tampilkanInventory();
            detailItem();
            tungguKembali();
        } else if (pilihan == 9) {
            tampilkanInventory();
            clearInventory();
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 10) {
            tampilkanInventory();
            cout << "\nTotal semua item = " << countTotalItems() << endl;
            tungguKembali();
        }
    } while (pilihan != 0);
}

int main() {
    menu();
    return 0;
}

