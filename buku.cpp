#include "buku.h"

void initList(PenulisList &L) {
    L.first = L.last = nullptr;
}

void initList(BukuList &L) {
    L.first = L.last = nullptr;
}

void insertFirstPenulis(PenulisList &L, string id, string nama, int umur) {
    PenulisNode* p = new PenulisNode{id, nama, umur, L.first, nullptr};
    L.first = p;
    if (!L.last) L.last = p;
}

void insertLastBuku(BukuList &L, string id, string judul, int tahun) {
    BukuNode* b = new BukuNode{id, judul, tahun, L.last, nullptr};
    if (!L.first) L.first = b;
    else L.last->next = b;
    L.last = b;
}

PenulisNode* findPenulis(PenulisList L, string id) {
    PenulisNode* p = L.first;
    while (p && p->idPenulis != id) p = p->next;
    return p;
}

BukuNode* findBuku(BukuList L, string id) {
    BukuNode* b = L.first;
    while (b && b->idBuku != id) b = b->next;
    return b;
}

void connect(PenulisList &LP, BukuList &LB, string idPenulis, string idBuku) {
    PenulisNode* p = findPenulis(LP, idPenulis);
    BukuNode* b = findBuku(LB, idBuku);
    if (!p || !b) return;

    RelasiNode* r = new RelasiNode{b, p->firstRelasi};
    p->firstRelasi = r;
}

void deletePenulisAndRelasi(PenulisList &LP, string idPenulis) {
    PenulisNode* p = LP.first;
    PenulisNode* prev = nullptr;

    while (p && p->idPenulis != idPenulis) {
        prev = p;
        p = p->next;
    }
    if (!p) return;

    RelasiNode* r = p->firstRelasi;
    while (r) {
        RelasiNode* del = r;
        r = r->next;
        delete del;
    }

    if (!prev) LP.first = p->next;
    else prev->next = p->next;
    if (LP.last == p) LP.last = prev;

    delete p;
}

void deleteBukuAndRelasi(BukuList &LB, PenulisList &LP, string idBuku) {
    BukuNode* b = findBuku(LB, idBuku);
    if (!b) return;

    PenulisNode* p = LP.first;
    while (p) {
        RelasiNode* r = p->firstRelasi;
        RelasiNode* prev = nullptr;
        while (r) {
            if (r->buku == b) {
                if (!prev) p->firstRelasi = r->next;
                else prev->next = r->next;
                delete r;
                r = (prev ? prev->next : p->firstRelasi);
            } else {
                prev = r;
                r = r->next;
            }
        }
        p = p->next;
    }

    if (b->prev) b->prev->next = b->next;
    else LB.first = b->next;
    if (b->next) b->next->prev = b->prev;
    else LB.last = b->prev;

    delete b;
}

void displayBukuByPenulis(PenulisList LP, string idPenulis) {
    PenulisNode* p = findPenulis(LP, idPenulis);
    if (!p) return;

    RelasiNode* r = p->firstRelasi;
    while (r) {
        cout << "- " << r->buku->judul << endl;
        r = r->next;
    }
}

void displayPenulisByBuku(PenulisList LP, string idBuku) {
    PenulisNode* p = LP.first;
    while (p) {
        RelasiNode* r = p->firstRelasi;
        while (r) {
            if (r->buku->idBuku == idBuku)
                cout << "- " << p->nama << endl;
            r = r->next;
        }
        p = p->next;
    }
}

void displayAllBukuWithPenulis(BukuList LB, PenulisList LP) {
    BukuNode* b = LB.first;
    while (b) {
        cout << b->judul << " | Penulis: ";
        bool ada = false;
        PenulisNode* p = LP.first;
        while (p) {
            RelasiNode* r = p->firstRelasi;
            while (r) {
                if (r->buku == b) {
                    if (ada) cout << ", ";
                    cout << p->nama;
                    ada = true;
                }
                r = r->next;
            }
            p = p->next;
        }
        cout << endl;
        b = b->next;
    }
}

void displayMostActivePenulis(PenulisList LP) {
    int maxB = 0;
    for (PenulisNode* p = LP.first; p; p = p->next) {
        int c = 0;
        for (RelasiNode* r = p->firstRelasi; r; r = r->next) c++;
        if (c > maxB) maxB = c;
    }

    cout << "\n--- PENULIS PALING AKTIF ---\n";
    for (PenulisNode* p = LP.first; p; p = p->next) {
        int c = 0;
        for (RelasiNode* r = p->firstRelasi; r; r = r->next) c++;
        if (c == maxB && maxB > 0) {
            cout << "- " << p->nama << " (" << c << " buku)\n";
        }
    }
}


void displayLeastActivePenulis(PenulisList LP) {
    if (!LP.first) return;

    int minB = -1;
    for (PenulisNode* p = LP.first; p; p = p->next) {
        int c = 0;
        for (RelasiNode* r = p->firstRelasi; r; r = r->next) c++;
        if (minB == -1 || c < minB) minB = c;
    }

    cout << "\n--- PENULIS PALING TIDAK AKTIF ---\n";
    for (PenulisNode* p = LP.first; p; p = p->next) {
        int c = 0;
        for (RelasiNode* r = p->firstRelasi; r; r = r->next) c++;
        if (c == minB) {
            cout << "- " << p->nama << " (" << c << " buku)\n";
        }
    }
}
