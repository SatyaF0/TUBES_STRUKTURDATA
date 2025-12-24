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
    string idBuku; 
    string judul;
    int tahunTerbit; 
    BukuNode* prev; 
    BukuNode* next;
    RelasiNode* firstRelasi; 
};

struct PenulisNode {
    string idPenulis; 
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
void insertFirstPenulis(PenulisList &L, string id, string nama, int umur);
void insertLastBuku(BukuList &L, string id, string judul, int tahun);

PenulisNode* findPenulis(PenulisList L, string id);
BukuNode* findBuku(BukuList L, string id);

void connect(PenulisList &LP, BukuList &LB, string idPenulis, string idBuku);

void deleteBukuAndRelasi(BukuList &LB, PenulisList &LP, string idBuku);
void deletePenulisAndRelasi(PenulisList &LP, BukuList &LB, string idPenulis);

void displayAllBukuWithPenulis(BukuList LB);
void displayBukuByPenulis(PenulisList LP, string idPenulis);
void displayPenulisByBuku(BukuList LB, string idBuku);

void displayMostActivePenulis(PenulisList LP);
void displayLeastActivePenulis(PenulisList LP); 

#endif
