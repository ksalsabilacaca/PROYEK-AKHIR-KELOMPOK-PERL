#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KAPASITAS_AWAL_MAKANAN 15
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

typedef enum {
    PAGI,
    SIANG,
    MALAM
} WaktuMakan;

typedef struct {
    Makanan item;
    int gram;
    WaktuMakan waktu;
} Konsumsi;

typedef struct {
    char nama[100];
    int umur;
    Gender gender;
    float berat;
    float tinggi;
    int aktivitas;
} User;

// Function inputIntMin buat bantu ngecek input yang diketik user itu bener. Jadi misalnya pas mereka masukin umur atau berat badan, kita pastiin nilainya minimal harus logis, kayak umur gak mungkin minus atau berat badan 0 kg. Ini penting banget biar program gak rusak karena salah input. Intinya buat ngejaga supaya input dari user gak bisa lebih kecil dari batas minimum yang masuk akal. Jadi, bikin validasi biar programnya aman dan gak error karena input aneh.
// Dikerjakan oleh Sabbia Meilandri PUtri Delarosya
int inputIntMin(const char *prompt, int min) {                  // Fungsi ini dipakai buat minta input angka dari user, 
                                                                // tapi angka itu harus lebih besar atau sama dengan nilai minimal yang kita tentuin.
                                                                // Misalnya, buat input umur atau berat badan di Nutrition Track — kan nggak mungkin umur negatif.
    int value, rc;                                              // Kita siapin dua variabel: 'value' buat nyimpen angka yang diketik user, 
                                                                // dan 'rc' buat ngecek input-nya berhasil dibaca atau nggak.

    do {                                                        // Kita masukin ke do-while biar terus ngulang sampe input-nya valid.

        printf("%s", prompt);                                   // Tampilkan pertanyaan ke user (misalnya: "Masukkan umur Anda:").

        rc = scanf("%d", &value);                               // Baca input angka dari user dan simpan ke 'value'.
                                                                // 'rc' bakal nilainya 1 kalau user ngisi angka dengan benar.

        while(getchar() != '\n');                               // Ini buat bersihin sisa karakter yang mungkin masih nyangkut di buffer (kayak Enter atau spasi).
                                                                // Biar input selanjutnya nggak ikut-ikutan kacau.

    } while(rc != 1 || value < min);                            // Ulangin terus kalau input-nya bukan angka (rc ? 1) atau angkanya kurang dari minimal.
                                                                // Misalnya: kita pengen minimal berat badan itu 1 kg — kalau user ngisi 0 atau -5, bakal diminta ulang.

    return value;                                               // Kalau input-nya udah valid dan sesuai syarat, langsung kita balikin nilainya.
}

// Function inputIntRange ini digunakan untuk memilih jenis kelamin, dengan pilihan yang dibatasi hanya antara 1 dan 2. Validasi seperti ini penting untuk mencegah pilihan yang tidak valid. Jadi user cuma bisa pilih angka yang sesuai kayak 1 buat laki-laki, 2 buat perempuan. Jadi gak bakal ada user yang masukin angka aneh kayak 7 atau 99 buat gender. Biar data yang masuk juga rapih dan gampang diolah.
// Dikerjakan oleh Sabbia Meilandri Putri Delarosya
int inputIntRange(const char *prompt, int min, int max) {           // Fungsi ini gunanya buat minta input angka dari user,
                                                                    // tapi angkanya harus ada di antara nilai minimal dan maksimal.
                                                                    // Contohnya di Nutrition Track, kita bisa pakai ini buat milih jenis kelamin (1 atau 2),
                                                                    // atau buat input skala mood 1–5, screen time, dan lain-lain.
    int value;                                                      // Ini variabel buat nyimpan angka yang diketik sama user.

    do {                                                            // Mulai perulangan, biar kita bisa ngecek terus sampai input-nya valid.

        printf("%s", prompt);                                       // Tampilkan pertanyaan atau perintah ke user, misalnya:
                                                                    // "Masukkan mood Anda (1 = sangat buruk, 5 = sangat baik): "

        scanf("%d", &value);                                        // Baca angka dari keyboard dan simpan ke 'value'.

        while(getchar() != '\n');                                   // Bersihin sisa karakter di input (misalnya enter, spasi, huruf yang nggak sengaja diketik),
                                                                    // supaya nggak ganggu input berikutnya.

    } while (value < min || value > max);                           // Ulangin terus kalau angka yang dimasukkan kurang dari batas bawah
                                                                    // atau lebih dari batas atas. Misalnya user disuruh pilih antara 1–5,
                                                                    // tapi dia ngisi 6, maka bakal diminta isi ulang.

    return value;                                                   // Kalau angkanya udah di dalam range yang kita mau, kita balikin nilainya.
}

