#include "mll.h"
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