#include "logistics.h"

void init_hash_table(Package table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].is_occupied = false;
    }
}

// Tip A Hash Fonksiyonu: Modülo Yöntemi
int hash_function_type_a(int key) {
    return key % TABLE_SIZE;
}

// Çakışma Çözümü: Açık Adresleme (Linear Probing)
void insert_package(Package table[], int package_id, const char* dest, const char* status) {
    int index = hash_function_type_a(package_id);
    int original_index = index;

    while (table[index].is_occupied) {
        index = (index + 1) % TABLE_SIZE; // Bir sonraki slota geç
        if (index == original_index) {
            printf("Hata: Hash tablosu dolu!\n");
            return;
        }
    }

    table[index].package_id = package_id;
    strcpy(table[index].destination, dest);
    strcpy(table[index].status, status);
    table[index].is_occupied = true;
    printf("Paket %d eklendi. (Index: %d, Bellek Adresi: %p)\n", package_id, index, (void*)&table[index]);
}

void search_package(Package table[], int package_id) {
    int index = hash_function_type_a(package_id);
    int original_index = index;

    while (table[index].is_occupied) {
        if (table[index].package_id == package_id) {
            printf("Bulundu! ID: %d, Hedef: %s, Durum: %s\n", table[index].package_id, table[index].destination, table[index].status);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == original_index) break;
    }
    printf("Paket %d bulunamadı.\n", package_id);
}
