#include <stdio.h>
#include "head.h"
#include "body.c"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#define Nil NULL

int main(void){
    arrayKota dataKota;
    int i = 0;
    char nama[MAX];
    char kota[MAX];
    char pilihan;
    banner();
    printf("\nPROGRAM KEPENDUDUKAN.");
    printf("\nSELAMAT DATANG DALAM PROGRAM KEPENDUDUKAN");
    printf("\nMasukkan Jumlah kota : ");
    alokasiArray(&dataKota);
    // loop untuk memasukkan nama kota
    printf("Input nama Kota.\n");
    while(i < dataKota.length){
        printf("Input nama kota ke %d : ", i+1);
        scanf("%99s", dataKota.kota[i].kt);
        dataKota.kota[i].p = Nil;
        i++;
    }
    // Menambahkan warga ke kota
    do {
        printf("Masukkan nama warga: ");
        scanf("%s", nama);
        printf("Masukkan domisili kota: ");
        scanf("%s", kota);

        addWarga(&dataKota, nama, kota);

        printf("Apakah ingin menambahkan warga lagi? (y/n): ");
        scanf(" %c", &pilihan);
    } while (pilihan == 'y' || pilihan == 'Y');

    // Cetak daftar masyarakat
    printf("\nDaftar masyarakat:\n");
    printMasyarakat(dataKota);

    // Bebaskan memori yang dialokasikan
    for (int i = 0; i < dataKota.length; i++) {
        address temp = dataKota.kota[i].p;
        while (temp != Nil) {
            address toFree = temp;
            temp = temp->q;
            free(toFree);
        }
    }
    free(dataKota.kota);
    // arrayKota dataKota;

    // Menu hapus warga
    printf("\nApakah ingin menghapus warga? (y/n): ");
    scanf(" %c", &pilihan);
    while (pilihan == 'y' || pilihan == 'Y') {
        printf("Masukkan nama warga yang ingin dihapus: ");
        scanf("%s", nama);
        printf("Masukkan domisili kota: ");
        scanf("%s", kota);

        deleteWarga(&dataKota, nama, kota);

        printf("Hapus warga lagi? (y/n): ");
        scanf(" %c", &pilihan);
    }

    // Menu hapus kota
    printf("\nApakah ingin menghapus kota? (y/n): ");
    scanf(" %c", &pilihan);
    while (pilihan == 'y' || pilihan == 'Y') {
        printf("Masukkan nama kota yang ingin dihapus: ");
        scanf("%s", kota);

        deleteKota(&dataKota, kota);

        printf("Hapus kota lagi? (y/n): ");
        scanf(" %c", &pilihan);
    }

    return 0;
}