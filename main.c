#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_MAKANAN 20
#define KONSUMSI_AWAL 10

typedef struct {
    char nama[100];
    int kalori;
    int protein;
    int karbo;
    int lemak;
} Makanan;

typedef enum {
    LAKI_LAKI,
    PEREMPUAN
} Gender;

typedef struct {
    Makanan item;
    int gram;
} Konsumsi;

typedef struct {
    char nama[100];
    int umur;
    Gender gender;
} User;

// === FUNCTION inputIntMin KHUSUS DARI SABBIA ===
int inputIntMin (const char *prompt, int min)  {
    int value, rc;
    do {
        printf("%s", prompt);
        rc = scanf("%d", &value);
        while(getchar() != '\n');
    } while(rc != 1 || value < min);
    return value;

}

// === FUNCTION inputIntRange KHUSUS DARI SABBIA ==

int inputAktivitas() {
    printf("\n=== Input Aktivitas Fisik ===\n");
    printf("Pilih jenis aktivitas yang dilakukan hari ini:\n");
    printf("1. Tidak ada aktivitas\n");
    printf("2. Jalan kaki ringan (30 menit)\n");
    printf("3. Lari sedang (60 menit)\n");
    printf("4. Latihan intensif (90 menit)\n");
    printf("Pilihan Anda: ");
    int pilihan;
    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1: return 0;
        case 2: return 30;
        case 3: return 60;
        case 4: return 90;
        default: 
            printf("Pilihan tidak valid. Dianggap tidak ada aktivitas.\n");
            return 0;
    }
}

int inputAirMinum() {
    return inputIntMin("\nBerapa gelas air yang diminum hari ini? ", 0);
}

int inputTidur() {
    return inputIntMin("Berapa jam Anda tidur? ", 0);
}

int inputScreenTime() {
    return inputIntMin("Berapa jam screen time (TV/HP/Komputer)? ", 0);
}

int inputMood() {
    int mood = inputIntRange("Bagaimana mood Anda hari ini? (1=sangat buruk ... 5=sangat baik): ", 1, 5);
    return mood;
}

void tampilkanMenuMakanan(Makanan makanan[], int n) {
    printf("\n=== Daftar Makanan ===\n");
    // printing out calorie, protein, carbs, fat composition of a food / 100g
    for (int i = 0; i < n; i++) {
        printf("%d. %s (per 100g) - %d kcal", i + 1, makanan[i].nama, makanan[i].kalori);
        printf(", %dg protein, %dg karbo, %dg lemak\n", makanan[i].protein, makanan[i].karbo, makanan[i].lemak);
    }
}

