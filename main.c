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