// Function inputUser ini tempat semua data user masuk kayak nama, umur, gender, berat, tinggi. Aku ngebikin ini biar semuanya dikumpulin satu tempat, dan aku manfaatin dua fungsi yang tadi (inputIntMin & inputIntRange) buat ngecek valid nggaknya inputnya. Jadi user gak bakal salah masukin umur atau berat. 
// Dikerjakan oleh Sabbia Meilandri Putri Delarosya
void inputUser(User *user) {                                                      // Fungsi ini dipakai buat ngisi data pengguna di awal program Nutrition Track.
                                                                                  // Jadi semua info penting kayak nama, umur, gender, berat, dan tinggi akan disimpan di struct 'User'.
    printf("=== Nutrition Track ===\n");                                          // Tampilkan judul program biar user tahu dia lagi pakai aplikasi apa.
    printf("Program ini mendukung SDG 3: Good Health and Well-Being\n");         // Info penting: program ini berkontribusi ke tujuan pembangunan berkelanjutan (SDG) nomor 3.
    printf("dengan membantu pengguna memantau dan menyeimbangkan asupan gizi anda.\n\n"); // Jelasin tujuan aplikasinya: bantu user biar gaya hidupnya lebih sehat.

    printf("Masukkan nama Anda: ");                                              // Minta user untuk mengisi nama mereka.
    scanf(" %[^\n]", user->nama);                                                // Baca nama lengkap yang diketik user (termasuk spasi).
    user->nama[99] = '\0';                                                       // Pastikan nama maksimal 99 karakter biar nggak overflow dan program tetap aman.

    user->umur = inputIntMin("Masukkan umur Anda: ", 0);                         // Minta user masukkan umur, minimal 0 tahun.
                                                                                  // Umur ini penting buat hitung kebutuhan kalori harian nantinya.

    int pilihan;                                                                 // Variabel sementara buat nyimpan pilihan gender user (1 atau 2).
    pilihan = inputIntRange("Jenis kelamin (1 = Laki-laki, 2 = Perempuan): ", 1, 2); // Tampilkan pilihan gender, user harus isi 1 atau 2 aja.
    user->gender = (pilihan == 1) ? LAKI_LAKI : PEREMPUAN;                        // Konversi angka yang dipilih user jadi enum gender, disimpan di struct User.

    user->berat = (float)inputIntMin("Masukkan berat badan Anda (kg): ", 1);     // Minta input berat badan user, minimal 1 kg.
                                                                                  // Data berat ini nanti dipakai buat hitung BMI dan kebutuhan kalori.

	user->tinggi = (float)inputIntMin("Masukkan tinggi badan Anda (cm): ", 50);  // Minta input tinggi badan user, minimal 50 cm.
                                                                                  // Tinggi badan juga dipakai untuk hitung BMI yang akan bantu nilai status gizi user.
}


// Function ini berfungsi untuk mengambil jenis dan durasi aktivitas fisik user
// Dikerjakan Novatama Eka Fitria
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

// Function ini berfungsi untuk mengambil jumlah air minum (gelas) yang dikonsumsi user
// Dikerjakan Novatama Eka Fitria
int inputAirMinum() {
    return inputIntMin("\nBerapa gelas air yang diminum hari ini? ", 0);
}

// Function ini berfungsi untuk mengambil durasi tidur user dalam sehari
// Dikerjakan Novatama Eka Fitria
int inputTidur() {
    return inputIntMin("Berapa jam Anda tidur? ", 0);
}

// Function ini berfungsi untuk mengambil durasi screen time user dalam sehari
// Dikerjakan Novatama Eka Fitria
int inputScreenTime() {
    return inputIntMin("Berapa jam screen time (TV/HP/Komputer)? ", 0);
}

// Function ini berfungsi untuk mengambil mood user dengan skala 1 sampai 5
// Dikerjakan Novatama Eka Fitria
int inputMood() {
    int mood = inputIntRange("Bagaimana mood Anda hari ini? (1=sangat buruk ... 5=sangat baik): ", 1, 5);
    return mood;
}