void inputKonsumsi(Makanan makananList[], int *jumlahMakanan, Konsumsi **konsumsiList,
                   int *jumlahKonsumsi, int *kapasitasKonsumsi) {
    int lanjut = 1;
    while (lanjut) {
        if (*jumlahKonsumsi >= *kapasitasKonsumsi) {
            *kapasitasKonsumsi *= 2;
            Konsumsi *temp = (Konsumsi *) realloc(*konsumsiList, (*kapasitasKonsumsi) * sizeof(Konsumsi));
            if (temp == NULL) {
                printf("Gagal mengalokasikan memori tambahan.\n");
                exit(EXIT_FAILURE);
            }
            *konsumsiList = temp; 
        }

        printf("\nPilih metode input makanan:\n");
        printf("1. Pilih dari daftar makanan\n");
        printf("2. Input makanan baru\n");
        int metode = inputIntMin("Pilihan (1/2): ", 1);

        Makanan makanan;
        if (metode == 1) {
            if (*jumlahMakanan == 0) {
                printf("Daftar makanan kosong, silakan input makanan baru.\n");
                metode = 2;
            } else {
                tampilkanMenuMakanan(makananList, *jumlahMakanan);
                int pilihan = inputIntMin("Pilih makanan (nomor): ", 1);
                while (pilihan < 1 || pilihan > *jumlahMakanan) {
                    printf("Pilihan tidak valid.\n");
                    pilihan = inputIntMin("Pilih makanan (nomor): ", 1);
                }
                makanan = makananList[pilihan - 1];
            }
        }

        if (metode == 2) {
            printf("Masukkan nama makanan: ");
            scanf(" %[^\n]", makanan.nama);
            makanan.nama[99] = '\0';

            makanan.kalori = inputIntMin("Kalori per 100g: ", 0);
            makanan.protein = inputIntMin("Protein per 100g (gram): ", 0);
            makanan.karbo = inputIntMin("Karbohidrat per 100g (gram): ", 0);
            makanan.lemak = inputIntMin("Lemak per 100g (gram): ", 0);

            if (*jumlahMakanan < MAX_MAKANAN) {
                makananList[*jumlahMakanan] = makanan;
                (*jumlahMakanan)++;
            } else {
                printf("Maaf, daftar makanan sudah penuh.\n");
            }
        }

        int gram = inputIntMin("Berapa gram dikonsumsi? (1-1000): ", 1);
        while (gram > 1000) {
            printf("Nilai terlalu besar. Maksimal 1000 gram.\n");
            gram = inputIntMin("Berapa gram dikonsumsi? (1-1000): ", 1);
        }

        (*konsumsiList)[*jumlahKonsumsi].item = makanan;
        (*konsumsiList)[*jumlahKonsumsi].gram = gram;
        (*jumlahKonsumsi)++;

        lanjut = inputIntMin("Tambah makanan lagi? (1=Ya, 0=Tidak): ", 0);
    }
}

void tampilkanTips(int totalKalori, int kebutuhanKalori, int aktivitas, int airMinum, int jamTidur, int screenTime, int mood) {
    printf("\n=== Tips dan Saran untuk Anda ===\n");

    if (totalKalori < kebutuhanKalori) {
        printf("- Tambah makanan bergizi untuk mencukupi kebutuhan kalori harian.\n");
    } else if (totalKalori > kebutuhanKalori + 500) {
        printf("- Perhatikan porsi makan agar tidak berlebihan kalori.\n");
    }

    if (aktivitas < 30) {
        printf("- Coba jalan kaki sebentar atau lakukan aktivitas fisik ringan.\n");
    } else {
        printf("- Aktivitas fisik Anda sudah baik, pertahankan ya!\n");
    }

    if (airMinum < 8) {
        printf("- Minum air putih lebih banyak agar tubuh tetap terhidrasi.\n");
    }

    if (jamTidur < 7) {
        printf("- Usahakan tidur minimal 7 jam agar tubuh lebih segar.\n");
    } else if (jamTidur > 9) {
        printf("- Tidur terlalu lama juga bisa kurang baik, jaga pola tidur.\n");
    }

    if (screenTime > 12) {
        printf("- Kurangi screen time malam agar mata dan otak lebih rileks.\n");
    }

    if (mood <= 2) {
        printf("- Hari ini memang berat, tapi kamu bisa mulai lagi besok.\n");
    } else if (mood >= 4) {
        printf("- Mood kamu bagus hari ini, pertahankan semangatnya!\n");
    } else {
        printf("- Jaga mood dan kesehatan tubuhmu ya.\n");
    }
}

int main() {
    User user;
    Makanan makananList[MAX_MAKANAN]; 

    int kapasitasKonsumsi = 10; 
    Konsumsi *konsumsiList = (Konsumsi *) malloc(kapasitasKonsumsi * sizeof(Konsumsi));
    if (konsumsiList == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        return 1;
    }

    int jumlahMakanan = 0, jumlahKonsumsi = 0;

    inisialisasiMakanan(makananList, &jumlahMakanan);
    inputUser(&user);
    inputKonsumsi(makananList, &jumlahMakanan, &konsumsiList, &jumlahKonsumsi, &kapasitasKonsumsi);

    tampilkanRingkasan(user, konsumsiList, jumlahKonsumsi);

    free(konsumsiList); 
    printf("\nTerima kasih telah menggunakan Nutrition Track!\n");

    return 0;
}