#include "head.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define Nil NULL

void mainProgram() {
    arrayKota dataKota;
    int i = 0;
    char nama[MAX];
    char kota[MAX];
    char pilihan;
    int menu;

    banner();
    printf("\nPROGRAM KEPENDUDUKAN\n");
    printf("SELAMAT DATANG DALAM PROGRAM KEPENDUDUKAN\n");

    for (;;) {
        printf("\n");
        printf("====================[ PILIHAN PROGRAM ]====================\n");
        printf("1. Tambah Kota\n");
        printf("2. Tambah Warga\n");
        printf("3. Cetak Daftar Masyarakat\n");
        printf("4. Hapus Warga\n");
        printf("5. Hapus Kota\n");
        printf("6. Keluar\n");
        printf("Pilihan Anda: ");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &menu);

        if (menu == 1) {
            alokasiArray(&dataKota);
            // Input nama kota
            while (i < dataKota.length) {
                printf("Input nama kota ke-%d: ", i + 1);
                scanf("%99s", dataKota.kota[i].kt);
                dataKota.kota[i].p = Nil;
                i++;
            }
        }
        else if (menu == 2) { 
            // Menambahkan warga ke kota
            do {
                printf("\nMasukkan nama warga: ");
                scanf("%s", nama);
                printf("Masukkan domisili kota: ");
                scanf("%s", kota);

                addWarga(&dataKota, nama, kota);

                printf("Apakah ingin menambahkan warga lagi? (y/n): ");
                scanf(" %c", &pilihan);
            } while (pilihan == 'y' || pilihan == 'Y');
        } 
        else if (menu == 3) {
            // Cetak daftar masyarakat
            printf("\nDaftar masyarakat:\n");
            printMasyarakat(dataKota);
        }
        else if (menu == 4) { 
            // Menu hapus warga
            do {
                printf("\nApakah ingin menghapus warga? (y/n): ");
                scanf(" %c", &pilihan);
                if (pilihan == 'y' || pilihan == 'Y') {
                    printf("Masukkan nama warga yang ingin dihapus: ");
                    scanf("%s", nama);
                    printf("Masukkan domisili kota: ");
                    scanf("%s", kota);

                    deleteWarga(&dataKota, nama, kota);
                }
            } while (pilihan == 'y' || pilihan == 'Y');

            printf("\nDaftar masyarakat setelah penghapusan:\n");
            printMasyarakat(dataKota);
        } 
        else if (menu == 5) {
            // Menu hapus kota
            do {
                printf("\nApakah ingin menghapus kota? (y/n): ");
                scanf(" %c", &pilihan);
                if (pilihan == 'y' || pilihan == 'Y') {
                    printf("Masukkan nama kota yang ingin dihapus: ");
                    scanf("%s", kota);
                    deleteKota(&dataKota, kota);
                }
            } while (pilihan == 'y' || pilihan == 'Y');

            printf("\nDaftar masyarakat setelah penghapusan kota:\n");
            printMasyarakat(dataKota);
        } 
        else if (menu == 6) {
            // Keluar program
            printf("\nProgram selesai. Terima kasih!\n");

            // Bebaskan memori
            for (int i = 0; i < dataKota.length; i++) {
                address temp = dataKota.kota[i].p;
                while (temp != Nil) {
                    address toFree = temp;
                    temp = temp->q;
                    free(toFree);
                }
            }
            free(dataKota.kota);
            return; // Keluar dari mainProgram
        } 
        else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    }
}

void alokasiArray(arrayKota *P){
    do {
        if((*P).length < 5) {
            printf("Panjang array masih kurang!!!\n");
        }
        printf("\nMasukkan jumlah kota: ");
        scanf("%d", &(*P).length);
        (*P).kota = malloc(sizeof(kota) * (*P).length);
    } while ((*P).length < 5);
}

address alokasi(char *nama){
    address P = (address)malloc(sizeof(warga));
    if(P != Nil){
        strcpy(P->nm, nama);
        P->q = Nil;
    } else {
        printf("Alokasi gagal!!\n");
    }
    return P;
}

