#include "head.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define Nil NULL

//====================
// MODUL NON-CONTROL
//====================
void mainProgram(){
    
    List head; 
    head.first = Nil;
    int pilihan;
    char nama[MAX];
    char kota[MAX];
    
    printf("SELAMAT DATANG DALAM PROGRAM KEPENDUDUKAN\n");
    printf("Program Kependudukan\n");
    for(;;){
        system("cls");
        banner();
        printf("List warga daerah : \n");
        printf("=================================\n");
        printMasyarakat(head);
        printf("\n=================================\n");
        printf("Apa yang akan anda lakukan ? \n1. Tambah Kota\n2. Hapus kota\n3. Tambah data warga\n4. Hapus data warga\n5. Keluar\nMasukkan pilihan anda : ");
        scanf("%d", &pilihan);
        system("cls");
        if(pilihan == 1){
            printf("Pilihan : Tambah Kota\n");
            printf("Masukkan nama kota yang ingin ditambahkan ke list : ");
            scanf("%s", kota);
            addKota(&head, kota);
        }else if(pilihan == 2){
            printf("Pilihan : Hapus Kota\n");
            printf("Masukkan data kota yang akan dihapus : ");
            scanf("%s", kota);
            deleteKota(&head, kota);
        }else if(pilihan == 3){
            printf("Pilihan : Tambah data warga\n");
            printf("Masukkan nama warga yang akan anda tambahkan : ");
            scanf("%s", nama);
            printf("Masukkan kota yang akan anda ditambahkan warganya : ");
            scanf("%s", kota);
            addWarga(&head, nama, kota);
        }else if(pilihan == 4){
            printf("Pilihan : Hapus data warga\n");
            printf("Masukkan nama warga yang akan anda hapus : ");
            scanf("%s", nama);
            printf("Masukkan kota dari data warga yang akan anda hapus : ");
            scanf("%s", kota);
            deleteWarga(&head, nama, kota);
        }else if(pilihan == 5){
            printf("terimakasih sudah menggunakan program ini.......");
            break;
        }
    }
}

