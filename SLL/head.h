#ifndef HEAD_H
#define HEAD_H
#define MAX 100

typedef struct warga* address;
// membuat node untuk warga
typedef struct warga{
    char nm[MAX];
    address q;
}warga;

// membuat node untuk kota
typedef struct kota{
    char kt[MAX];
    address p;
}kota;

typedef struct arrayKota{
    int length;
    kota *kota;
}arrayKota;

// MODUL NON-CONTROL
void banner();
void alokasiArray(arrayKota *P);
address alokasi(char *nama);
void mainProgram();

// MODUL CONTROL
void addWarga(arrayKota *P, char *nama, char *domisili);
void printMasyarakat(arrayKota P);
void deleteWarga(arrayKota *P, char *nama, char *domisili);
void deleteKota(arrayKota *P, char *namaKota);

#endif