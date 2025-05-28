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
int inputIntRange(const char *prompt, int min, int max) {
    int value;
    do {
        printf("%s", prompt);
        scanf("%d", &value);
        while(getchar() != '\n');
    } while(value < min || value > max);
    return value;
}

// == FUNCTION inputUser KHUSUS DARI SABBIA ==
void inputUser(User *user) {
    printf("== Nutrition Track == \n");
    printf("Program ini mendukung SDG 3: Good Health and Well - Being\n");
    printf("dengan membantu pengguna memantau dan menyeimbangkan asupan gizi anda.\n\n");
    printf("Masukkan nama Anda: ");
    scanf(" %[^\n]", user->nama);
    user->nama[99] = '\0';

    user->umur = inputIntMin("Masukkan umur Anda: ", 0);

    int pilihan;
    pilihan = inputIntRange("Jenis kelamin (1 = Laki - laki, 2 = Perempuan): ", 1, 2);
    user->gender = (pilihan == 1) ? LAKI_LAKI : PEREMPUAN;
}


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

void inisialisasiMakanan(Makanan **makananList, int *jumlahMakanan, int *kapasitasMakanan) {
    Makanan daftar[] = {
        {"Nasi Putih", 175, 4, 40, 1},
        {"Ayam Goreng", 260, 20, 5, 18},
        {"Tahu Goreng", 120, 10, 3, 8},
        {"Tempe Goreng", 150, 12, 6, 9},
        {"Sayur Bayam", 40, 3, 6, 1},
        {"Telur Rebus", 155, 13, 1, 11},
        {"Roti Gandum", 250, 9, 45, 3},
        {"Ikan Bakar", 200, 22, 0, 10},
        {"Kentang Rebus", 86, 2, 20, 0},
        {"Susu Sapi", 60, 3, 5, 3},
        {"Apel", 52, 0, 14, 0},
        {"Pisang", 89, 1, 23, 0},
        {"Wortel", 41, 1, 10, 0},
        {"Brokoli", 55, 4, 11, 1},
        {"Kacang Merah", 127, 9, 23, 0}
    };

    int n = sizeof(daftar) / sizeof(daftar[0]);
    *kapasitasMakanan = n > 10 ? n : 10; // Minimal kapasitas awal = 10
    *jumlahMakanan = 0;

    *makananList = (Makanan *) malloc(n * sizeof(Makanan));
    if (*makananList == NULL) {
        printf("Gagal mengalokasikan memori untuk daftar makanan.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        // Realloc jika kapasitas tidak cukup (jaga-jaga kalau n bisa lebih besar)
        if (*jumlahMakanan >= *kapasitasMakanan) {
            *kapasitasMakanan *= 2;
            Makanan *temp = (Makanan *) realloc(*makananList, *kapasitasMakanan * sizeof(Makanan));
			if (temp == NULL) {
			    printf("Gagal mengalokasikan ulang memori untuk daftar makanan.\n");
			    exit(1);
			}
			*makananList = temp;
        }
        (*makananList)[*jumlahMakanan] = daftar[i];
        (*jumlahMakanan)++;
    }
}

// Function untuk menampilkan daftar menu makanan yang ingin dipilih
// Dikerjakan oleh Qais Ismail
void tampilkanMenuMakanan(Makanan makanan[], int n) {
    printf("\n=== Daftar Makanan ===\n");
    // printing out calorie, protein, carbs, fat composition of a food / 100g
    for (int i = 0; i < n; i++) {
        printf("%d. %s (per 100g) - %d kcal", i + 1, makanan[i].nama, makanan[i].kalori);
        printf(", %dg protein, %dg karbo, %dg lemak\n", makanan[i].protein, makanan[i].karbo, makanan[i].lemak);
    }
}

// == FUNCTION tampilkanHeader KHUSUS DARI SABBIA ==
void tampilkanHeader(User user, const char* tanggal) {
    printf("\n========================================\n");
    printf(" WELCOME TO NUTRITIONTRACK\n");
    printf(" Your Smart Health Assistant \n");
    printf("========================================\n");
    printf("Nama Pengguna: %s\n", user.nama);
    printf("Umur: %d tahun\n", user.umur);
    printf("Gender: %s\n\n", user.gender == LAKI_LAKI ? "Laki-laki" : "Perempuan");
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

// Function untuk menghitung wellness score
// Dikerjakan Qais Ismail
float hitungWellnessScore(float totalKalori, int kebutuhanKalori, float protein, float karbo, float lemak,
                          int aktivitas, int airMinum, int jamTidur, int screenTime, int mood) {
    // tentukan calorie score
    float skorKalori = 100.0f - (abs(totalKalori - kebutuhanKalori) * 100.0f / kebutuhanKalori);
    if (skorKalori < 0) skorKalori = 0;

    // tentukan protein score
    float skorProtein;
    if (protein >= 50 && protein <= 70) skorProtein = 100.0f;
    else if (protein < 50) skorProtein = protein * 2.0f;
    else skorProtein = 140.0f - protein * 0.5f;

    if (skorProtein < 0) skorProtein = 0;
    else if (skorProtein > 100) skorProtein = 100;
    
    // tentukan carb score
    float skorKarbo;
    if (karbo >= 130 && karbo <= 300) skorKarbo = 100.0f;
    else if (karbo < 130) skorKarbo = karbo * 100.0f / 130.0f;
    else skorKarbo = 300.0f * 100.0f / karbo;

    if (skorKarbo > 100) skorKarbo = 100;

    // tentukan fat score
    float skorLemak;
    if (lemak <= 70) skorLemak = 100.0f;
    else skorLemak = 100.0f - ((lemak - 70) * 100.0f / 70.0f);

    if (skorLemak < 0) skorLemak = 0;
    
    // tentukan activity score
    float skorAktivitas;
    if (aktivitas >= 30) skorAktivitas = 100.0f;
    else skorAktivitas = aktivitas * 3.33f;

    // tentukan hydration score
    float skorAirMinum;
    if (airMinum >= 8) skorAirMinum = 100.0f;
    else skorAirMinum = airMinum * 12.5f;
    
    // tentukan sleep score
    float skorTidur;
    if (jamTidur >= 7 && jamTidur <= 9) skorTidur = 100.0f;
    else skorTidur = jamTidur * 100.0f / 9.0f;

    if (skorTidur > 100) skorTidur = 100;

    // tentukan skor waktu penggunaan gadget
    float skorScreenTime;
    if (screenTime <= 4) skorScreenTime = 100.0f;
    else skorScreenTime = 100.0f - (screenTime - 4) * 10.0f;

    if (skorScreenTime < 0) skorScreenTime = 0;

    // tentukan mood score
    float skorMood = mood * 20.0f;

    // rata-ratakan seluruh skor
    return (skorKalori + skorProtein + skorKarbo + skorLemak +
            skorAktivitas + skorAirMinum + skorTidur + skorScreenTime + skorMood) / 9.0f;
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

void tampilkanRingkasanGabungan(User user, Konsumsi konsumsiList[], int jumlahKonsumsi) {
    float totalKalori = 0, totalProtein = 0, totalKarbo = 0, totalLemak = 0;
    // Kalkulasi total nutrisi
    for (int i = 0; i < jumlahKonsumsi; i++) {
        Konsumsi k = konsumsiList[i];
        totalKalori += k.item.kalori * k.gram / 100;
        totalProtein += k.item.protein * k.gram / 100;
        totalKarbo += k.item.karbo * k.gram / 100;
        totalLemak += k.item.lemak * k.gram / 100;
    }

    int kebutuhanKalori = hitungKebutuhanKalori(user);
    user.aktivitas = inputAktivitas();
    int airMinum = inputAirMinum();
    int jamTidur = inputTidur();
    int screenTime = inputScreenTime();
    int mood = inputMood();
    
    printf("\n========================================\n");
    printf(" WELCOME TO NUTRITION TRACK\n");
    printf(" Your Smart Health Assistant\n");
    printf("========================================\n\n");
    
    // Ringkasan Profil User
	printf("=== Profil Pengguna ===\n");
	printf("Nama          : %s\n", user.nama);
	printf("Jenis Kelamin : %s\n", user.gender == LAKI_LAKI ? "Laki-laki" : "Perempuan");
    printf("Umur          : %d tahun\n", user.umur);
	printf("Berat Badan   : %.1f kg\n", user.berat);
	printf("Tinggi Badan  : %.1f cm\n\n", user.tinggi);

    // Ringkasan Total
    printf("=== Kebutuhan Kalori Harian ===\n");
    printf("Kebutuhan Kalori Anda     : %.0f kcal\n", (float)kebutuhanKalori);
    printf("Kalori yang sudah dipenuhi: %.1f kcal\n", totalKalori);
    float selisihKalori = totalKalori - kebutuhanKalori;

    if (selisihKalori < -100) {
        printf("Status Kalori: Masih kurang %.1f kcal\n", -selisihKalori);
    } else if (selisihKalori > 100) {
        printf("Status Kalori: Kelebihan %.1f kcal\n", selisihKalori);
    } else {
        printf("Status Kalori: Sudah cukup sesuai kebutuhan!\n");
    }

    printf("\n=== Ringkasan Konsumsi Total ===\n");
    for (int i = 0; i < jumlahKonsumsi; i++) {
        Konsumsi k = konsumsiList[i];
        printf("%s - %dg\n", k.item.nama, k.gram);
    }

    printf("\nTotal Kalori : %.1f kcal\n", totalKalori);
    printf("Total Protein: %.1f g\n", totalProtein);
    printf("Total Karbo  : %.1f g\n", totalKarbo);
    printf("Total Lemak  : %.1f g\n", totalLemak);

    // Ringkasan per waktu makan
    printf("\n=== Ringkasan Konsumsi per Waktu Makan ===\n");
    const char* labelWaktu[] = {"Pagi", "Siang", "Malam"};

    for (int waktu = 0; waktu < 3; waktu++) {
        printf("\n[%s]\n", labelWaktu[waktu]);
        float kaloriW = 0;
        int ada = 0;
        for (int i = 0; i < jumlahKonsumsi; i++) {
            if (konsumsiList[i].waktu == waktu) {
                printf("- %s (%dg)\n", konsumsiList[i].item.nama, konsumsiList[i].gram);
                kaloriW += konsumsiList[i].item.kalori * konsumsiList[i].gram / 100;
                ada = 1;
            }
        }
        if (!ada) {
            printf("(Tidak ada konsumsi tercatat)\n");
        } else {
            printf("Total kalori waktu ini: %.1f kcal\n", kaloriW);
        }
    }

    // Aktivitas dan Gaya Hidup
    printf("\n=== Ringkasan Aktivitas dan Gaya Hidup ===\n");
    printf("Aktivitas Fisik : %d menit\n", user.aktivitas);
    printf("Air Diminum     : %d gelas\n", airMinum);
    printf("Tidur           : %d jam\n", jamTidur);
    printf("Screen Time     : %d jam\n", screenTime);
    printf("Mood            : %d / 5\n", mood);

    // BMI
    float bmi = hitungBMI(user.berat, user.tinggi);
    printf("BMI Anda        : %.2f\n", bmi);
    if (bmi < 18.5) {
        printf("Kategori        : Berat badan kurang\n");
    } else if (bmi < 25) {
        printf("Kategori        : Normal\n");
    } else if (bmi < 30) {
        printf("Kategori        : Berat badan berlebih\n");
    } else {
        printf("Kategori        : Obesitas\n");
    }

    float skorWellbeing = hitungWellnessScore(totalKalori, kebutuhanKalori, totalProtein, totalKarbo, totalLemak, user.aktivitas, airMinum, jamTidur, screenTime, mood);
    printf("\n=== Skor Wellbeing Anda: %.2f / 100 ===\n", skorWellbeing);
    tampilkanTips(totalKalori, kebutuhanKalori, user.aktivitas, airMinum, jamTidur, screenTime, mood);
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
