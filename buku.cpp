#include "buku.h"
#include <iomanip>

void initList(PenulisList &L) {
    L.first = nullptr;
    L.last = nullptr;
}

void initList(BukuList &L) {
    L.first = nullptr;
    L.last = nullptr;
}

void insertFirstPenulis(PenulisList &L, int id, string nama, int umur) {
    PenulisNode* newNode = new PenulisNode;
    newNode->idPenulis = id;
    newNode->nama = nama;
    newNode->umur = umur;
    newNode->firstRelasi = nullptr;
    newNode->next = L.first;
    L.first = newNode;
    
    if (L.last == nullptr) {
        L.last = newNode;
    }
    cout << "Penulis " << nama << " (ID: " << id << ") berhasil ditambahkan.\n";

}

void insertLastBuku(BukuList &L, int id, string judul, int tahun) {
    BukuNode* newNode = new BukuNode;
    newNode->idBuku = id;
    newNode->judul = judul;
    newNode->tahunTerbit = tahun;
    newNode->firstRelasi = nullptr;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (L.first == nullptr) {
        L.first = newNode;
        L.last = newNode;
    } else {
        L.last->next = newNode;
        newNode->prev = L.last;
        L.last = newNode;
    }
    cout << "Buku " << judul << " (ID: " << id << ") berhasil ditambahkan.\n";
}

PenulisNode* findPenulis(PenulisList L, int id) {
    PenulisNode* current = L.first;
    while (current != nullptr && current->idPenulis != id) {
        current = current->next;
    }
    return current;
}

BukuNode* findBuku(BukuList L, int id) {
    BukuNode* current = L.first;
    while (current != nullptr && current->idBuku != id) {
        current = current->next;
    }
    return current;
}


void connect(PenulisList &LP, BukuList &LB, int idPenulis, int idBuku) {
    PenulisNode* penulis = findPenulis(LP, idPenulis);
    BukuNode* buku = findBuku(LB, idBuku);

    if (!penulis || !buku) {
        cout << "Error: Penulis atau Buku tidak ditemukan.\n";
        return;
    }

    RelasiNode* currentRelasi = penulis->firstRelasi;
    while (currentRelasi != nullptr) {
        if (currentRelasi->nextBuku == buku) {
            cout << "Relasi antara Penulis " << penulis->nama << " dan Buku " << buku->judul << " sudah ada.\n";
            return;
        }
        currentRelasi = currentRelasi->nextRelasiPenulis;
    }

    RelasiNode* newRelasi = new RelasiNode;
    newRelasi->nextPenulis = penulis;
    newRelasi->nextBuku = buku;       
    
    newRelasi->nextRelasiPenulis = penulis->firstRelasi;
    penulis->firstRelasi = newRelasi;
    
    newRelasi->nextRelasiBuku = buku->firstRelasi;
    buku->firstRelasi = newRelasi;
    
    cout << "Relasi berhasil dibuat: " << penulis->nama << " menulis " << buku->judul << ".\n";
}
void deleteBukuAndRelasi(BukuList &LB, PenulisList &LP, int idBuku) {
    BukuNode* bukuToDelete = findBuku(LB, idBuku);
    if (!bukuToDelete) {
        cout << "Buku dengan ID " << idBuku << " tidak ditemukan.\n";
        return;
    }
    
    string judulBuku = bukuToDelete->judul;

    RelasiNode* currentRelasi = bukuToDelete->firstRelasi;
    while (currentRelasi != nullptr) {
        RelasiNode* relasiNext = currentRelasi->nextRelasiBuku; 
        PenulisNode* penulisTerkait = currentRelasi->nextPenulis;
        
        RelasiNode* relasiPenulis = penulisTerkait->firstRelasi;
        if (relasiPenulis == currentRelasi) {
            penulisTerkait->firstRelasi = currentRelasi->nextRelasiPenulis;
        } else {
            RelasiNode* prevRelasiPenulis = penulisTerkait->firstRelasi;
            while (prevRelasiPenulis != nullptr && prevRelasiPenulis->nextRelasiPenulis != currentRelasi) {
                prevRelasiPenulis = prevRelasiPenulis->nextRelasiPenulis;
            }
            if (prevRelasiPenulis != nullptr) {
                prevRelasiPenulis->nextRelasiPenulis = currentRelasi->nextRelasiPenulis;
            }
        }
        
        delete currentRelasi;
        currentRelasi = relasiNext;
    }
    bukuToDelete->firstRelasi = nullptr;

    if (bukuToDelete == LB.first && bukuToDelete == LB.last) {
        LB.first = nullptr;
        LB.last = nullptr;
    } else if (bukuToDelete == LB.first) {
        LB.first = bukuToDelete->next;
        if (LB.first != nullptr) LB.first->prev = nullptr;
    } else if (bukuToDelete == LB.last) {
        LB.last = bukuToDelete->prev;
        if (LB.last != nullptr) LB.last->next = nullptr;
    } else {
        bukuToDelete->prev->next = bukuToDelete->next;
        bukuToDelete->next->prev = bukuToDelete->prev;
    }
    
    delete bukuToDelete;
    cout << "Buku '" << judulBuku << "' (ID: " << idBuku << ") beserta semua relasinya berhasil dihapus.\n";
}

