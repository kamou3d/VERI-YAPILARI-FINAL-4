#ifndef LOGISTICS_H
#define LOGISTICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 10 // Hash tablosu boyutu
#define MAX_CITIES 20 // Maksimum şehir sayısı

// --- HASH TABLOSU (Paketler İçin) ---
typedef struct {
    int package_id;
    char destination[50];
    char status[20];
    bool is_occupied; // Açık adresleme için doluluk kontrolü
} Package;

// --- GRAF (Şehir Bağlantıları İçin - Adjacency List) ---
typedef struct Node {
    int city_index;
    struct Node* next;
} Node;

typedef struct {
    char city_names[MAX_CITIES][50];
    Node* head[MAX_CITIES];
    int num_cities;
} Graph;

// --- Fonksiyon Prototipleri ---
// Hash Fonksiyonları
void init_hash_table(Package table[]);
int hash_function_type_a(int key);
void insert_package(Package table[], int package_id, const char* dest, const char* status);
void search_package(Package table[], int package_id);

// Graf Fonksiyonları
void init_graph(Graph* g);
void add_city(Graph* g, const char* name);
void add_edge(Graph* g, int src_index, int dest_index);
void bfs_traversal(Graph* g, int start_index);

// Bellek Raporu
void generate_memory_report(Package table[], Graph* g);

#endif
