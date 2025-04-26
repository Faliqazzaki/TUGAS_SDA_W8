#ifndef HEAD_H
#define HEAD_H
#define MAX 100

typedef struct warga* address;
typedef struct kota* addressKota;
// membuat node untuk warga
typedef struct warga{
    char nm[MAX];
    address q;
}warga;

// membuat node untuk kota
typedef struct kota{
    addressKota next; // menunjuk kearah kota selanjutnya
    char kt[MAX]; // nama kota
    address p; // menunjuk kearah warga linked list
}kota;

typedef struct {
    addressKota first;
}List; // list menunjuk ke sebuah linkedlist kota

// MODUL NON-CONTROL NODE
void banner();
addressKota alokasiKota(char *domisili);
address alokasi(char *nama);
void mainProgram();

// MODUL CONTROL NODE
void addKota(List *P, char *domisili);
void addWarga(List *P, char *nama, char *domisili);
void printMasyarakat(List P);
void deleteWarga(List *dataKota, char *nama, char *domisili);
void deleteKota(List *dataKota, char *kota);

#endif