void deletePenulisAndRelasi(PenulisList &LP, BukuList &LB, int idPenulis) {
    PenulisNode* penulisToDelete = findPenulis(LP, idPenulis);
    if (!penulisToDelete) {
        cout << "Penulis dengan ID " << idPenulis << " tidak ditemukan.\n";
        return;
    }
    
    string namaPenulis = penulisToDelete->nama;
    
    RelasiNode* currentRelasi = penulisToDelete->firstRelasi;
    while (currentRelasi != nullptr) {
        RelasiNode* relasiNext = currentRelasi->nextRelasiPenulis; 
        BukuNode* bukuTerkait = currentRelasi->nextBuku;
        
        RelasiNode* relasiBuku = bukuTerkait->firstRelasi;
        if (relasiBuku == currentRelasi) {
            bukuTerkait->firstRelasi = currentRelasi->nextRelasiBuku;
        } else {
            RelasiNode* prevRelasiBuku = bukuTerkait->firstRelasi;
            while (prevRelasiBuku != nullptr && prevRelasiBuku->nextRelasiBuku != currentRelasi) {
                prevRelasiBuku = prevRelasiBuku->nextRelasiBuku;
            }
            if (prevRelasiBuku != nullptr) {
                prevRelasiBuku->nextRelasiBuku = currentRelasi->nextRelasiBuku;
            }
        }
        
        delete currentRelasi;
        currentRelasi = relasiNext;
    }
    penulisToDelete->firstRelasi = nullptr;

    if (penulisToDelete == LP.first) {
        LP.first = penulisToDelete->next;
        if (LP.last == penulisToDelete) LP.last = nullptr;
    } else {
        PenulisNode* prevPenulis = LP.first;
        while (prevPenulis != nullptr && prevPenulis->next != penulisToDelete) {
            prevPenulis = prevPenulis->next;
        }
        
        if (prevPenulis != nullptr) {
            prevPenulis->next = penulisToDelete->next;
            if (LP.last == penulisToDelete) LP.last = prevPenulis;
        }
    }
    
    delete penulisToDelete;
    cout << "Penulis '" << namaPenulis << "' (ID: " << idPenulis << ") beserta semua relasinya berhasil dihapus.\n";
}

void displayAllBukuWithPenulis(BukuList LB) {
    cout << "\n--- Data Keseluruhan Buku Beserta Penulisnya ---\n";
    if (LB.first == nullptr) {
        cout << "Tidak ada data buku.\n";
        return;
    }

    BukuNode* currentBuku = LB.first;
    while (currentBuku != nullptr) {
        cout << "------------------------------------------\n";
        cout << "Buku ID : " << currentBuku->idBuku << "\n";
        cout << "Judul   : " << currentBuku->judul << "\n";
        cout << "Tahun   : " << currentBuku->tahunTerbit << "\n";
        cout << "Penulis : ";

        RelasiNode* currentRelasi = currentBuku->firstRelasi;
        if (currentRelasi == nullptr) {
            cout << "(Tidak ada penulis terhubung)\n";
        } else {
            int count = 0;
            while (currentRelasi != nullptr) {
                if (count > 0) cout << ", ";
                cout << currentRelasi->nextPenulis->nama;
                currentRelasi = currentRelasi->nextRelasiBuku; 
                count++;
            }
            cout << "\n";
        }
        currentBuku = currentBuku->next;
    }
    cout << "------------------------------------------\n";

}
