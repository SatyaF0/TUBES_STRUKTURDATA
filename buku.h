#ifndef BUKU_H
#define BUKU_H

#include <iostream>
#include <string>

using namespace std;


struct PenulisNode;
struct BukuNode;
struct RelasiNode {
    PenulisNode* nextPenulis; 
    BukuNode* nextBuku;      
    RelasiNode* nextRelasiPenulis;
    RelasiNode* nextRelasiBuku; 
};

struct BukuNode {
    int idBuku;
    string judul;
    int tahunTerbit; 
    
    BukuNode* prev; 
    BukuNode* next;
    
    RelasiNode* firstRelasi; 
};

struct PenulisNode {
    int idPenulis;
    string nama;
    int umur;
    
    PenulisNode* next; 
    
    RelasiNode* firstRelasi; 
};


struct PenulisList {
    PenulisNode* first;
    PenulisNode* last;
};

struct BukuList {
    BukuNode* first;
    BukuNode* last;
};

void initList(PenulisList &L);
void initList(BukuList &L);
void insertFirstPenulis(PenulisList &L, int id, string nama, int umur);

void insertLastBuku(BukuList &L, int id, string judul, int tahun);
PenulisNode* findPenulis(PenulisList L, int id);
BukuNode* findBuku(BukuList L, int id);

void connect(PenulisList &LP, BukuList &LB, int idPenulis, int idBuku);

void deleteBukuAndRelasi(BukuList &LB, PenulisList &LP, int idBuku);
void deletePenulisAndRelasi(PenulisList &LP, BukuList &LB, int idPenulis);

void displayAllBukuWithPenulis(BukuList LB);
void displayBukuByPenulis(PenulisList LP, int idPenulis);
void displayPenulisByBuku(BukuList LB, int idBuku);
void displayMostActivePenulis(PenulisList LP);

#endif