// Function ini berfungsi untuk menghitung nilai Body Mass Index (BMI) seseorang berdasarkan berat dan tinggi badannya
// Dikerjakan Salsabila Maharani Mumtaz
float hitungBMI(float berat, float tinggi) {
    float tinggiMeter = tinggi / 100.0f;
    return berat / (tinggiMeter * tinggiMeter);
}

// Function ini berfungsi untuk menghitung kebutuhan kalori harian seorang pengguna berdasarkan data personal dan tingkat aktivitas fisik
// Dikerjakan Salsabila Maharani Mumtaz
float hitungKebutuhanKalori(User user) {
    float bmr;
    if (user.gender == LAKI_LAKI) {
        bmr = 10 * user.berat + 6.25 * user.tinggi - 5 * user.umur + 5;
    } else {
        bmr = 10 * user.berat + 6.25 * user.tinggi - 5 * user.umur - 161;
    }

    // Asumsikan aktivitas adalah dalam menit per hari (misal 30, 60)
    // Menggunakan faktor aktivitas kasar berdasarkan waktu:
    float faktorAktivitas;
    if (user.aktivitas >= 90) faktorAktivitas = 1.725;
    else if (user.aktivitas >= 60) faktorAktivitas = 1.55;
    else if (user.aktivitas >= 30) faktorAktivitas = 1.375;
    else faktorAktivitas = 1.2;

    float kebutuhanKalori = bmr * faktorAktivitas;
    return kebutuhanKalori;
}

// Function inisialisasiMakanan berfungsi untuk mengisi daftar makanan awal dan mengatur alokasi memori dinamis untuk makanan
// Dikerjakan oleh Syifa Aulia Azhim
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
	
	int i = 0;
    for (i = 0; i < n; i++) {
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
void tampilkanMenuMakanan(Makanan makananList[], int n) {
    printf("\n--- Daftar Makanan ---\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("%d. %s (per 100g) - %d kcal, %dg protein, %dg karbo, %dg lemak\n",
            i + 1, makananList[i].nama, makananList[i].kalori, makananList[i].protein,
            makananList[i].karbo, makananList[i].lemak);
    }
}

// Function tampilkanHeader itu semacam “opening card”-nya program. Aku bikin biar setelah input data tadi, langsung muncul info user-nya di layar. Jadi kesannya kayak aplikasi beneran, profesional gitu. User juga bisa langsung liat datanya udah masuk bener atau belum.
// Dikerjakan oleh Sabbia Meilandri Putri Delarosya
void tampilkanHeader(User user, const char* tanggal) {                              // Fungsi ini dipakai buat nampilin header alias bagian atas tampilan,
                                                                                     // yang berisi info dasar user. Jadi, user tahu datanya udah tercatat.

    printf("\n========================================\n");                         // Garis pembatas biar tampilannya rapi dan menarik dilihat.
    printf(" WELCOME TO NUTRITIONTRACK\n");                                          // Tampilkan sambutan selamat datang buat user, kasih kesan ramah.
    printf(" Your Smart Health Assistant \n");                                       // Penjelasan singkat bahwa program ini adalah asisten pintar untuk bantu jaga gizi dan kesehatan.
    printf("========================================\n");                         // Garis penutup bagian header supaya tampilannya simetris.

    printf("Nama Pengguna: %s\n", user.nama);                                       // Nampilin nama user yang udah dimasukin sebelumnya,
                                                                                     // supaya user merasa lebih personal dan diingat sama aplikasi.

    printf("Umur: %d tahun\n", user.umur);                                           // Nampilin umur user, info ini penting karena berpengaruh ke kebutuhan gizi harian.

    printf("Gender: %s\n\n", user.gender == LAKI_LAKI ? "Laki-laki" : "Perempuan"); // Tampilkan gender user dengan teks yang jelas (bukan angka),
                                                                                     // karena kebutuhan kalori laki-laki dan perempuan bisa beda, jadi penting buat penyesuaian fitur selanjutnya.
}

