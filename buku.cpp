#include "buku.h"

void initList(PenulisList &L) { L.first = nullptr; L.last = nullptr; }
void initList(BukuList &L) { L.first = nullptr; L.last = nullptr; }

void insertFirstPenulis(PenulisList &L, string id, string nama, int umur) {
    PenulisNode* newNode = new PenulisNode{id, nama, umur, L.first, nullptr};
    L.first = newNode;
    if (L.last == nullptr) L.last = newNode;
    cout << "Penulis " << nama << " (ID: " << id << ") berhasil ditambahkan.\n";
}

void insertLastBuku(BukuList &L, string id, string judul, int tahun) {
    BukuNode* newNode = new BukuNode{id, judul, tahun, L.last, nullptr, nullptr};
    if (L.first == nullptr) L.first = newNode;
    else L.last->next = newNode;
    L.last = newNode;
    cout << "Buku " << judul << " (ID: " << id << ") berhasil ditambahkan.\n";
}

PenulisNode* findPenulis(PenulisList L, string id) {
    PenulisNode* current = L.first;
    while (current != nullptr && current->idPenulis != id) current = current->next;
    return current;
}

BukuNode* findBuku(BukuList L, string id) {
    BukuNode* current = L.first;
    while (current != nullptr && current->idBuku != id) current = current->next;
    return current;
}

void connect(PenulisList &LP, BukuList &LB, string idPenulis, string idBuku) {
    PenulisNode* p = findPenulis(LP, idPenulis);
    BukuNode* b = findBuku(LB, idBuku);
    if (!p || !b) { cout << "Error: ID tidak ditemukan.\n"; return; }

    RelasiNode* r = new RelasiNode{p, b, p->firstRelasi, b->firstRelasi};
    p->firstRelasi = r;
    b->firstRelasi = r;
    cout << "Relasi " << p->nama << " -> " << b->judul << " berhasil.\n";
}

void deleteBukuAndRelasi(BukuList &LB, PenulisList &LP, string idBuku) {
    BukuNode* b = findBuku(LB, idBuku);
    if (!b) return;

    RelasiNode* r = b->firstRelasi;
    while (r != nullptr) {
        RelasiNode* nextR = r->nextRelasiBuku;
        PenulisNode* p = r->nextPenulis;
        
        if (p->firstRelasi == r) p->firstRelasi = r->nextRelasiPenulis;
        else {
            RelasiNode* prev = p->firstRelasi;
            while (prev->nextRelasiPenulis != r) prev = prev->nextRelasiPenulis;
            prev->nextRelasiPenulis = r->nextRelasiPenulis;
        }
        delete r;
        r = nextR;
    }

    if (b->prev) b->prev->next = b->next; else LB.first = b->next;
    if (b->next) b->next->prev = b->prev; else LB.last = b->prev;
    delete b;
    cout << "Buku dihapus.\n";
}

void deletePenulisAndRelasi(PenulisList &LP, BukuList &LB, string idPenulis) {
    PenulisNode* p = findPenulis(LP, idPenulis);
    if (!p) return;

    RelasiNode* r = p->firstRelasi;
    while (r != nullptr) {
        RelasiNode* nextR = r->nextRelasiPenulis;
        BukuNode* b = r->nextBuku;

        if (b->firstRelasi == r) b->firstRelasi = r->nextRelasiBuku;
        else {
            RelasiNode* prev = b->firstRelasi;
            while (prev->nextRelasiBuku != r) prev = prev->nextRelasiBuku;
            prev->nextRelasiBuku = r->nextRelasiBuku;
        }
        delete r;
        r = nextR;
    }

    if (LP.first == p) LP.first = p->next;
    else {
        PenulisNode* prevP = LP.first;
        while (prevP->next != p) prevP = prevP->next;
        prevP->next = p->next;
        if (LP.last == p) LP.last = prevP;
    }
    delete p;
    cout << "Penulis dihapus.\n";
}

void displayAllBukuWithPenulis(BukuList LB) {
    BukuNode* b = LB.first;
    while (b) {
        cout << b->judul << " (ID:" << b->idBuku << ") | Penulis: ";
        RelasiNode* r = b->firstRelasi;
        while (r) {
            cout << r->nextPenulis->nama << (r->nextRelasiBuku ? ", " : "");
            r = r->nextRelasiBuku;
        }
        cout << endl;
        b = b->next;
    }
}

void displayMostActivePenulis(PenulisList LP) {
    int maxB = 0;
    PenulisNode* curr = LP.first;
    while (curr) {
        int c = 0; RelasiNode* r = curr->firstRelasi;
        while (r) { c++; r = r->nextRelasiPenulis; }
        if (c > maxB) maxB = c;
        curr = curr->next;
    }
    cout << "\n--- Paling Aktif (" << maxB << " Buku) ---\n";
    curr = LP.first;
    while (curr) {
        int c = 0; RelasiNode* r = curr->firstRelasi;
        while (r) { c++; r = r->nextRelasiPenulis; }
        if (c == maxB && maxB > 0) cout << "- " << curr->nama << endl;
        curr = curr->next;
    }
}

void displayLeastActivePenulis(PenulisList LP) {
    if (!LP.first) return;
    int minB = -1;
    PenulisNode* curr = LP.first;
    while (curr) {
        int c = 0; RelasiNode* r = curr->firstRelasi;
        while (r) { c++; r = r->nextRelasiPenulis; }
        if (minB == -1 || c < minB) minB = c;
        curr = curr->next;
    }
    cout << "\n--- Paling Tidak Aktif (" << minB << " Buku) ---\n";
    curr = LP.first;
    while (curr) {
        int c = 0; RelasiNode* r = curr->firstRelasi;
        while (r) { c++; r = r->nextRelasiPenulis; }
        if (c == minB) cout << "- " << curr->nama << endl;
        curr = curr->next;
    }
}

void displayBukuByPenulis(PenulisList LP, string idPenulis) {
    PenulisNode* p = findPenulis(LP, idPenulis);
    if (!p) return;
    RelasiNode* r = p->firstRelasi;
    while (r) { cout << "- " << r->nextBuku->judul << endl; r = r->nextRelasiPenulis; }
}

void displayPenulisByBuku(BukuList LB, string idBuku) {
    BukuNode* b = findBuku(LB, idBuku);
    if (!b) return;
    RelasiNode* r = b->firstRelasi;
    while (r) { cout << "- " << r->nextPenulis->nama << endl; r = r->nextRelasiBuku; }
}
