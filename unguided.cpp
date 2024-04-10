#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Struktur data untuk setiap mahasiswa
struct Mahasiswa {
    string nim;
    string nama;
    int nilai;
    Mahasiswa(string nim, string nama, int nilai) : nim(nim), nama(nama), nilai(nilai) {}
};

// Class HashNode untuk setiap node pada hash table
class HashNode {
public:
    string nim;
    string nama;
    int nilai;
    HashNode(string nim, string nama, int nilai) : nim(nim), nama(nama), nilai(nilai) {}
};

// Class HashMap untuk hash table
class HashMap {
private:
    static const int TABLE_SIZE = 10;
    vector<HashNode*> table[TABLE_SIZE];

public:
    // Fungsi hash sederhana
    int hashFunc(string key) {
        int hash_val = 0;
        for (char c : key) {
            hash_val += c;
        }
        return hash_val % TABLE_SIZE;
    }

    // Menambahkan data mahasiswa baru
    void insert(string nim, string nama, int nilai) {
        int hash_val = hashFunc(nim);
        table[hash_val].push_back(new HashNode(nim, nama, nilai));
    }

    // Menghapus data mahasiswa berdasarkan NIM
    void remove(string nim) {
        int hash_val = hashFunc(nim);
        for (auto it = table[hash_val].begin(); it != table[hash_val].end(); it++) {
            if ((*it)->nim == nim) {
                table[hash_val].erase(it);
                return;
            }
        }
    }

    // Mencari data mahasiswa berdasarkan NIM
    int searchByNIM(string nim) {
        int hash_val = hashFunc(nim);
        for (auto node : table[hash_val]) {
            if (node->nim == nim) {
                return node->nilai;
            }
        }
        return -1; // Mahasiswa tidak ditemukan
    }

    // Mencari data mahasiswa berdasarkan rentang nilai (80 - 90)
    vector<string> searchByRange(int minNilai, int maxNilai) {
        vector<string> result;
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (auto node : table[i]) {
                if (node->nilai >= minNilai && node->nilai <= maxNilai) {
                    result.push_back(node->nama);
                }
            }
        }
        return result;
    }
};

int main() {
    HashMap mahasiswaMap;
    int choice;
    do {
        cout << "Menu:" << endl;
        cout << endl;
        cout << "1. Tambah data mahasiswa" << endl;
        cout << "2. Hapus data mahasiswa" << endl;
        cout << "3. Cari data mahasiswa berdasarkan NIM" << endl;
        cout << "4. Cari data mahasiswa berdasarkan rentang nilai (80 - 90)" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih: ";
        cin >> choice;

        cout << endl;

        switch (choice) {
            case 1: {
                string nim, nama;
                int nilai;
                cout << "Masukkan NIM: ";
                cin >> nim;
                cout << "Masukkan Nama: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan nilai: ";
                cin >> nilai;
                mahasiswaMap.insert(nim, nama, nilai);
                cout << "Data mahasiswa ditambahkan." << endl;
                cout << endl ;
                break;
            }
            case 2: {
                string nim;
                cout << "Masukkan NIM yang ingin dihapus: ";
                cin >> nim;
                mahasiswaMap.remove(nim);
                cout << "Data mahasiswa dihapus." << endl;
                cout << endl ;
                break;
            }
            case 3: {
                string nim;
                cout << "Masukkan NIM yang ingin dicari: ";
                cin >> nim;
                int nilai = mahasiswaMap.searchByNIM(nim);
                if (nilai != -1) {
                    cout << "Nilai mahasiswa dengan NIM " << nim << " adalah: " << nilai << endl;
                } else {
                    cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan." << endl;
                }
                cout << endl ;
                break;
            }
            case 4: {
                vector<string> mahasiswa80_90 = mahasiswaMap.searchByRange(80, 90);
                if (mahasiswa80_90.size() > 0) {
                    cout << "Mahasiswa dengan nilai antara 80 dan 90 adalah: ";
                    for (string nama : mahasiswa80_90) {
                        cout << nama << " ";
                    }
                    cout << endl;
                } else {
                    cout << "Tidak ada mahasiswa dengan nilai antara 80 dan 90." << endl;
                }
                cout << endl ;
                break;
            }
            case 5: {
                cout << "Program selesai." << endl;
                cout << endl ;
                break;
            }
            default: {
                cout << "Pilihan tidak valid. Silakan pilih kembali." << endl;
                cout << endl ;
                break;
            }
        }
    } while (choice != 5);

    return 1;
}