// Function ini untuk mencatat makanan apa saja yang dimakan pengguna berdasarkan waktu makan (pagi, siang, malam) dan berapa gram yang dikonsumsi
// Dikerjakan Salsabila Maharani Mumtaz
void inputKonsumsi(Makanan **makananList, int *jumlahMakanan, int *kapasitasMakanan,
                   Konsumsi **konsumsiList, int *jumlahKonsumsi, int *kapasitasKonsumsi) {
    int lanjut = 1;

    while (lanjut) {
        printf("\nWaktu makan apa yang ingin dicatat?\n");
        printf("1. Pagi\n2. Siang\n3. Malam\n");
        int waktuInput = inputIntRange("Pilih waktu makan (1-3): ", 1, 3);
        WaktuMakan waktu = (WaktuMakan)(waktuInput - 1);

        int tambah = 1;
        while (tambah) {
            // Cek dan perluas konsumsiList jika penuh
            if (*jumlahKonsumsi >= *kapasitasKonsumsi) {
                *kapasitasKonsumsi *= 2;
                Konsumsi *temp = (Konsumsi *) realloc(*konsumsiList, (*kapasitasKonsumsi) * sizeof(Konsumsi));
                if (temp == NULL) {
                    printf("Gagal mengalokasikan memori tambahan untuk konsumsi.\n");
                    exit(EXIT_FAILURE);
                }
                *konsumsiList = temp;
            }

            printf("\nPilih metode input makanan:\n");
            printf("1. Pilih dari daftar makanan\n");
            printf("2. Input makanan baru\n");
            int metode = inputIntMin("Pilihan (1/2): ", 1);

            Makanan makanan;
            if (metode == 1 && *jumlahMakanan > 0) {
                tampilkanMenuMakanan(*makananList, *jumlahMakanan);
                int pilihan = inputIntMin("Pilih makanan (nomor): ", 1);
                while (pilihan < 1 || pilihan > *jumlahMakanan) {
                    printf("Pilihan tidak valid.\n");
                    pilihan = inputIntMin("Pilih makanan (nomor): ", 1);
                }
                makanan = (*makananList)[pilihan - 1];
            } else {
                printf("Masukkan nama makanan: ");
                scanf(" %[^\n]", makanan.nama);
                makanan.nama[99] = '\0';

                makanan.kalori = inputIntMin("Kalori per 100g: ", 0);
                makanan.protein = inputIntMin("Protein per 100g (gram): ", 0);
                makanan.karbo = inputIntMin("Karbohidrat per 100g (gram): ", 0);
                makanan.lemak = inputIntMin("Lemak per 100g (gram): ", 0);

                // Periksa dan perluas makananList jika penuh
                if (*jumlahMakanan >= *kapasitasMakanan) {
                    *kapasitasMakanan *= 2;
                    Makanan *temp = (Makanan *) realloc(*makananList, *kapasitasMakanan * sizeof(Makanan));
					if (temp == NULL) {
					    printf("Gagal mengalokasikan ulang memori untuk daftar makanan.\n");
					    exit(1);
					}
					*makananList = temp;
                }
                (*makananList)[*jumlahMakanan] = makanan;
                (*jumlahMakanan)++;
            }
            // Bukti penggunaan array dinamis dengan alokasi memori dinamis dan pointer

            int gram = inputIntMin("Berapa gram dikonsumsi? (1-1000): ", 1);
            while (gram > 1000) {
                printf("Nilai terlalu besar. Maksimal 1000 gram.\n");
                gram = inputIntMin("Berapa gram dikonsumsi? (1-1000): ", 1);
            }

            (*konsumsiList)[*jumlahKonsumsi].item = makanan;
            (*konsumsiList)[*jumlahKonsumsi].gram = gram;
            (*konsumsiList)[*jumlahKonsumsi].waktu = waktu;
            (*jumlahKonsumsi)++;

            tambah = inputIntMin("Tambah makanan untuk waktu makan ini lagi? (1=Ya, 0=Tidak): ", 0);
        }

        lanjut = inputIntMin("Ingin input makanan untuk waktu makan lain? (1=Ya, 0=Tidak): ", 0);
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

// Function ini berfungsi untuk memberikan saran kepada user berdasarkan data gaya hidup yang telah dimasukkan
// Dikerjakan Novatama Eka Fitria
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

// Function tampilkanRingkasanGabungan berfungsi untuk menampilkan ringkasan lengkap aktivitas pengguna hari ini.
// Dikerjakan oleh Syifa Aulia Azhim
void tampilkanRingkasanGabungan(User user, Konsumsi konsumsiList[], int jumlahKonsumsi) {
    float totalKalori = 0, totalProtein = 0, totalKarbo = 0, totalLemak = 0;
    // Kalkulasi total nutrisi
    int i = 0;
    for (i = 0; i < jumlahKonsumsi; i++) {
        Konsumsi k = konsumsiList[i];
        totalKalori += k.item.kalori * k.gram / 100;
        totalProtein += k.item.protein * k.gram / 100;
        totalKarbo += k.item.karbo * k.gram / 100;
        totalLemak += k.item.lemak * k.gram / 100;
    }
    
    // Hitung kebutuhan kalori harian berdasarkan data user
    int kebutuhanKalori = hitungKebutuhanKalori(user);
    
    // Ambil data aktivitas dan gaya hidup dari input pengguna
    user.aktivitas = inputAktivitas();   // Input durasi aktivitas fisik
    int airMinum = inputAirMinum();      // Input jumlah air yang diminum (gelas)
    int jamTidur = inputTidur();         // Input jam tidur
    int screenTime = inputScreenTime();  // Input screen time (jam)
    int mood = inputMood();              // Input mood 1-5ang 
    
    // Tampilan awal ringkasan
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
    
    // Cek apakah kalori sudah cukup, kurang, atau kelebihan
    float selisihKalori = totalKalori - kebutuhanKalori;
    if (selisihKalori < -100) {
        printf("Status Kalori: Masih kurang %.1f kcal\n", -selisihKalori);
    } else if (selisihKalori > 100) {
        printf("Status Kalori: Kelebihan %.1f kcal\n", selisihKalori);
    } else {
        printf("Status Kalori: Sudah cukup sesuai kebutuhan!\n");
    }

    printf("\n=== Ringkasan Konsumsi Total ===\n");
    for (i = 0; i < jumlahKonsumsi; i++) {
        Konsumsi k = konsumsiList[i];
        printf("%s - %dg\n", k.item.nama, k.gram);
    }
    
     // Tampilkan total nutrisi keseluruhan
    printf("\nTotal Kalori : %.1f kcal\n", totalKalori);
    printf("Total Protein: %.1f g\n", totalProtein);
    printf("Total Karbo  : %.1f g\n", totalKarbo);
    printf("Total Lemak  : %.1f g\n", totalLemak);

    // Ringkasan per waktu makan
    printf("\n=== Ringkasan Konsumsi per Waktu Makan ===\n");
    const char* labelWaktu[] = {"Pagi", "Siang", "Malam"};
	
	int waktu;
    for (waktu = 0; waktu < 3; waktu++) {
        printf("\n[%s]\n", labelWaktu[waktu]);
        float kaloriW = 0;
        int ada = 0;
        int i;
        for (i = 0; i < jumlahKonsumsi; i++) {
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

// main untuk memanggil function-function yang ada
// Dikerjakan Salsabila Maharani Mumtaz
int main() {
    User user; // Deklarasi variabel user untuk menyimpan data pengguna
	//Mengalokasikan array dinamis awal untuk menyimpan data makanan yang dikonsumsi (konsumsiList)
    int kapasitasKonsumsi = KONSUMSI_AWAL; 
    Konsumsi *konsumsiList = (Konsumsi *) malloc(kapasitasKonsumsi * sizeof(Konsumsi));
    if (konsumsiList == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        return 1;
    }
    int jumlahKonsumsi = 0;
	//Menyediakan array dinamis untuk daftar makanan yang tersedia (makananList).
    int kapasitasMakanan = KAPASITAS_AWAL_MAKANAN;
    int jumlahMakanan = 0;
    Makanan *makananList = (Makanan *)malloc(kapasitasMakanan * sizeof(Makanan));
    if (makananList == NULL) {
        printf("Gagal mengalokasikan memori untuk daftar makanan.\n");
        return 1;
    }
    // call by reference function
    inputUser(&user); // Memanggil funtion yang berisi nama, tinggi badan, berat badan
    inisialisasiMakanan(&makananList, &jumlahMakanan, &kapasitasMakanan); //Mengisi makananList dengan daftar makanan default
    // user dapat memilih waktu makan, memilih makanan (dari daftar atau input baru), input gram yang dikonsumsi,Data tersebut disimpan dalam konsumsiList beserta waktu makannya 
    inputKonsumsi(&makananList, &jumlahMakanan, &kapasitasMakanan, &konsumsiList, &jumlahKonsumsi, &kapasitasKonsumsi);
	// Menampilkan Header kebutuhan kalori
	// Menampilkan total konsumsi harian dan konsumsi per waktu makan
	// Menampikan aktivitas fisik, jumlah gelas air minum, jam tidur, screen time, mood, BMI & Kategorinya
	// Menampilkan skor wellbeing dan tips
    tampilkanRingkasanGabungan(user, konsumsiList, jumlahKonsumsi);

    free(konsumsiList); 
    free(makananList);
    printf("\nTerima kasih telah menggunakan Nutrition Track!\n");

    return 0;
}