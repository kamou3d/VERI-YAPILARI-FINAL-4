# VERI-YAPILARI-FINAL-4
# Lojistik Yönetim Sistemi - Veri Yapıları Final Projesi

Bu proje, bir lojistik firmasının şehirler arası bağlantılarını ve paket takip süreçlerini yönetmek amacıyla C dilinde geliştirilmiş hibrit bir veri yapısı sistemidir. Sistem, graf (graph) teorisi ve hızlı indeksleme (hash table) mekanizmalarını modüler bir mimaride birleştirerek bellek optimizasyonu ve yüksek performanslı sorgulama hedefler.

## 📌 Proje Özeti
Proje, teslimat ağındaki düğümleri (şehirleri) ve bu düğümler arasındaki yolları yönetirken, sistemdeki paketlerin durumlarını sabit zaman karmaşıklığına yakın bir sürede sorgulamayı sağlar. 

Kullanılan temel veri yapıları ve atanan spesifik konfigürasyonlar (Öğrenci No Sonu: 62) şunlardır:
*   **İndeksleme (Hash Table):** Tip A (Modülo Aritmetiği)
*   **Çakışma Çözümü (Collision):** Açık Adresleme (Linear Probing / Doğrusal Yoklama)
*   **Ağ Gezinmesi (Graph Traversal):** BFS (Breadth-First Search / Sığ Öncelikli Arama)

## ⚙️ Teknik Mimari ve Algoritma Analizi

### 1. Hash Tablosu (Paket Yönetimi)
Paketlerin bellekte tutulması ve sorgulanması için yapılandırılmıştır.
*   **Hash Fonksiyonu:** `h(k) = k mod m` (Burada `k` paket ID'si, `m` ise tablo boyutudur).
*   **Linear Probing:** Çakışma durumunda algoritma `(h(k) + i) mod m` formülünü kullanarak bir sonraki boş bellek bloğunu (slot) arar.
*   **Zaman Karmaşıklığı (Time Complexity):** 
    *   Arama/Ekleme (Ortalama): **O(1)**
    *   Arama/Ekleme (En Kötü Durum - Tablo doluysa): **O(n)**

### 2. Graf Yapısı (Şehir Ağı)
Şehirler arası ulaşım ağı, belleği verimli kullanmak adına **Komşuluk Listesi (Adjacency List)** kullanılarak modellenmiştir. Dinamik bellek tahsisi (`malloc`) ile düğümler arası *Linked List* (Bağlı Liste) işaretçileri (pointers) kurulmuştur.
*   **BFS Algoritması:** Lojistik ağında belirli bir şehirden başlayarak katman katman (seviye bazlı) gezinme işlemi yapar. Hedef arama ve en kısa yol analizleri için altyapı sunar.
*   **Zaman Karmaşıklığı:** **O(V + E)** (`V`: Düğüm/Şehir sayısı, `E`: Kenar/Yol sayısı).

## 📂 Modüler Dosya Yapısı
Kod tabanı, mantıksal sorumluluklarına göre parçalara ayrılmıştır:

```text
.
├── logistics.h    # Veri yapıları (struct), sabitler ve fonksiyon prototipleri
├── hash.c         # Tip A Hash fonksiyonu ve Open Addressing implementasyonları
├── graph.c        # Dinamik graf düğümü oluşturma ve BFS gezinme mantığı
├── main.c         # Test senaryoları, ana akış ve bellek adresleme çıktısı
└── README.md      # Teknik dokümantasyon
```

## 🚀 Kurulum ve Çalıştırma

### Gereksinimler
Projeyi derleyip çalıştırabilmek için sisteminizde aşağıdaki araçların kurulu olması gerekmektedir:
*   `gcc` (GNU Compiler Collection)
*   `git`
*   `make` (Opsiyonel, otomatik derleme için)
*   `valgrind` (Opsiyonel, bellek sızıntısı analizi için)

### Adım Adım Kurulum

**1. Depoyu Klonlayın**
Terminalinizi açın ve projeyi yerel makinenize indirin:
```bash
git clone <repository-linki>
cd <proje-klasoru>
```

**2. Projeyi Derleyin**
Eğer bir `Makefile` kullanıyorsanız doğrudan `make` komutunu çalıştırabilirsiniz:
```bash
make
```
Alternatif olarak, GCC ile manuel olarak derlemek için:
```bash
gcc main.c hash.c graph.c -o logistics_system
```

**3. Programı Çalıştırın**
Derleme işlemi tamamlandıktan sonra oluşan çalıştırılabilir dosyayı başlatın:
```bash
./logistics_system
```

**4. Bellek Sızıntısı Kontrolü (Opsiyonel)**
Graf yapısındaki dinamik düğümlerin ve hash tablosunun bellek yönetimini analiz etmek için `valgrind` kullanabilirsiniz:
```bash
valgrind --leak-check=full ./logistics_system
```

## 📊 Bellek İzleme ve Analiz Raporu
Sistem tasarımı gereği, çalışma zamanında bellekteki durumları izlemek mümkündür. Program çalıştırıldığında; Hash tablosundaki kayıtların ve Graf yapısında dinamik olarak oluşturulan düğümlerin RAM üzerindeki anlık `0x...` hex bellek adresleri terminale yazdırılır. Pointer bağlantılarının şematik gösterimi ve detaylı RAM durumu, proje teslimine **Ek Dosya (PDF)** olarak dahil edilmiştir.

## 🤖 Geliştirici Notları
*   Projenin bellek yönetimi (memory management) manuel olarak yapılmıştır. Tahsis edilen dinamik alanların takibi ve optimizasyonu ön planda tutulmuştur.
*   *Kod dökümantasyonu, genel yapı iskeletinin oluşturulması ve README dosyasının hazırlanması süreçlerinde Gemini AI asistanından faydalanılmıştır.*
