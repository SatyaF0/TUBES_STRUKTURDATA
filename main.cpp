#include "buku.h"
#include <limits> 

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

void displayMenu() {
    cout << "\n=========================================\n";
    cout << "          MENU SISTEM MANAJEMEN BUKU       \n";
    cout << "=========================================\n";
    cout << "1. Tambah Data Penulis\n";
    cout << "2. Tambah Data Buku\n";
    cout << "3. Tentukan Relasi (Penulis dan Buku)\n";
    cout << "4. Hapus Data Penulis Beserta Relasi\n";
    cout << "5. Hapus Data Buku Beserta Relasi\n";
    cout << "-----------------------------------------\n";
    cout << "6. Pencarian & Tampil Data\n"; 
    cout << "0. Keluar\n";
    cout << "=========================================\n";
    cout << "Pilih Opsi: ";
}

void displaySubMenuSearch() {
    cout << "\n--- PENCARIAN & TAMPIL DATA ---\n";
    cout << "1. Tampilkan Semua Buku Beserta Penulisnya\n";
    cout << "2. Tampilkan Buku Berdasarkan Penulis Tertentu\n";
    cout << "3. Tampilkan Penulis Berdasarkan Buku Tertentu\n";
    cout << "4. Tampilkan Penulis Paling Aktif\n";
    cout << "0. Kembali ke Menu Utama\n";
    cout << "Pilih Opsi: ";
}

void handleAddPenulis(PenulisList &LP) {
    int id, umur;
    string nama;
    
    cout << "\n--- Tambah Data Penulis ---\n";
    cout << "ID Penulis (int): ";
    if (!(cin >> id)) { clearInputBuffer(); cout << "Input ID tidak valid.\n"; return; }
    cin.ignore(); 
    cout << "Nama Penulis: ";
    getline(cin, nama);
    cout << "Umur Penulis (int): ";
    if (!(cin >> umur)) { clearInputBuffer(); cout << "Input Umur tidak valid.\n"; return; }
    
    insertFirstPenulis(LP, id, nama, umur);
}

void handleAddBuku(BukuList &LB) {
    int id, tahun;
    string judul;
    
    cout << "\n--- Tambah Data Buku ---\n";
    cout << "ID Buku (int): ";
    if (!(cin >> id)) { clearInputBuffer(); cout << "Input ID tidak valid.\n"; return; }
    cin.ignore();
    cout << "Judul Buku: ";
    getline(cin, judul);
    cout << "Tahun Terbit (int): ";
    if (!(cin >> tahun)) { clearInputBuffer(); cout << "Input Tahun tidak valid.\n"; return; }
    
    insertLastBuku(LB, id, judul, tahun);
}

void handleConnect(PenulisList &LP, BukuList &LB) {
    int idPenulis, idBuku;
    
    cout << "\n--- Tentukan Relasi ---\n";
    cout << "Masukkan ID Penulis: ";
    if (!(cin >> idPenulis)) { clearInputBuffer(); cout << "Input ID Penulis tidak valid.\n"; return; }
    cout << "Masukkan ID Buku: ";
    if (!(cin >> idBuku)) { clearInputBuffer(); cout << "Input ID Buku tidak valid.\n"; return; }
    
    connect(LP, LB, idPenulis, idBuku);
}

void handleDeletePenulis(PenulisList &LP, BukuList &LB) {
    int id;
    cout << "\n--- Hapus Data Penulis ---\n";
    cout << "Masukkan ID Penulis yang akan dihapus: ";
    if (!(cin >> id)) { clearInputBuffer(); cout << "Input ID tidak valid.\n"; return; }
    
    deletePenulisAndRelasi(LP, LB, id);
}

void handleDeleteBuku(BukuList &LB, PenulisList &LP) {
    int id;
    cout << "\n--- Hapus Data Buku ---\n";
    cout << "Masukkan ID Buku yang akan dihapus: ";
    if (!(cin >> id)) { clearInputBuffer(); cout << "Input ID tidak valid.\n"; return; }
    
    deleteBukuAndRelasi(LB, LP, id);
}


void handleDisplayBukuByPenulis(PenulisList &LP) {
    int id;
    cout << "\n--- Tampilkan Buku Berdasarkan Penulis ---\n";
    cout << "Masukkan ID Penulis: ";
    if (!(cin >> id)) { clearInputBuffer(); cout << "Input ID tidak valid.\n"; return; }
    
    displayBukuByPenulis(LP, id);
}

void handleDisplayPenulisByBuku(BukuList &LB) {
    int id;
    cout << "\n--- Tampilkan Penulis Berdasarkan Buku ---\n";
    cout << "Masukkan ID Buku: ";
    if (!(cin >> id)) { clearInputBuffer(); cout << "Input ID tidak valid.\n"; return; }
    
    displayPenulisByBuku(LB, id);
}

void handleSearchMenu(PenulisList &LP, BukuList &LB) {
    int subChoice;
    bool subRunning = true;
    
    while (subRunning) {
        displaySubMenuSearch();
        
        if (!(cin >> subChoice)) {
            clearInputBuffer();
            cout << "Input tidak valid. Silakan masukkan angka dari sub-menu.\n";
            continue;
        }

        switch (subChoice) {
            case 1:
                displayAllBukuWithPenulis(LB);
                break;
            case 2:
                handleDisplayBukuByPenulis(LP);
                break;
            case 3:
                handleDisplayPenulisByBuku(LB);
                break;
            case 4:
                displayMostActivePenulis(LP);
                break;
            case 0:
                subRunning = false;
                break;
            default:
                cout << "Opsi sub-menu tidak valid. Silakan coba lagi.\n";
                break;
        }
    }
}

int main() {
    PenulisList listPenulis;
    BukuList listBuku;
    initList(listPenulis);
    initList(listBuku);

    int choice;
    bool running = true;

    cout << "=========================================\n";
    cout << "  SELAMAT DATANG DI SISTEM MANAJEMEN BUKU  \n";
    cout << "=========================================\n";

    while (running) {
        displayMenu();
        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << "Input tidak valid. Silakan masukkan angka dari menu.\n";
            continue;
        }

        switch (choice) {
            case 1:
                handleAddPenulis(listPenulis);
                break;
            case 2:
                handleAddBuku(listBuku);
                break;
            case 3:
                handleConnect(listPenulis, listBuku);
                break;
            case 4:
                handleDeletePenulis(listPenulis, listBuku);
                break;
            case 5:
                handleDeleteBuku(listBuku, listPenulis);
                break;
            case 6:
                handleSearchMenu(listPenulis, listBuku);
                break;
            case 0:
                running = false;
                cout << "Terima kasih telah menggunakan sistem manajemen buku.\n";
                break;
            default:
                cout << "Opsi tidak valid. Silakan coba lagi.\n";
                break;
        }
    }

    return 0;
}

