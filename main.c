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