addressKota alokasiKota(char *nama){
    addressKota P = (addressKota)malloc(sizeof(kota));
    if(P != Nil){
        strcpy(P->kt, nama);
        P->p = Nil;
        P->next = Nil;
    }else{
        printf("alokasi gagal !!");
    }
    return P;
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

void banner(){
    printf("===============================================================\n");
    printf(" ____  __    __                                      \n");
    printf("|    \\|  |  |  |      ___ ___ ___ ___ ___ ___ _____ \n");
    printf("|  |  |  |__|  |__   | . |  _| . | . |  _| .'|     |\n");
    printf("|____/|_____|_____|  |  _|_| |___|_  |_| |__,|_|_|_|\n");
    printf("                     |_|         |___|              \n");
    printf("===============================================================\n");

}

//====================
// MODUL CONTROL
//====================
void addKota(List *P, char *domisili){
    addressKota kota = alokasiKota(domisili);
    addressKota prev = Nil;
    addressKota head = (P)->first;
    if(kota != Nil){
        if(head != Nil){
            while((head != Nil) && (strcmp(head->kt, domisili) != 0)){
                prev = head;
                head = head->next;
            }
            if(head == Nil){
                prev->next = kota;
                printf("kota %s berhasil ditambahkan. \n", domisili);
            }else if(strcmp(head->kt, domisili) == 0){
                printf("kota sudah ada....");
            }
        }else{
            (P)->first = kota; 
            printf("\nkota %s berhasil ditambahkan. \n", domisili);
        }
    }else{
        printf("alokasi gagal !!");
    }
}

void addWarga(List *P, char *nama, char *domisili){
    // List (*P) selalu didepan
    address warga = alokasi(nama);
    address prev = Nil;
    addressKota head = (*P).first;
    address headWarga = Nil;
    if( warga == Nil){
        printf("alokasi gagal !!");
        return;
    }
    if(head != Nil){
        while((head != Nil) && (strcmp(head->kt, domisili) != 0)){
            head = head->next;
        }
        
        if(head == Nil){
            printf("input tidak ada kota dalam list\n");
            free(warga);
            return;
        }
        if(strcmp(head->kt, domisili) == 0){
            headWarga = head->p;
            if(headWarga != Nil){
                while((headWarga->q != Nil) && (strcmp(headWarga->nm, nama) != 0)){
                    prev = headWarga;
                    headWarga = headWarga->q;
                }
                if(headWarga->q == Nil){
                    headWarga->q = warga;
                }
                if(strcmp(headWarga->nm, nama) == 0){
                    printf("nama duplikat pada kota %s \n", domisili);
                    return;
                }
            }else{
                head->p = warga;
                headWarga = head->p;
            }
        }
    }else {
        printf("tidak ada kota.....");
        return;
    }

}

void printMasyarakat(List P){
    addressKota tempKota = P.first;
    address temp = Nil;
    if(tempKota != Nil){
        while(tempKota != Nil){
            printf("Kota %s ", tempKota->kt);
            printf("\nWarga : ");
            temp = tempKota->p;
            if(temp != Nil){
                while(temp != Nil){
                    printf("%s - ", temp->nm);
                    temp = temp->q;
                }
                printf("(Nil)");
            }else{
                printf("(Nil)");
            }
            printf("\n");
            tempKota = tempKota->next;
        }
    }else{
        printf("tidak ada data kota dan warga\n");
    }
}


void deleteWarga(List *dataKota, char *nama, char *domisili){
    address head_warga = Nil;
    addressKota head_kota = (*dataKota).first;
    address prev_warga = Nil;
    address temp_warga = Nil;

    if(head_kota != Nil){
        while(head_kota != Nil && strcmp(head_kota->kt, domisili) != 0 ){
            head_kota = head_kota->next;
        }
        if(head_kota == Nil){
            printf("kota tidak ada dalam list....");
            return;
        }
        head_warga = head_kota->p;
        
            while(head_warga->q != Nil && strcmp(head_warga->nm, nama) != 0){
                prev_warga = head_warga;
                head_warga = head_warga->q;
            }

            if(head_warga == Nil){
                printf("tidak ada list dalam kota ini......");
                return;
            }

            if(prev_warga == Nil){ // Node berada di posisi pertama
                temp_warga = (*dataKota).first->p;
                (*dataKota).first->p = (*dataKota).first->p->q;
                free(temp_warga);
                printf("data %s sudah berhasil dihapus di kota %s.\n", nama, domisili);
            }else{
                temp_warga = head_warga;
                head_warga = head_warga->q;
                prev_warga->q = head_warga;
                free(temp_warga);
                printf("data %s sudah berhasil dihapus di kota %s.\n", nama, domisili);
            }
    }else{
        printf("tidak ada list kota....");
    }
}

void deleteKota(List *dataKota, char *kota){
    addressKota head_kota = (dataKota)->first;
    addressKota prev_kota = Nil;
    addressKota temp_kota = Nil;
    address temp_warga = Nil;
    address head_warga = Nil;

    if(head_kota != Nil){
        while(head_kota != Nil && strcmp(head_kota->kt, kota) != 0 ){
            prev_kota = head_kota;
            head_kota = head_kota->next;
        }

        if(head_kota == Nil){
            printf("tidak ada data kota yang bisa dihapus...");
            return;
        }

        head_warga = head_kota->p;
        if(head_warga != Nil){
            while(head_warga != Nil){
                temp_warga = head_warga;
                head_warga = head_warga->q;
                free(temp_warga);
            }
        }

        if(prev_kota == Nil){
            temp_kota = (*dataKota).first;
            (*dataKota).first = (*dataKota).first->next;
            head_kota = (*dataKota).first;
            free(temp_kota);
            printf("Kota %s berhasil dihapus\n", kota);
        }else{
            temp_kota = head_kota;
            head_kota = head_kota->next;
            prev_kota->next = head_kota;
            free(temp_kota);
            printf("Kota %s berhasil dihapus\n", kota);
        }  
    }else{
        printf("Tidak ada list kota yang bisa dihapus..");
    }
}