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

struct Node {
    string namaItem;
    int jumlah;
    string tipe;
    string rarity;
    Node* next;
};

Node* head = NULL;

string nama = "Ivan Dwigus Herdiyan";
string nim  = "2109106147";

int getJumlahAwal() {
    if (nim.size() < 2) return 1;
    int duaDigit = atoi(nim.substr(nim.size()-2).c_str());
    return duaDigit;
}

int getPosisiSisip() {
    int lastDigit = nim[nim.size()-1] - '0';
    return (lastDigit == 0) ? 2 : lastDigit + 1;
}

// ---------------- VALIDASI INPUT -----------------
string inputNama() {
    string n;
    do {
        cout << "Nama item (contoh: Sword, Potion, Shield): ";
        getline(cin, n);
        if (n.size() < 2) {
            cout << RED << "Nama item minimal 2 huruf!\n" << RESET;
        }
    } while (n.size() < 2);
    return n;
}

string inputTipe() {
    string t;
    do {
        cout << "Tipe item (contoh: Weapon, Consumable, Armor): ";
        getline(cin, t);
        if (t.empty()) {
            cout << RED << "Tipe item tidak boleh kosong!\n" << RESET;
        }
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
        for (int i=0; i<4; i++) {
            if (r == valid[i]) { ok = true; break; }
        }
        if (!ok) cout << RED << "Rarity harus salah satu dari: Common, Rare, Epic, Legendary!\n" << RESET;
    } while (!ok);
    return r;
}
// -------------------------------------------------

Node* buatNode(const string& namaItem, const string& tipe, const string& rarity) {
    Node* nodeBaru = new Node;
    nodeBaru->namaItem = namaItem;
    nodeBaru->tipe = tipe;
    nodeBaru->rarity = rarity;
    nodeBaru->jumlah = getJumlahAwal();
    nodeBaru->next = NULL;
    return nodeBaru;
}

void tampilkanInventory() {
    cout << CYAN << "\n=== INVENTORY ===\n" << RESET;
    Node* temp = head;
    int i = 1;
    while (temp) {
        cout << i++ << ". " << temp->namaItem 
             << " | Jumlah: " << temp->jumlah 
             << " | Tipe: " << temp->tipe
             << " | Rarity: " << temp->rarity << endl;
        temp = temp->next;
    }
    if (!head) cout << "(Kosong)\n";
}

void tambahItemBaru(const string& namaItem, const string& tipe, const string& rarity) {
    Node* nodeBaru = buatNode(namaItem, tipe, rarity);
    if (!head) { head = nodeBaru; return; }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = nodeBaru;
}

void sisipItem(const string& namaItem, const string& tipe, const string& rarity) {
    Node* nodeBaru = buatNode(namaItem, tipe, rarity);
    int pos = getPosisiSisip();
    if (pos <= 1 || !head) {
        nodeBaru->next = head;
        head = nodeBaru;
        return;
    }
    Node* temp = head;
    for (int i=1; temp && i<pos-1; i++) temp = temp->next;
    if (!temp) {
        tambahItemBaru(namaItem, tipe, rarity);
    } else {
        nodeBaru->next = temp->next;
        temp->next = nodeBaru;
    }
}

void hapusItemTerakhir() {
    if (!head) { cout << RED << "Inventory kosong!\n" << RESET; return; }
    if (!head->next) { delete head; head = NULL; return; }
    Node* temp = head;
    while (temp->next->next) temp = temp->next;
    delete temp->next;
    temp->next = NULL;
}

void gunakanItem(const string& namaItem) {
    Node* temp = head; Node* prev = NULL;
    while (temp) {
        if (temp->namaItem == namaItem) {
            temp->jumlah -= 1;
            if (temp->jumlah <= 0) {
                if (!prev) head = temp->next;
                else prev->next = temp->next;
                delete temp;
                cout << YELLOW << "Item \"" << namaItem << "\" habis dan dihapus!\n" << RESET;
            } else {
                cout << GREEN << "Gunakan " << namaItem << ", sisa: " << temp->jumlah << RESET << endl;
            }
            return;
        }
        prev = temp; temp = temp->next;
    }
    cout << RED << "Item tidak ditemukan!\n" << RESET;
}

void searchItem(const string& namaItem) {
    Node* temp = head;
    while (temp) {
        if (temp->namaItem == namaItem) {
            cout << GREEN << "Item ditemukan: " << temp->namaItem 
                 << " (" << temp->tipe << ", " << temp->rarity 
                 << ", jumlah: " << temp->jumlah << ")\n" << RESET;
            return;
        }
        temp = temp->next;
    }
    cout << RED << "Item tidak ada di inventory.\n" << RESET;
}

void clearInventory() {
    char konfirmasi;
    cout << YELLOW << "Apakah Anda yakin ingin menghapus semua item? (y/n): " << RESET;
    cin >> konfirmasi;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << GREEN << "Penghapusan dibatalkan.\n" << RESET;
        return;
    }
    Node* temp = head;
    while (temp) {
        Node* hapus = temp;
        temp = temp->next;
        delete hapus;
    }
    head = NULL;
    cout << YELLOW << "Seluruh inventory dihapus!\n" << RESET;
}

int countTotalItems() {
    int total = 0;
    Node* temp = head;
    while (temp) { total += temp->jumlah; temp = temp->next; }
    return total;
}

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
        cout << CYAN << "+----------------------------------+\n";
        cout << "      GAME INVENTORY MANAGEMENT\n";
        cout << "[" << nama << " - " << nim << "]\n";
        cout << "+----------------------------------+" << RESET << "\n";
        cout << "1. Tambah Item Baru\n";
        cout << "2. Sisipkan Item\n";
        cout << "3. Hapus Item Terakhir\n";
        cout << "4. Gunakan Item\n";
        cout << "5. Tampilkan Inventory\n";
        cout << "6. Cari Item\n";
        cout << "7. Hapus Semua Item\n";
        cout << "8. Hitung Total Jumlah Item\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan; cin.ignore();

        system(CLEAR);

        if (pilihan == 1) {
            cout << CYAN << "=== Tambah Item Baru ===\n" << RESET;
            tampilkanInventory();
            string n = inputNama();
            string t = inputTipe();
            string r = inputRarity();
            tambahItemBaru(n, t, r);
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 2) {
            cout << CYAN << "=== Sisipkan Item ===\n" << RESET;
            tampilkanInventory();
            string n = inputNama();
            string t = inputTipe();
            string r = inputRarity();
            sisipItem(n, t, r);
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 3) {
            cout << CYAN << "=== Hapus Item Terakhir ===\n" << RESET;
            tampilkanInventory();
            hapusItemTerakhir();
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 4) {
            cout << CYAN << "=== Gunakan Item ===\n" << RESET;
            tampilkanInventory();
            string n = inputNama();
            gunakanItem(n);
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 5) {
            cout << CYAN << "=== Lihat Inventory ===\n" << RESET;
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 6) {
            cout << CYAN << "=== Cari Item ===\n" << RESET;
            tampilkanInventory();
            string n = inputNama();
            searchItem(n);
            tungguKembali();
        } else if (pilihan == 7) {
            cout << CYAN << "=== Hapus Semua Item ===\n" << RESET;
            tampilkanInventory();
            clearInventory();
            tampilkanInventory();
            tungguKembali();
        } else if (pilihan == 8) {
            cout << CYAN << "=== Hitung Total Jumlah Item ===\n" << RESET;
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

