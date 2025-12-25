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
    cout << "5. Tampilkan Penulis Paling Tidak Aktif\n";
    cout << "0. Kembali ke Menu Utama\n";
    cout << "Pilih Opsi: ";
}

void handleAddPenulis(PenulisList &LP) {
    string id, nama;
    int umur;
    
    cout << "\n--- Tambah Data Penulis ---\n";
    cout << "ID Penulis : "; 
    cin >> id;
    cin.ignore(); 
    cout << "Nama Penulis: ";
    getline(cin, nama);
    cout << "Umur Penulis : ";
    if (!(cin >> umur)) {
        clearInputBuffer();
        cout << "Input umur tidak valid.\n";
        return;
    }
    insertFirstPenulis(LP, id, nama, umur);
}

void handleAddBuku(BukuList &LB) {
    string id, judul;
    int tahun;
    
    cout << "\n--- Tambah Data Buku ---\n";
    cout << "ID Buku : "; 
    cin >> id;
    cin.ignore();
    cout << "Judul Buku: ";
    getline(cin, judul);
    cout << "Tahun Terbit : ";
    if (!(cin >> tahun)) {
        clearInputBuffer();
        cout << "Input tahun tidak valid.\n";
        return;
    }
    insertLastBuku(LB, id, judul, tahun);
}

void handleConnect(PenulisList &LP, BukuList &LB) {
    string idPenulis, idBuku;
    cout << "\n--- Tentukan Relasi ---\n";
    cout << "Masukkan ID Penulis: ";
    cin >> idPenulis;
    cout << "Masukkan ID Buku: ";
    cin >> idBuku;
    connect(LP, LB, idPenulis, idBuku);
}

void handleDeletePenulis(PenulisList &LP) {
    string id;
    cout << "\n--- Hapus Data Penulis ---\n";
    cout << "Masukkan ID Penulis yang akan dihapus: ";
    cin >> id;
    deletePenulisAndRelasi(LP, id);
}

void handleDeleteBuku(BukuList &LB, PenulisList &LP) {
    string id;
    cout << "\n--- Hapus Data Buku ---\n";
    cout << "Masukkan ID Buku yang akan dihapus: ";
    cin >> id;
    deleteBukuAndRelasi(LB, LP, id);
}

void handleDisplayBukuByPenulis(PenulisList &LP) {
    string id;
    cout << "\n--- Tampilkan Buku Berdasarkan Penulis ---\n";
    cout << "Masukkan ID Penulis: ";
    cin >> id;
    displayBukuByPenulis(LP, id);
}

void handleDisplayPenulisByBuku(PenulisList &LP) {
    string id;
    cout << "\n--- Tampilkan Penulis Berdasarkan Buku ---\n";
    cout << "Masukkan ID Buku: ";
    cin >> id;
    displayPenulisByBuku(LP, id);
}

void handleSearchMenu(PenulisList &LP, BukuList &LB) {
    int subChoice;
    bool subRunning = true;
    while (subRunning) {
        displaySubMenuSearch();
        if (!(cin >> subChoice)) {
            clearInputBuffer();
            cout << "Input tidak valid.\n";
            continue;
        }
        switch (subChoice) {
            case 1: displayAllBukuWithPenulis(LB, LP); break;
            case 2: handleDisplayBukuByPenulis(LP); break;
            case 3: handleDisplayPenulisByBuku(LP); break;
            case 4: displayMostActivePenulis(LP); break;
            case 5: displayLeastActivePenulis(LP); break;
            case 0: subRunning = false; break;
            default: cout << "Opsi tidak valid.\n"; break;
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
            cout << "Input tidak valid.\n";
            continue;
        }
        switch (choice) {
            case 1: handleAddPenulis(listPenulis); break;
            case 2: handleAddBuku(listBuku); break;
            case 3: handleConnect(listPenulis, listBuku); break;
            case 4: handleDeletePenulis(listPenulis); break;
            case 5: handleDeleteBuku(listBuku, listPenulis); break;
            case 6: handleSearchMenu(listPenulis, listBuku); break;
            case 0: running = false; cout << "Terima kasih.\n"; break;
            default: cout << "Opsi tidak valid.\n"; break;
        }
    }
    return 0;
}
