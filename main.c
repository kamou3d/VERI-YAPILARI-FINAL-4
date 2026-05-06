#include "logistics.h"

// İstenen EK DOSYA (Bellek İzleme Raporu) için yardımcı fonksiyon
void generate_memory_report(Package table[], Graph* g) {
    printf("\n=== BELLEK IZLEME RAPORU ===\n");
    printf("1. HASH TABLOSU BELLEK ADRESLERI (Ilk 5 kayit):\n");
    int count = 0;
    for (int i = 0; i < TABLE_SIZE && count < 5; i++) {
        if (table[i].is_occupied) {
            printf("Index %d | Paket ID: %d | Adres: %p\n", i, table[i].package_id, (void*)&table[i]);
            count++;
        }
    }

    printf("\n2. GRAF DUGUMLERI BELLEK ADRESLERI (Dinamik Tahsis):\n");
    for (int i = 0; i < g->num_cities; i++) {
        printf("Sehir: %s (Baslangic Pointer: %p)\n", g->city_names[i], (void*)g->head[i]);
        Node* temp = g->head[i];
        while (temp != NULL) {
            printf("  -> Baglanti (Hedef Index: %d) | Dugum Adresi: %p | Next Pointer: %p\n",
                   temp->city_index, (void*)temp, (void*)temp->next);
            temp = temp->next;
        }
    }
    printf("============================\n");
}

int main() {
    Package hash_table[TABLE_SIZE];
    Graph logistics_graph;

    init_hash_table(hash_table);
    init_graph(&logistics_graph);

    // 1. Graf Kurulumu
    add_city(&logistics_graph, "Istanbul"); // Index 0
    add_city(&logistics_graph, "Ankara");   // Index 1
    add_city(&logistics_graph, "Izmir");    // Index 2
    add_city(&logistics_graph, "Bursa");    // Index 3

    add_edge(&logistics_graph, 0, 1); // Istanbul - Ankara
    add_edge(&logistics_graph, 0, 3); // Istanbul - Bursa
    add_edge(&logistics_graph, 1, 2); // Ankara - Izmir

    // 2. Hash Tablosuna Paket Ekleme (Açık Adresleme Testi)
    insert_package(hash_table, 102, "Ankara", "Yolda");
    insert_package(hash_table, 205, "Izmir", "Depoda");
    insert_package(hash_table, 312, "Bursa", "Teslim Edildi");
    insert_package(hash_table, 422, "Istanbul", "Yolda"); // 102 ve 312 ile aynı modu verebilir (2), Linear Probing devreye girer!
    insert_package(hash_table, 555, "Ankara", "Depoda");

    printf("\n");
    search_package(hash_table, 422);

    printf("\n");
    bfs_traversal(&logistics_graph, 0); // Istanbul'dan başla

    // 3. Bellek Raporunu Çıktı Alma
    generate_memory_report(hash_table, &logistics_graph);

    return 0;
}
