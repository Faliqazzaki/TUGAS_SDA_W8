#include "head.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#define Nil NULL

void mainProgram(){
    arrayKota dataKota;
    int i = 0;
    char nama[MAX];
    char kota[MAX];
    char pilihan;

    banner();
    printf("\nPROGRAM KEPENDUDUKAN\n");
    printf("SELAMAT DATANG DALAM PROGRAM KEPENDUDUKAN\n");

    // Alokasi array untuk kota
    
    alokasiArray(&dataKota);

    // Input nama kota
    printf("\nInput nama kota:\n");
    while (i < dataKota.length) {
        printf("Input nama kota ke-%d: ", i + 1);
        scanf("%99s", dataKota.kota[i].kt);
        dataKota.kota[i].p = Nil;
        i++;
    }

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

    // Cetak daftar masyarakat
    printf("\nDaftar masyarakat:\n");
    printMasyarakat(dataKota);

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

    // Cetak daftar masyarakat setelah penghapusan
    printf("\nDaftar masyarakat setelah penghapusan:\n");
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

    printf("\nProgram selesai. Terima kasih!\n");
}

void alokasiArray(arrayKota *P){
    do{
        if((*P).length < 5){
            printf("panjang array masih kurang !!!");
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
    }else{
        printf("alokasi gagal !!");
    }
    return P;
}

void addWarga(arrayKota *P, char *nama, char *domisili){
    address warga = alokasi(nama);
    int i = 0;
    address temp;
    if(warga != Nil){
        while(strcmp((*P).kota[i].kt, domisili) != 0){
            if(strcmp((*P).kota[i].kt, domisili) == 0){
                break;
            }
            i++;
        }
        // terjadi jika tidak ada sebuah kota

        if(i >= (*P).length){
            printf("tidak ada kota !!!");
            return;
        }else{
            // terjadi jika terdapat sebuah kota 
            temp = (*P).kota[i].p;
            if(temp != Nil){
                while(temp->q != Nil){
                    temp = temp->q;
                }   
                temp->q = warga;
            }else{
                (*P).kota[i].p = warga;
            }
        }
    }else{
        printf("alokasi gagal !!");
        return;
    }
}

void printMasyarakat(arrayKota P){
    int i;
    address temp;
    if(P.kota != Nil){
        i = 0;
        while(i < P.length){
            printf("Kota %d : %s", i+1, P.kota[i].kt);
            printf("\nWarga : ");
            temp = P.kota[i].p;
            if(temp != Nil){
                while(temp != Nil){
                    printf("%s , ", temp->nm);
                    temp = temp->q;
                }
            }else{
                printf("(Nil)");
            }
            printf("\n");
            i++;
        }
    }else{
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

    while(( (i < dataKota->length) && strcmp(dataKota->kota[i].kt, domisili) != 0)){
        i++;
    }

    if(i >= dataKota->length){
        printf("kota tidak ditemukan");
        return;
    }

    first = dataKota->kota[i].p;
    if(first != Nil){
        if((strcmp(dataKota->kota[i].p->nm, nama) == 0)){ //kondisi untuk node berada di posisi pertama
            temp = dataKota->kota[i].p;
            dataKota->kota[i].p = dataKota->kota[i].p->q;
            temp->q = Nil;
            free(temp);
        }else{
            while(first != Nil){ //loop untuk node tidak di pertama, bisa ditengah atau diakhir
                prev = first;
                first = first->q;
                if(strcmp(first->nm, nama) == 0){ // kondisi untuk menghapus data di tenganh
                    temp = first;
                    first = first->q;
                    prev->q = first;
                    free(temp);
                }
            }
        }
        printf("penghapusan warga berhasil di kota %s", dataKota->kota[i].kt);
        return;
    }else{
        printf("tidak ada warga yang bisa dihapus di kota %s ", dataKota->kota[i].kt);
        return;
    }
}

void deleteKota(kota *dataKota, char *kota){
    
}