void addWarga(arrayKota *P, char *nama, char *domisili){
    address warga = alokasi(nama);
    int i = 0;
    address temp;
    if(warga != Nil){
        while(strcmp((*P).kota[i].kt, domisili) != 0){
            i++;
        }
        // terjadi jika tidak ada sebuah kota
        if(i >= (*P).length){
            printf("Tidak ada kota!!!\n");
            return;
        } else {
            // terjadi jika terdapat sebuah kota
            temp = (*P).kota[i].p;
            if(temp != Nil){
                while(temp->q != Nil){
                    temp = temp->q;
                }
                temp->q = warga;
            } else {
                (*P).kota[i].p = warga;
            }
        }
    } else {
        printf("Alokasi gagal!!\n");
        return;
    }
}

void printMasyarakat(arrayKota P) {
    int i;
    address temp;
    if (P.kota != Nil) {
        i = 0;
        while (i < P.length) {
            printf("Kota %d : %s", i + 1, P.kota[i].kt);
            printf("\nWarga : ");
            temp = P.kota[i].p;
            if (temp != Nil) {
                while (temp != Nil) {
                    printf("%s , ", temp->nm);
                    temp = temp->q;
                }
            } else {
                printf("(Nil)");
            }
            printf("\n");
            i++;
        }
    } else {
        printf("tidak ada kota dan warga");
    }
}

void banner(){
    printf("===============================================================\n");
    printf("    ___                         _          _____ _      _     \n");
    printf("   / _ \\                       | |        /  ___| |    | |    \n");
    printf("  / /_\\ \\_ __ _ __ __ _ _   _  | |_ ___   \\ `--.| |    | |    \n");
    printf("  |  _  | '__| '__/ _` | | | | | __/ _ \\   `--. \\ |    | |    \n");
    printf("  | | | | |  | | | (_| | |_| | | || (_) | /\\__/ / |____| |__  \n");
    printf("  \\_| |_/_|  |_|  \\__,_|\\__, |  \\__\\___/  \\____/\\_____/\\_____/\n");
    printf("                         __/ |                                \n");
    printf("                        |___/                                 \n");
    printf("===============================================================");
}

void deleteWarga(arrayKota *dataKota, char *nama, char *domisili){
    int i = 0;
    address first = Nil;
    address temp = Nil;
    address prev = Nil;

    if (dataKota == NULL || nama == NULL || domisili == NULL) {
        printf("Input tidak valid!\n");
        return;
    }

    while ((i < dataKota->length) && strcmp(dataKota->kota[i].kt, domisili) != 0) {
        i++;
    }

    if (i >= dataKota->length) {
        printf("Kota tidak ditemukan!\n");
        return;
    }

    first = dataKota->kota[i].p;
    if (first != Nil) {
        if (strcmp(dataKota->kota[i].p->nm, nama) == 0) { // Kondisi untuk node berada di posisi pertama
            temp = dataKota->kota[i].p;
            dataKota->kota[i].p = dataKota->kota[i].p->q;
            temp->q = Nil;
            free(temp);
        } else {
            while (first != Nil) { // Loop untuk node tidak di pertama, bisa di tengah atau di akhir
                prev = first;
                first = first->q;
                if (first != Nil && strcmp(first->nm, nama) == 0) { // Kondisi untuk menghapus data di tengah
                    temp = first;
                    first = first->q;
                    prev->q = first;
                    free(temp);
                }
            }
        }
        printf("Penghapusan warga %s berhasil di kota %s\n", nama, dataKota->kota[i].kt);
        return;
    } else {
        printf("Tidak ada warga yang bisa dihapus di kota %s\n", dataKota->kota[i].kt);
        return;
    }
}

void deleteKota(arrayKota *dataKota, char *namaKota){
    int i = 0, j;
    address temp = Nil;
    address toFree = Nil;

    if (dataKota == NULL || namaKota == NULL) {
        printf("Input tidak valid!\n");
        return;
    }

    while (i < dataKota->length && strcmp(dataKota->kota[i].kt, namaKota) != 0) {
        i++;
    }

    if (i >= dataKota->length) {
        printf("Kota tidak ditemukan!\n");
        return;
    }
    temp = dataKota->kota[i].p;
    while (temp != Nil) {
        toFree = temp;
        temp = temp->q;
        free(toFree);
    }

    for (j = i; j < dataKota->length - 1; j++) {
        dataKota->kota[j] = dataKota->kota[j + 1];
    }

    dataKota->length--;

    printf("Kota %s berhasil dihapus!\n", namaKota);
}